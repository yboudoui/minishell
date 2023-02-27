/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 14:22:41 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"

void pipex(t_list env, t_prompt prompt)
{
	t_list_commande 		cmd;
	t_pipex					pipex;
	static const t_pipex	EMPTY_PIP;
	int						i;

	pipex = EMPTY_PIP;
	pipex.argc = ft_lstsize(prompt->commande);
	cmd = (t_list_commande)prompt->commande;
	pipex.paths = get_paths(env, &pipex);
	pipex.env = env;
	i = 0;
	while (cmd)
	{
		pipex.infile = infile(cmd->content->redir_in);
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->content->redir_out);
		if (pipex.outfile != -1)
			execute((char **)cmd->content->argv, &pipex, i);
		i++;
		cmd = cmd->next;
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

char	**get_paths(t_list env, t_pipex *pipex)
{
	char	**paths;
	char	*path;
	t_list	tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PATH=", 5) == 0)
		{
			path = ft_strdup(tmp->content + 5);
			if (path == NULL)
				return (NULL);
			paths = ft_split(path, ':');
			if (paths == NULL)
				return (NULL);
			free(path);
			pipex->path = true;
			return (paths);
		}
		tmp = tmp->next;
	}
	pipex->path = false;
	return (NULL);
}

int infile(t_list redir_in)
{
	int	fd;

	if (redir_in == NULL)
		return (STDIN_FILENO);
	fd = -1;
	while (redir_in)
	{
		fd = f_open((char *)redir_in->content, O_RDONLY, 0);
		if (fd == -1 && redir_in->next == NULL)
			return (-1);
		if (fd != -1 && redir_in->next != NULL)
			close_fd(&fd);
		if (fd != -1 && redir_in->next == NULL)
			return (fd);
		redir_in = redir_in->next;
	}
	return (STDIN_FILENO);
}

int	outfile(t_list redir_out)
{
	int	fd;
	t_token token;

	if (redir_out == NULL)
		return (STDOUT_FILENO);
	fd = -1;
	token = NULL;
	while (redir_out)
	{
		token = redir_out->content;
		if (token->type == TOKEN_REDIRECT_OUT)
			fd = f_open((char *)redir_out->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (token->type == TOKEN_REDIRECT_OUT_APPEND)
			fd = f_open((char *)redir_out->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1 && redir_out->next == NULL)
			return (-1);
		if (fd != -1 && redir_out->next != NULL)
			close_fd(&fd);
		if (fd != -1 && redir_out->next == NULL)
			return (fd);
		redir_out = redir_out->next;
	}
	return (STDOUT_FILENO);
}
