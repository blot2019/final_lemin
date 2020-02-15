/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar <lcaesar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:15:41 by lcaesar           #+#    #+#             */
/*   Updated: 2019/11/10 15:47:06 by lcaesar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*mallokill(size_t size)
{
	void *result;

	result = malloc(size);
	if (!result)
	{
		free(result);
		exit(1);
	}
	return (result);
}
