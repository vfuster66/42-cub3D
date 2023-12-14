/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecullier <ecullier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:00:43 by ecullier          #+#    #+#             */
/*   Updated: 2023/12/14 10:03:41 by ecullier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inludes/cub3D.h"

void	exit_cleanup(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}
	free_data(data);
	exit(code);
}

int	exit_game(t_data *data)
{
	exit_cleanup(data, 0);
	return (0);
}