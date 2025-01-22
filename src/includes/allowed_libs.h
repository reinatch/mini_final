/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allowed_libs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:54:09 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/21 16:29:22 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOWED_LIBS_H
# define ALLOWED_LIBS_H

# include "../../libft/includes/libft.h" // libft
# include <fcntl.h>                // open flags
# include <readline/history.h>     // history
# include <readline/readline.h>    // readline
# include <signal.h>               // sigaction
# include <stdio.h>                // perror
# include <stdlib.h>               // getenv
# include <sys/stat.h>             // stat
# include <sys/wait.h>             // waitpid
# include <unistd.h>               // getpwd

#endif
