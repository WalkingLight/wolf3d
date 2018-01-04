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
/*
static int		ft_open(char *file, int *fd)
{
	if (BUFF_SIZE < 1)
	{
		ft_putendl_fd("error: BUFF_SIZE must be greater than 0", 2);
		return (-1);
	}
	if ((*fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl_fd("error: could not read file", 2);
		return (-1);
	}
	return (1);
}

static char		*ft_readbuf(char *file, int *nbl)
{
	int			fd;
	char		*buf;
	char		*line;

	buf = ft_strnew(1);
	if (ft_open(file, &fd) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0 && (*nbl)++ > -1)
	{
		buf = ft_strjoin(ft_strjoin(buf, line), "\n");
		free(line);
	}
	if (close(fd) == -1)
	{
		ft_putendl_fd("error: could not close connection to file", 2);
		return (NULL);
	}
	return (buf);
}

static char		**ft_getmap(char *buf, int nbl)
{
	int			i;
	int			k;
	int			j;
	char		**map;

	k = 0;
	j = 0;
	if (!buf)
		return (NULL);
	if (!(map = (char **)malloc(sizeof(char) * nbl)))
		return (NULL);
	printf("nbl->%d\n", nbl);
	while (buf[k] != '\0' && j < nbl)
	{
		i = 0;
		if (!(map[j] = (char *)malloc(sizeof(char) * ft_linelen(buf, k))))
			return (NULL);
		while (buf[k] != '\n' && buf[k] != '\0')
		{
			map[j][i++] = buf[k++];
		}
		map[j][i] = '\0';
		k++;
		j++;
	}
	ft_print(map);
	return (map);
}
*/

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
		printf("read -> '%s'\n", line);
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
	printf("nbl -> %d\n", num - 1);
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
		ft_print(f->map);
		ft_instructions();
		ft_draw(f);
		mlx_hook(f->win, 2, (1L << 0), key_press, f);
		mlx_loop(f->mlx);
		mlx_destroy_window(f->mlx, f->win);
	}
	return (0);
}
