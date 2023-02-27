/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 19:25:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"

static int	ft_lstsize_prompt(t_prompt lst)
{
	int	out;

	out = 0;
	while (lst)
	{
		out += 1;
		lst = lst->next;
	}
	return (out);
}

// actuellement t_prompt et t_list_commande sont extremement similaire
// on pourrai les intervertirent sans problème mais on a ne la pas fait avant mon départ
void pipex(t_list env, t_prompt prompt)
{
	t_list_commande 		cmd_list;
	t_pipex					pipex;
	t_commande              cmd;
	static const t_pipex	EMPTY_PIP;
	int						i;

	pipex = EMPTY_PIP;
	pipex.argc = ft_lstsize_prompt(prompt);
// la confusion que tu fait ici c'est que tu pense que t_prompt->content est une list de commande
// mais ça n'est plus le cas depuis se matin
//	cmd_list = (t_list_commande)prompt->content;//		<---- kdhrif
	cmd_list = (t_list_commande)prompt;//		<---- yboudoui
	pipex.paths = get_paths(env, &pipex);
	pipex.env = env;
	i = 0;
	while (cmd_list)
	{
		cmd = (t_commande)(cmd_list->content);
		pipex.infile = infile(cmd->redir_in);
		t_token tok = cmd->redir_out->content;
		printf("redir_out input = %s", tok->input);
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->redir_out);
		printf("outfile return = %d\n", pipex.outfile);
		exit(1);
		if (pipex.outfile != -1)
			execute((char **)cmd->argv, &pipex, i);
		i++;
		cmd_list = cmd_list->next;
	}
}

char *check_fpath(t_pipex *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
		{
			if (pipex->path == false)
				generic_err("No such file or directory", 2);
			else
				generic_err("Command not found", 2);
			return (NULL);
		}
	}
	else
		return (NULL);
}


void	null_str_err(char *str)
{
	if (str == NULL)
		generic_err("Malloc error.\n", 0);
}


char *check_slash(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (str[i  - 1] == '/')
		str[i - 1] = '\0';
	return (str);
}

char *get_cmd_path(t_pipex *pipex, char *cmd)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = check_fpath(pipex, cmd);
	if (tmp1 != NULL)
		return (tmp1);
	path_null(pipex, cmd);
	i = -1;
	while (pipex->paths[++i])
	{
		check_slash(pipex->paths[i]);
		tmp1 = ft_strjoin(pipex->paths[i], "/");
		null_str_err(tmp1);
		tmp2 = ft_strjoin(tmp1, cmd);
		null_str_err(tmp2);
		free(tmp1);
		if (access(tmp2, F_OK) == 0)
			return (tmp2);
		free(tmp2);
	}
	return (NULL);
}

char **parse_env(t_list env)
{
	char	**envp;
	int		i;
	t_env_var tmp;
	char *tmp1;
	char *tmp2;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	null_str_err((char *)envp);
	while (env)
	{
		tmp = (t_env_var)env->content;
		tmp1 = ft_strjoin(tmp->name, "=");
		null_str_err(tmp1);
		tmp2 = ft_strjoin(tmp1, tmp->value);
		null_str_err(tmp2);
		free(tmp1);
		envp[i] = tmp2;
		null_str_err(envp[i]);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int exec_cmd(t_pipex *pipex, char **argv, int in, int out)
{
	char *cmd_path;

	dup_fd(in, STDIN_FILENO);
	dup_fd(out, STDOUT_FILENO);
	cmd_path = get_cmd_path(pipex, argv[0]);
	if (cmd_path == NULL)
		return (EXIT_FAILURE);
	if (execve(cmd_path, argv, parse_env(pipex->env)) == -1)
		generic_err("Execve error.\n", 0);
	return (1);
}

void execute(char **argv, t_pipex *pipex, int i)
{
	pid_t	pid;

	pipe_fd(pipex, pipex->fd);
	fork_pid(&pid);
	if (pid == 0)
	{
		close_fd(&pipex->fd[0]);
		exec_cmd(pipex, argv, pipex->infile, pipex->outfile);
		if (exec_cmd(pipex, argv, pipex->infile, pipex->outfile) == -1)
			generic_err("execve", 1);
	}
	else 
	{
		close_fd(&pipex->fd[1]);
		dup_fd(pipex->fd[0], STDIN_FILENO);
		close_fd(&pipex->fd[0]);
		pipeline_status(pipex, i, pid);
	}
}

void	*token_to_string(void *data)
{
	t_token	input;

	input = data;
	if (input == NULL)
		return (NULL);
	return (input->input);
}

t_cmd *cmd_create(t_commande cmd)
{
	t_cmd *new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->argv = list_to_array(cmd->argv, token_to_string);
	new->redir_in = cmd->redir_in;
	new->redir_out = cmd->redir_out;
	/* new->here_document = cmd->here_document; */
	return (new);
}


