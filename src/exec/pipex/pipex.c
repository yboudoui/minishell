/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/28 20:39:14 by kdhrif           ###   ########.fr       */
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

void pipex(t_list env, t_prompt prompt)
{
	t_list_commande 		cmd_list;
	t_pipex					pipex;
	t_commande              cmd;
	static const t_pipex	EMPTY_PIP;
	int						i;

	pipex = EMPTY_PIP;
	pipex.argc = ft_lstsize_prompt(prompt);
	cmd_list = (t_list_commande)prompt;
	pipex.paths = get_paths(env, &pipex);
	pipex.env = env;
	i = 0;
	while (cmd_list)
	{
		cmd = (t_commande)(cmd_list->content);
		pipex.infile = infile(cmd->redir_in);
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->redir_out);
		if (pipex.outfile != -1)
			execute(cmd->argv, &pipex, i);
		i++;
		cmd_list = cmd_list->next;
	}
}

char **parse_the_fucking_arg(t_list argv, t_pipex *pipex)
{
	char **arg;
	char **ret;
	int i;

	ret = malloc((pipex->argc + 1) * sizeof(char *));
	if (ret == NULL)
	{
		generic_err("Malloc failed", NULL, 3);
		return (NULL);
	}
	i = 0;
	while (argv)
	{
		arg = (char **)argv->content;
		ret[i] = arg[0];
		i++;
		argv = argv->next;
	}
	ret[i] = (char *)0;
	return (ret);
}

void execute(t_list shit, t_pipex *pipex, int i)
{
	pid_t	pid;
	char **argv;

	argv = parse_the_fucking_arg(shit, pipex);
	if (argv == NULL)
		return;
	pipe_fd(pipex, pipex->fd);
	fork_pid(&pid);
	if (pid == 0)
	{
		close_fd(&pipex->fd[0]);
	if (pipex->outfile == STDOUT_FILENO)
			exec_cmd(pipex, argv, pipex->infile, pipex->outfile);
	else 
			exec_cmd(pipex, argv, pipex->infile, pipex->outfile);
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


