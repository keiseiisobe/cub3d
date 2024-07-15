/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:12:38 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 02:12:41 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	handle_error(!ptr && errno == ENOMEM);
	return (ptr);
}
