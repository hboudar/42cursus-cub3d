/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .print_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:08:59 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/29 15:13:54 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_file(t_cube *cube)
{
	int i;

	i = 0;
	while (cube->file[i])
	{
		printf("%s\n", cube->file[i]);
		i++;
	}
	printf("North : %s\n", cube->texture.north);
	printf("South : %s\n", cube->texture.south);
	printf("West : %s\n", cube->texture.west);
	printf("East : %s\n", cube->texture.east);
	
	
}
