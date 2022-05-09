/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:58:50 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/09 10:44:22 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void test_print(t_gen_info *info)
{
	int i;
	printf("PATH: %s\n", info->texture_SO_path);
	printf("PATH: %s\n", info->texture_NO_path);
	printf("PATH: %s\n", info->texture_WE_path);
	printf("PATH: %s\n", info->texture_EA_path);
	printf("F:\nred:%d\nyellow:%d\nblue:%d\n", info->floor.red, info->floor.yellow, info->floor.blue);
	printf("C:\nred:%d\nyellow:%d\nblue:%d\n", info->ceiling.red, info->ceiling.yellow, info->ceiling.blue);
	printf("MAP: \n");
	// printf("%s", info->map[info->map_height - 1]);
	
	i = 0;
	while(info->map[i] != NULL)
	{
	printf("%s", info->map[i]);
		i++;
	}
}

int main(void)
{
	t_gen_info info;
	if (init_data_info(&info))
	//1)NSEW spieler position
	//1.1) was wenn keien spieler position angegeben ist?
	//2)jede zahl/buchstabe in der map durchgehen
	//3)char *8argv abklären
	//4) NO/SO/... fail dann exiten
	{
		test_print(&info);
		create_window();
	}
	// system("leaks cube3d");
	return(0);
}