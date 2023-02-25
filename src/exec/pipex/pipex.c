/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/25 20:02:15 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"
#include <unistd.h>

void pipex(t_list env, t_prompt prompt)
{
	t_list_commande 		cmd;
	t_pipex					pipex;
	static const t_pipex	EMPTY_PIP;

	pipex = EMPTY_PIP;
	cmd = (t_list_commande)prompt->commande;
	pipex.paths = get_paths(env, &pipex);
	pipex.env = env;
	while (cmd)
	{
		pipex.infile = infile(cmd->content->redir_in);
		if (pipex.infile == -1)
			continue ;
		pipex.outfile = outfile(cmd->content->redir_out);
		if (pipex.outfile == -1)
			continue ;
		execute((char **)cmd->content->argv, &pipex);


		cmd = cmd->next;
	}
}

char *get_cmd_path(char *cmd)
{

}

int exec_cmd(t_pipex *pipex, char **argv, int in, int out)
{
	char *cmd_path;

	dup_fd(in, STDIN_FILENO);
	dup_fd(out, STDOUT_FILENO);
	cmd_path = get_cmd_path(argv[0]);


}

void execute(char **argv, t_pipex *pipex)
{
	pid_t	pid;

	pipe_fd(pipex, pipex->fd);
	fork_pid(&pid);
	if (pid == 0)
	{
		close_fd(&pipex->fd[0]);
		exec_cmd(pipex, argv, pipex->infile, pipex->outfile);


	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("exit status: %d\n", WEXITSTATUS(status));
	}
	else
		generic_err(NULL, 1);
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
