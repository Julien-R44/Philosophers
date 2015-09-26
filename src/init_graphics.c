/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 22:08:38 by y0ja              #+#    #+#             */
/*   Updated: 2015/09/26 04:01:55 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void		init_sdl_ttf(t_all *all)
{
	if (TTF_Init() == -1)
		ft_error(SYSCALL);
	all->text.font = TTF_OpenFont("./img/font.ttf", 15);
	if (!all->text.font)
		ft_error(FONT_ERR);
	all->text.color.r = 255;
	all->text.color.g = 255;
	all->text.color.b = 255;
}

static void	loadBackground(SDL_Surface *bg[8])
{
	char	str[] = "./img/bg/frame_0.gif";
	int		i;

	i = -1;
	while (str[15] != '7')
	{
		if (!(bg[++i] = IMG_Load(str)))
			ft_error(IMG_LOAD);
		str[15] += 1;
	}
}

static void		set_transparency(SDL_Surface *img, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format, r, g, b));
}

t_sprite	load_a_sprite(char *filename, char *healthbar, int posx, int posy)
{
	t_sprite	sprite;

	// Sprite Sheet
	sprite.img = SDL_LoadBMP(filename);
	if (sprite.img == NULL)
		ft_error(IMG_LOAD);
	// HealthBar
	sprite.bar = SDL_LoadBMP(healthbar);
	if (sprite.bar == NULL)
		ft_error(IMG_LOAD);
	sprite.pos.x = posx;
	sprite.pos.y = posy;
	return (sprite);
}

t_sprite	*loadSprites(void)
{
	t_sprite	*sprites;
	char		*array[] = {
		"./img/anim/standingNaruto.bmp", "./img/header/Hnaruto.bmp",
		"./img/anim/standingSasuke.bmp", "./img/header/Hsasuke.bmp",
		"./img/anim/standingSakura2.bmp", "./img/header/Hsakura.bmp",
		"./img/anim/standingKakashi.bmp", "./img/header/Hkakashi.bmp",
		"./img/anim/standingKankuro.bmp", "./img/header/Hneji.bmp",
		"./img/anim/standingLee.bmp", "./img/header/Hlee.bmp",
		"./img/anim/standingOrochimaru.bmp", "./img/header/Horochimaru.bmp", NULL
	};
	int			pos[] = {
		40, 205, // Naruto
		90, 205, // Sasuke
		120, 194, // Sakura
		190, 205, // Kakashi
		390, 202, // Kankuro
		450, 208, // Lee
		350, 190 // Orochimaru
	};
	int			i;
	int			j;

	j = -1;
	i = 0;
	sprites = (t_sprite *)malloc(sizeof(t_sprite) * 7);
	if (sprites == NULL)
		ft_error(SYSCALL);
	while (array[i] != NULL)
	{
		sprites[++j] = load_a_sprite(array[i], array[i+1], pos[i], pos[i+1]);
		set_transparency(sprites[j].img, 144, 176, 216);
		set_transparency(sprites[j].bar, 144, 176, 216);
		i += 2;
	}
	return (sprites);
}

void	init_graphics(t_all *all)
{
	all->win = init_window();
	init_sdl_ttf(all);
	loadBackground(all->bg);
	// Load Sprites & Items
	all->sprites = loadSprites();
	all->heal = SDL_LoadBMP("./img/heal.bmp");
	if (!all->heal)
		ft_error(IMG_LOAD);
	set_transparency(all->heal, 144, 176, 216);
	// Cut Sprites Sheets
	cut_sheets(&all->sprites[0], &all->sprites[1], &all->sprites[2], &all->sprites[3], &all->sprites[4]);
	cut_sheets2(&all->sprites[5], &all->sprites[6]);
	// Health Bar
	all->rect_bar = SDL_CreateRGBSurface(SDL_HWSURFACE, 40, 4, 32, 0, 0, 0, 0);
	SDL_FillRect(all->rect_bar, NULL, SDL_MapRGB(all->win->format, 241, 6, 60));
}
