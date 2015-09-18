/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 20:40:04 by jripoute          #+#    #+#             */
/*   Updated: 2015/09/17 22:19:17 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

static void			key_callback(GLFWwindow *window, int key, \
	int scancode, int action, int mod)
{
	(void)scancode;
	(void)mod;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow	*init_window(void)
{
	GLFWwindow *win;

	if (glfwInit() == GL_FALSE)
		exit(EXIT_FAILURE);
	if ((win = glfwCreateWindow(WIDTH, HEIGHT, "Philosophers", NULL, NULL)) == NULL)
		ft_error(CREATE_WINDOW);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	glfwSetKeyCallback(win, key_callback);
	return (win);
}

