/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 14:59:41 by rheukelm          #+#    #+#             */
/*   Updated: 2017/07/04 14:59:43 by rheukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf3d.h"

int				check_map(char *file)
{
	int		fd;
	int		num;
	int		i;
	char	*line;

	num = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i] != '\0')
		{
			if (!(line[i] == '0' || line[i] == '1' || line[i] == 'x'))
			{
				ft_putendl_fd("error: invalid character in file", 2);
				return (-1);
			}
			i++;
		}
		free(line);
		num++;
	}
	close(fd);
	return (num - 1);
}

int				get_map(t_var *f, char *file)
{
	int		i;
	int		fd;
	char	*line;

	if ((f->nbl = check_map(file)) == -1)
		return (-1);
	fd = open(file, O_RDONLY);
	if (!(f->map = (char **)malloc(sizeof(char) * f->nbl)))
		return (-1);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(f->map[i] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))))
			return (-1);
		f->map[i] = ft_strcpy(f->map[i], line);
		free(line);
		i++;
	}
	close(fd);
	return (1);
}

static t_var	*init_mlx(char *fd)
{
	t_var	*f;
	char	*name;

	name = ft_strjoin("wolf3d :", fd);
	if (!(f = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	f->mlx = mlx_init();
	f->img = mlx_new_image(f->mlx, WIN_W, WIN_H);
	f->win = mlx_new_window(f->mlx, WIN_W, WIN_H, name);
	free(name);
	f->imgdata = mlx_get_data_addr(f->img, &f->bpp, &f->size_line,
			&f->endian);
	if (get_map(f, fd) == -1)
		return (NULL);
	if (ft_player_init(f) == -1)
		return (NULL);
	f->cam.xplane = 0.0;
	f->cam.yplane = 0.6;
	return (f);
}

int				main(int argc, char **argv)
{
	t_var	*f;

	if (argc != 2 || !argv[1])
	{
		ft_putendl("usage: ./wolf3d input_file");
		return (0);
	}
	if ((f = init_mlx(argv[1])) != NULL)
	{
		ft_instructions();
		ft_draw(f);
		mlx_hook(f->win, 2, (1L << 0), key_press, f);
		mlx_hook(f->win, 17, 0L, &ft_close, f);
		mlx_loop(f->mlx);
		mlx_destroy_window(f->mlx, f->win);
	}
	return (0);
}
