/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:24:08 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/10 13:11:28 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include<stdlib.h>

void	init_images(t_global	*global)
{
	int	dm[2];
	global->holes_img[0] = mlx_xpm_file_to_image(global->mlx,
		"src/img/hole1.xpm", &dm[0], &dm[1]);
	global->holes_img[1] = mlx_xpm_file_to_image(global->mlx,
		"src/img/hole2.xpm", &dm[0], &dm[1]);
	global->holes_img[2] = mlx_xpm_file_to_image(global->mlx,
		"src/img/hole3.xpm", &dm[0], &dm[1]);
	global->holes_img[3] = mlx_xpm_file_to_image(global->mlx,
		"src/img/hole4.xpm", &dm[0], &dm[1]);
	global->holes_img[4] = mlx_xpm_file_to_image(global->mlx,
		"src/img/hole5.xpm", &dm[0], &dm[1]);
	global->holes_img[5] = mlx_xpm_file_to_image(global->mlx,
		"src/img/hole6.xpm", &dm[0], &dm[1]);
	global->holes_img[6] = mlx_xpm_file_to_image(global->mlx,
		"src/img/hole7.xpm", &dm[0], &dm[1]);
	global->leave_img = mlx_xpm_file_to_image(global->mlx,
		"src/img/leave.xpm", &dm[0], &dm[1]);
	global->wall_img = mlx_xpm_file_to_image(global->mlx,
		"src/img/wall.xpm", &dm[0], &dm[1]);
	global->player_img = mlx_xpm_file_to_image(global->mlx,
		"src/img/player.xpm", &dm[0], &dm[1]);
	global->hook_img = mlx_xpm_file_to_image(global->mlx,
		"src/img/hook.xpm", &dm[0], &dm[1]);
	global->background_img = mlx_xpm_file_to_image(global->mlx,
		"src/img/background.xpm", &dm[0], &dm[1]);
}
int ft_close (int keycode)
{
	(void) keycode;
	exit(0);
	return (1);
}

int	key_hook(int keycode, t_global *global)
{
	if (keycode == 13)
		move_up(global);
	else if (keycode == 1)
		move_down(global);
	else if (keycode == 0)
		move_left(global);
	else if (keycode == 2)
		move_right(global);
	else if (keycode == 53)
		exit(0);
	return (0);
}

void	set_init_game(t_global *global)
{
	size_t		i;
	size_t		j;

	global->total_point = 0;
	global->current_point = 0;
	global->hook_move = malloc(sizeof(int *) * global->map->height);

	i = -1;
	while (++i < global->map->height)
		global->hook_move[i] = malloc(sizeof(int) * global->map->width);

	i = 0;
	while (i < global->map->height)
	{
		j = 0;
		global->hook_move[i][j] = 0;
		while (j < global->map->width)
		{

			if (global->map->line[i][j] == 'P')
			{
				global->player_position[0] = i;
				global->player_position[1] = j;
			}
			if (global->map->line[i][j] == 'C')
				global->total_point++;
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_map		*map;
	t_global	global;

	if (ac != 2)
		throw_err("you must provid a map and only the map!", &map);
	global.map = (t_map *)malloc(sizeof(t_map));
	if (global.map == NULL)
		throw_err("No memory is avialbale to lunch the game", &map);
	map_parsser(av[1], &global.map);
	global.mlx = mlx_init();
	global.win = mlx_new_window(global.mlx, (global.map)->width * 98,
			(global.map)->height * 95, "hellow world");
	init_images(&global);
	set_init_game(&global);
	global.img_nb = 0;
	global.frame = 0;
	global.move_down = 0;
	global.game_on = 1;
	global.moves_count = 0;
	mlx_key_hook(global.win, key_hook, &global);
	mlx_loop_hook(global.mlx, &render, &global);
	mlx_hook(global.win, 17, 1L<<5, ft_close, &global);
	mlx_loop(global.mlx);
	//printf("working..");
	return (0);
}
//W == 13 up 
//A == 0 left
//S == 1 down
//D == 2 right