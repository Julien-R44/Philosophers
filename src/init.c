/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 20:40:04 by jripoute          #+#    #+#             */
/*   Updated: 2015/09/24 03:00:03 by y0ja             ###   ########.fr       */
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

