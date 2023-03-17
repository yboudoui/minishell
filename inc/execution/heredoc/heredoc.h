/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:06:03 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 09:39:25 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "list.h"
# include "string.h"

# include "prompt.h"

// open
# include <sys/stat.h>
# include <fcntl.h>

// fork
# include <sys/types.h>
# include <unistd.h>

// wait
# include <sys/wait.h>

// sigaction
# include <signal.h>

// read line
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_prompt	*t_prompt;
int	heredoc_read(t_token token);
int	heredoc(t_prompt cmd);

#endif
