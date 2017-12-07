/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 13:58:03 by rheukelm          #+#    #+#             */
/*   Updated: 2017/07/05 13:58:05 by rheukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf3d.h"

static void		ft_put_pixel(t_var *f, int x, int y, int colour)
{
	int				i;
	unsigned int	p;

	i = 0;
	p = x * (f->bpp / 8) + y * (f->size_line);
	while (i < (f->bpp / 8))
	{
		f->imgdata[p + i] = colour;
		colour >>= 8;
		i++;
	}
}

static int		ft_wall_colour(t_var *f)
{
	int				colour;

	if (f->draw.side == 0 && f->cam.xdir >= 0)
		colour = 0xFE0000;
	else if (f->draw.side == 0 && f->cam.xdir < 0)
		colour = 0xFEFE00;
	else if (f->draw.side == 1 && f->cam.ydir >= 0)
		colour = 0x00B2FE;
	else
		colour = 0xFE7700;
	if (f->draw.side == 1)
		colour = colour / 2;
	return (colour);
}

static void		ft_draw_init(t_var *f)
{
	f->cam.x = 2 * f->draw.x / (double)WIN_W - 1;
	f->draw.side = 0;
	f->draw.hit = 0;
	f->cam.xpos = f->player.xpos;
	f->cam.ypos = f->player.ypos;
	f->cam.xdir = f->player.xdir + f->cam.xplane * f->cam.x;
	f->cam.ydir = f->player.ydir + f->cam.yplane * f->cam.x;
	f->draw.xmap = (int)f->cam.xpos;
	f->draw.ymap = (int)f->cam.ypos;
	f->draw.xdelta_dist = sqrt(1 + pow(f->cam.ydir / f->cam.xdir, 2));
	f->draw.ydelta_dist = sqrt(1 + pow(f->cam.xdir / f->cam.ydir, 2));
}

static void		ft_draw_slice(t_var *f)
{
	int				y;
	int				colour;

	y = 0;
	while (y < WIN_H)
	{
		if (y < f->draw.start)
			colour = 0x5AD4EC;
		else if (y > f->draw.end)
			colour = 0x686868;
		else
		{
			if (f->draw.hit == 1)
				colour = ft_wall_colour(f);
		}
		ft_put_pixel(f, f->draw.x, y, colour);
		y++;
	}
}

void			ft_draw(t_var *f)
{
	f->draw.x = 0;
	while (f->draw.x < WIN_W)
	{
		ft_draw_init(f);
		ft_raycast(f);
		ft_draw_slice(f);
		f->draw.x++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
