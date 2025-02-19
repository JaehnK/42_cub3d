/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:02:32 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/30 16:26:41 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
<<<<<<< HEAD:srcs/00_main.c
	int	i;

	i = 0;
	while (f[i])
	{
		printf("%s: %d\n", f[i], i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_cub	*cub;
	int		i;

	cub = malloc(sizeof(t_cub));
	cub->data = malloc(sizeof(t_data));
	cub->file = NULL;
	ft_mlx_init(cub->data);
	ft_parse_file(argc, argv, &(cub->file));
	ft_read_cub_value(&(cub->file), &cub);
	print_file(cub->file->maparr);
	cub->data->buf_flag = 0;
	cub->data->buf = malloc(sizeof(int *) * (SCREEN_H + 1));
	i = 0;
	while (i < SCREEN_H)
		cub->data->buf[i++] = malloc(sizeof(int) * SCREEN_W);
	cub->data->buf[i] = NULL;
	mlx_loop_hook(cub->data->mlx, main_loop, &cub);
	mlx_loop(cub->data->mlx);
=======
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int	result;
	int				neg;

	result = 0;
	neg = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' \
			|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(result * neg));
>>>>>>> kangwoo:practice/libft/ft_atoi.c
}
