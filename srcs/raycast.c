/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:59:40 by rheukelm          #+#    #+#             */
/*   Updated: 2017/07/10 15:59:42 by rheukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf3d.h"

static void	ft_step(t_var *f)
{
	if (f->cam.xdir < 0)
	{
		f->draw.xstep = -1;
		f->draw.xside_dist = (f->cam.xpos - (double)f->draw.xmap) \
								* f->draw.xdelta_dist;
	}
	else
	{
		f->draw.xstep = 1;
		f->draw.xside_dist = ((double)f->draw.xmap + 1.0 - f->cam.xpos)\
								* f->draw.xdelta_dist;
	}
	if (f->cam.ydir < 0)
	{
		f->draw.ystep = -1;
		f->draw.yside_dist = (f->cam.ypos - (double)f->draw.ymap) \
								* f->draw.ydelta_dist;
	}
	else
	{
		f->draw.ystep = 1;
		f->draw.yside_dist = ((double)f->draw.ymap + 1.0 - f->cam.ypos)\
								* f->draw.ydelta_dist;
	}
}

static void	ft_hit(t_var *f)
{
	while (f->draw.hit != 1 && f->draw.ymap > 0 && \
			f->draw.ymap < ft_linelen(f->map[f->draw.xmap], 0) && \
			f->draw.xmap > 0 && f->draw.xmap <= f->nbl)
	{
		if (f->draw.xside_dist < f->draw.yside_dist)
		{
			f->draw.side = 0;
			f->draw.xmap += f->draw.xstep;
			f->draw.xside_dist += f->draw.xdelta_dist;
		}
		else
		{
			f->draw.side = 1;
			f->draw.ymap += f->draw.ystep;
			f->draw.yside_dist += f->draw.ydelta_dist;
		}
		if (f->map[f->draw.xmap][f->draw.ymap] == '1')
			f->draw.hit = 1;
	}
}

static void	ft_wall_dist(t_var *f)
{
	if (f->draw.side == 0)
		f->cam.wall_dist = fabs((f->draw.xmap - f->cam.xpos + \
		(1 - f->draw.xstep) / 2) / f->cam.xdir);
	else
		f->cam.wall_dist = fabs((f->draw.ymap - f->cam.ypos + \
		(1 - f->draw.ystep) / 2) / f->cam.ydir);
	if (f->cam.wall_dist <= 0.05)
		f->cam.wall_dist = 0.05;
}

void		ft_raycast(t_var *f)
{
	ft_step(f);
	ft_hit(f);
	ft_wall_dist(f);
	f->draw.height = fabs(WIN_H / f->cam.wall_dist);
	if ((f->draw.start = -(f->draw.height) / 2 + WIN_H / 2) < 0)
		f->draw.start = 0;
	if ((f->draw.end = f->draw.height / 2 + WIN_H / 2) >= WIN_H)
		f->draw.end = WIN_H - 1;
}
