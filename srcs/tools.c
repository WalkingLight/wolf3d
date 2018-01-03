/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 13:36:15 by rheukelm          #+#    #+#             */
/*   Updated: 2017/07/10 13:36:19 by rheukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf3d.h"

void		ft_print(char **arr)
{
	while (*arr)
		printf("%s\n", *arr++);
}

void		closeProg(t_var *f)
{
	int		i;

	i = 0;
	while (i < f->nbl)
	{
		free(f->map[i]);
		i++;
	}
	free(f->map);
	mlx_clear_window(f->mlx, f->win);
	exit(0);
}

int			ft_player_init(t_var *f)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (f->map[j])
	{
		i = 0;
		while (f->map[j][i])
		{
			if (f->map[j][i] == 'x')
			{
				f->player.xpos = j;
				f->player.ypos = i;
				f->player.xdir = -1;
				f->player.ydir = 0;
				return (0);
			}
			i++;
		}
		j++;
	}
	ft_putendl_fd("error: player not found in map", 2);
	return (-1);
}

int			ft_linelen(char *buf, int k)
{
	int		len;

	len = 0;
	while (buf[k] != '\n' && buf[k] != '\0')
	{
		k++;
		len++;
	}
	return (len);
}

void		ft_instructions(void)
{
	ft_putendl("------- INSTRUCTIONS -------");
	ft_putendl("< > : rotate camera");
	ft_putendl("^ v : move forward and back");
	ft_putendl("ESC : close");
}
