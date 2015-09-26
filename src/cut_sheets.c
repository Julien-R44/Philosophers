/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_sheets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/26 01:18:47 by y0ja              #+#    #+#             */
/*   Updated: 2015/09/26 04:18:49 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void		cut_sprite_sheet(SDL_Rect *clip, int x, int y, int w, int h)
{
	clip->x = x;
	clip->y = y;
	clip->h = h;
	clip->w = w;
}

void	cut_sheets(t_sprite *naruto, t_sprite *sasuke, t_sprite *sakura, t_sprite *kakashi, t_sprite *kankuro)
{
	int len;
	int	width;
	int	i;

	i = -1;
	len = naruto->img->h;
	cut_sprite_sheet(&naruto->clip[0], 0, 0, 45, len);
	cut_sprite_sheet(&naruto->clip[1], 50, 0, 45, len);
	cut_sprite_sheet(&naruto->clip[2], 100, 0, 45, len);
	cut_sprite_sheet(&naruto->clip[3], 147, 0, 50, len);
	cut_sprite_sheet(&naruto->clip[4], 195, 0, 50, len);
	cut_sprite_sheet(&naruto->clip[5], 243, 0, 50, len);
	len = sasuke->img->h;
	cut_sprite_sheet(&sasuke->clip[0], 0, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[1], 50, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[2], 100, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[3], 147, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[4], 195, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[5], 242, 0, 45, len);
	len = sakura->img->h;
	cut_sprite_sheet(&sakura->clip[0], 0, 0, 80, len);
	cut_sprite_sheet(&sakura->clip[1], 80, 0, 80, len);
	cut_sprite_sheet(&sakura->clip[2], 160, 0, 80, len);
	cut_sprite_sheet(&sakura->clip[3], 240, 0, 80, len);
	cut_sprite_sheet(&sakura->clip[4], 320, 0, 80, len);
	cut_sprite_sheet(&sakura->clip[5], 0, 0, 80, len);
	// Kankuro
	len = kankuro->img->h;
	width = 41;
	while (++i < 6)
		cut_sprite_sheet(&kankuro->clip[i], width * i, 0, width, len);

	len = kakashi->img->h;
	cut_sprite_sheet(&kakashi->clip[0], 0, 0, 50, len);
	cut_sprite_sheet(&kakashi->clip[1], 60, 0, 50, len);
	cut_sprite_sheet(&kakashi->clip[2], 120, 0, 50, len);
	cut_sprite_sheet(&kakashi->clip[3], 180, 0, 50, len);
}

void	cut_sheets2(t_sprite *lee, t_sprite *orochimaru)
{
	int len;

	len = lee->img->h;
	cut_sprite_sheet(&lee->clip[0], 0, 0, 40, len);
	cut_sprite_sheet(&lee->clip[1], 46, 0, 40, len);
	cut_sprite_sheet(&lee->clip[2], 93, 0, 40, len);
	cut_sprite_sheet(&lee->clip[3], 139, 0, 40, len);
	len = orochimaru->img->h;
	cut_sprite_sheet(&orochimaru->clip[0], 0, 0, 40, len);
	cut_sprite_sheet(&orochimaru->clip[1], 42, 0, 40, len);
	cut_sprite_sheet(&orochimaru->clip[2], 89, 0, 40, len);
	cut_sprite_sheet(&orochimaru->clip[3], 135, 0, 40, len);
}
