/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:51 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/18 02:31:17 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	create_thread(t_dlist *list)
{
	t_dlist *nav;
	t_philo	*philo;

	nav = list;
	while (nav)
	{
		philo = nav->content;
		if (pthread_create(&philo->th, NULL, func_th, ft_itoa(philo->name)) != 0)
			ft_error(PTHREAD_CREATE);
		nav = nav->next;
	}
}

t_dlist	*init_philo_list(void)
{
	t_dlist		*list;
	t_philo		philo;

	list = NULL;
	philo.name = 0;
	philo.life = MAX_LIFE;
	philo.statut = 0;
	philo.stick = 1;
	while (philo.name < 7)
	{
		if (pthread_mutex_init(&philo.mutex_stick, NULL) != 0)
			ft_error(PTHREAD_MUTEX_INIT);
		ft_dlstadd_end(&list, ft_dlstnew(&philo, sizeof(t_philo)));
		philo.name += 1;
	}
	return (list);
}

void	ft_hungry(t_dlist *list)
{
	t_dlist	*nav;
	t_philo *philo;

	nav = list;
	philo = nav->content;
	while (philo->statut != DEAD)
	{
		usleep(SEC / 7);
		if (philo->statut != EATING)
			philo->life--;
		if (philo->life < 1)
			philo->statut = DEAD;
		if (philo->statut != DEAD)
		{
			nav = nav->next == NULL ? list : nav->next;
			philo = nav->content;
		}
	}
}

/* GLOBALES */
GLuint wood_texture;
int angleX = 0;
int angleZ = 0;
int angleY = 0;

void	draw_cube(t_win *win, int angleZ, int angleX)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(3, 4, 2, 0, 0, 0, 0, 0, 1);

	glRotated(angleZ,0,0,1);
	glRotated(angleY,0,1,0);
	glRotated(angleX,1,0,0);

	glBegin(GL_QUADS);

	glColor3ub(255,0,0); //face rouge
	glVertex3d(1,1,TABLE_HEIGHT);
	glVertex3d(1,1,TABLE_BASE);
	glVertex3d(-1,1,TABLE_BASE);
	glVertex3d(-1,1,TABLE_HEIGHT);

	glColor3ub(0,255,0); //face verte
	glVertex3d(1,-1,TABLE_HEIGHT);
	glVertex3d(1,-1,TABLE_BASE);
	glVertex3d(1,1,TABLE_BASE);
	glVertex3d(1,1,TABLE_HEIGHT);

	glColor3ub(0,0,255); //face bleue
	glVertex3d(-1,-1,TABLE_HEIGHT);
	glVertex3d(-1,-1,TABLE_BASE);
	glVertex3d(1,-1,TABLE_BASE);
	glVertex3d(1,-1,TABLE_HEIGHT);

	glColor3ub(255,255,0); //face jaune
	glVertex3d(-1,1,TABLE_HEIGHT);
	glVertex3d(-1,1,TABLE_BASE);
	glVertex3d(-1,-1,TABLE_BASE);
	glVertex3d(-1,-1,TABLE_HEIGHT);

	glColor3ub(0,255,255); //face cyan
	glVertex3d(1,1,TABLE_BASE);
	glVertex3d(1,-1,TABLE_BASE);
	glVertex3d(-1,-1,TABLE_BASE);
	glVertex3d(-1,1,TABLE_BASE);

	glColor3ub(255,0,255); //face magenta
	glVertex3d(1,-1,TABLE_HEIGHT);
	glVertex3d(1,1,TABLE_HEIGHT);
	glVertex3d(-1,1,TABLE_HEIGHT);
	glVertex3d(-1,-1,TABLE_HEIGHT);

	glEnd();

	glFlush();
}

void	draw_floor(t_win *win)
{
	// glutSolidCube(1);
	glBegin(GL_QUADS);

	glColor3ub(0, 255, 255);
	glVertex3d(10, -10, -1);
	glVertex3d(-10, -10, -1);
	glVertex3d(-10, 10, -1);
	glVertex3d(10, 10, -1);

	glEnd();
	glFlush();
	glfwSwapBuffers(win->ptr);
}

GLuint LoadTexture( const char * filename ) {
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;
	file = fopen( filename, "rb" );
	if ( file == NULL )
		return 0;
	width = 1024;
	height = 512;
	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, width * height * 3, 1, file );
	fclose( file );
	for (int i = 0; i < width * height ; ++i) {
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];
		data[index] = R;
		data[index+2] = B;
	}
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );

	return texture;
}

void	rotate_callback(int x, int y)
{
	printf("x = [%d], y = [%d]\n", x,y);
}

void	key_hook(t_win *win)
{
	glfwPollEvents();
	if (glfwGetKey(win->ptr, GLFW_KEY_LEFT) == GLFW_PRESS)
		angleX += 1.5;
	if (glfwGetKey(win->ptr, GLFW_KEY_RIGHT) == GLFW_PRESS)
		angleX -= 1.5;
	if (glfwGetKey(win->ptr, GLFW_KEY_UP) == GLFW_PRESS)
		angleY += 1.5;
}

int main(int ac, char **av)
{
	t_dlist		*list;
	pthread_t	time_th;
	t_win		win;


	// list = init_philo_list();
	// ft_global(list);
	// create_thread(list);
	// if ((pthread_create(&time_th, NULL, time_func, list)) != 0)
	// 	ft_putstr("err\n");
	// ft_hungry(list);
	// pthread_join(time_th, NULL);

	// Init OpenGL
	win.ptr = init_window();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110, (double)WIDTH/HEIGHT, 1, 1000);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	// Load Textures
	// wood_texture = LoadTexture("./img/bricks.bmp");
	// glBindTexture(GL_TEXTURE_2D, wood_texture);
	/* Cameras bruh */
	glutPassiveMotionFunc(&rotate_callback);

	while (!glfwWindowShouldClose(win.ptr))
	{
		// angleZ += 1.0;
		angleX += 1.5;
		draw_cube(&win, angleX, angleZ);
		draw_floor(&win);
		key_hook(&win);
	}
	glfwDestroyWindow(win.ptr);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return (0);
}
