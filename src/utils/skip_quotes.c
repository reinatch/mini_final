/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:31:52 by rerodrig          #+#    #+#             */
/*   Updated: 2025/01/25 00:39:48 by rerodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_to_closing_quote(char **str)
{
	char	starting_quote;
	char	*temp;

	temp = *str;
	if (!is_quote(*temp))
		return ;
	starting_quote = *temp++;
	while (*temp && *temp != starting_quote)
		temp++;
	*str = temp;
}
