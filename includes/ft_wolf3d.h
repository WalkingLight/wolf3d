/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 15:00:26 by rheukelm          #+#    #+#             */
/*   Updated: 2017/07/04 15:01:55 by rheukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF3D_H
# define FT_WOLF3D_H

# include "../libft/includes/libft.h"
# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>

# define WIN_W 1280
# define WIN_H 720

typedef struct	s_player
{
	double		xpos;
	double		ypos;
	double		xdir;
	double		ydir;
}				t_player;

typedef struct	s_cam
{
	double		x;
	double		xpos;
	double		ypos;
	double		xdir;
	double		ydir;
	double		xplane;
	double		yplane;
	double		wall_dist;
}				t_cam;

typedef struct	s_draw
{
	int			x;
	int			xmap;
	int			ymap;
	int			start;
	int			end;
	int			height;
	int			side;
	int			hit;
	int			xstep;
	int			ystep;
	double		xside_dist;
	double		yside_dist;
	double		xdelta_dist;
	double		ydelta_dist;
}				t_draw;

typedef struct	s_var
{
	int			nbl;
	int			bpp;
	int			size_line;
	int			endian;
	char		*imgdata;
	char		**map;
	void		*mlx;
	void		*win;
	void		*img;
	t_cam		cam;
	t_draw		draw;
	t_player	player;
}				t_var;

void			ft_instructions(void);
int				ft_player_init(t_var *f);
int				ft_linelen(char *buf, int k);
int				key_press(int keycode, t_var *f);
void			ft_draw(t_var *f);
void			ft_raycast(t_var *f);
void			ft_print(char **arr);
int				ft_close(void);

#endif
