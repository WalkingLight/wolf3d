/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 14:59:41 by rheukelm          #+#    #+#             */
/*   Updated: 2018/01/10 13:31:13 by rheukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf3d.h"

int				ft_checkchar(char *buf)
{
	int		i;

	i = 0;
	while (buf[i] != '\0')
		i++;
	buf[i - 1] = '\0';
	i = 0;
	while (buf[i])
	{
		if (buf[i] != '\n' && buf[i] != '0' && buf[i] != '1'\
				&& buf[i] != 'x' && buf[i] != '\0')
		{
			ft_putendl("error: invalid characters in map");
			return (-1);
		}
		i++;
	}
	return (0);
}

static char		*ft_getbuf(char *file, int *nbl)
{
	int		fd;
	char	*buf;
	char	*line;

	buf = ft_strnew(1);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0 && (*nbl)++ > -1)
	{
		buf = ft_strjoin(ft_strjoin(buf, line), "\n");
		free(line);
	}
	if (ft_checkchar(buf) == -1)
		return (NULL);
	if (close(fd) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (NULL);
	}
	return (buf);
}

static char		**ft_getmap(char *buf, int nbl)
{
	int		i;
	int		k;
	int		j;
	char	**map;

	k = 0;
	j = 0;
	if (!buf)
		return (NULL);
	if (!(map = (char **)malloc(sizeof(char *) * nbl)))
		return (NULL);
	while (buf[k] != '\0' && j < nbl)
	{
		i = 0;
		if (!(map[j] = (char *)malloc(sizeof(char) * ft_linelen(buf, k))))
			return (NULL);
		while (buf[k] != '\n' && buf[k] != '\0')
			map[j][i++] = buf[k++];
		map[j][i] = '\0';
		k++;
		j++;
	}
	return (map);
}

static t_var	*init_mlx(char *fd)
{
	t_var	*f;
	char	*buf;
	char	*name;

	name = ft_strjoin("wolf3d :", fd);
	if (!(f = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	buf = ft_getbuf(fd, &(f->nbl));
	if ((f->map = ft_getmap(buf, f->nbl)) == NULL)
		return (NULL);
	free(buf);
	if (ft_player_init(f) == -1)
		return (NULL);
	f->nbl = 0;
	f->mlx = mlx_init();
	f->img = mlx_new_image(f->mlx, WIN_W, WIN_H);
	f->win = mlx_new_window(f->mlx, WIN_W, WIN_H, name);
	f->imgdata = mlx_get_data_addr(f->img, &f->bpp, &f->size_line,
			&f->endian);
	f->cam.xplane = 0.0;
	f->cam.yplane = 0.6;
	free(name);
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
