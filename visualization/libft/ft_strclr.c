/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:19:47 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/10 19:01:06 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *str)
{
	int i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			str[i] = '\0';
			i++;
		}
	}
}
