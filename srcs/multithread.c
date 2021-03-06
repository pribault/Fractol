/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:57:33 by pribault          #+#    #+#             */
/*   Updated: 2016/12/15 11:00:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_fractal_mt(t_main *win)
{
	pthread_t	thread[win->threads];
	t_band		band[win->threads];
	int			i;
	int			l;

	i = 0;
	l = win->w.w / win->threads;
	mlx_clear_window(win->w.mlx, win->w.win);
	while (i < win->threads)
	{
		band[i].win = win;
		band[i].i = i * l;
		band[i].j = band[i].i + l;
		pthread_create(&thread[i], NULL, (void*)print_fractal, &band[i]);
		i++;
	}
	i = 0;
	while (i < win->threads)
		pthread_join(thread[i++], NULL);
	mlx_put_image_to_window(win->w.mlx, win->w.win, win->w.screen, 0, 0);
	if (win->menu == 1)
		print_menu(win);
}
