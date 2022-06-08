/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:54:23 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/08 21:37:24 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_startval(int x, t_gen_info *info)
{
	t_point	view;

	view.x = (info->player.plane.x * info->raycast.camera_x);
	view.y = (info->player.plane.y * info->raycast.camera_x);
	info->hit = 0;
	info->player.step_x = 1;
	info->raycast.camera_x = (double)(2 * x) / (double)SCREEN_W - 1;
	info->raycast.dir.x = info->player.dir.x + view.x;
	info->raycast.dir.y = info->player.dir.y + view.y;
}

int	main(int argc, char *argv[])
{
	t_gen_info	info;

	init_genaral_info(&info);
	if (init_data_info(&info, argv, argc))
	{
		get_textures(&info);
		init_raycast_info(&info);
		create_window(&info);
	}
	else
	{
		close(info.fd);
		system("leaks cube3d");
		exit(1);
	}
	error_free_exit(NULL, &info, INFO_MAP);
	return (0);
}
