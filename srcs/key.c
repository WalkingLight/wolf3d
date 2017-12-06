/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 13:50:02 by rheukelm          #+#    #+#             */
/*   Updated: 2017/07/05 13:50:04 by rheukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf3d.h"

static int	ft_rotate(int keycode, double tmp_dir, double tmp_plane, t_var *f)
{
	if (keycode == 123 || keycode == 0)
	{
		f->player.xdir = f->player.xdir * cos(0.05)
			- f->player.ydir * sin(0.05);
		f->player.ydir = tmp_dir * sin(0.05)
			+ f->player.ydir * cos(0.05);
		f->cam.xplane = f->cam.xplane * cos(0.05)
			- f->cam.yplane * sin(0.05);
		f->cam.yplane = tmp_plane * sin(0.05)
			+f->cam.yplane * cos(0.05);
	}
	if (keycode == 124 || keycode == 2)
	{
		f->player.xdir = f->player.xdir * cos(-0.05)
			- f->player.ydir * sin(-0.05);
		f->player.ydir = tmp_dir * sin(-0.05)
			+ f->player.ydir * cos(-0.05);
		f->cam.xplane = f->cam.xplane * cos(-0.05)
			- f->cam.yplane * sin(-0.05);
		f->cam.yplane = tmp_plane * sin(-0.05)
			+f->cam.yplane * cos(-0.05);
	}
	ft_draw(f);
	return (0);
}

int			key_press(int keycode, t_var *f)
{
	if (keycode == 53)
	{
		mlx_clear_window(f->mlx, f->win);
		exit(0);
	}
	if (keycode == 126 || keycode == 13)
	{
		if (f->map[(int)(f->player.xpos + f->player.xdir * 0.2)]
				[(int)(f->player.ypos)] != '1')
			f->player.xpos += f->player.xdir * 0.2;
		if (f->map[(int)(f->player.xpos)]
				[(int)(f->player.ypos + f->player.ydir * 0.2)] != '1')
			f->player.ypos += f->player.ydir * 0.2;
	}
	if (keycode == 125 || keycode == 1)
	{
		if (f->map[(int)(f->player.xpos - f->player.xdir * 0.2)]
				[(int)(f->player.ypos)] != '1')
			f->player.xpos -= f->player.xdir * 0.2;
		if (f->map[(int)(f->player.xpos)]
				[(int)(f->player.ypos - f->player.ydir * 0.2)] != '1')
			f->player.ypos -= f->player.ydir * 0.2;
	}
	ft_rotate(keycode, f->player.xdir, f->cam.xplane, f);
	return (0);
}
