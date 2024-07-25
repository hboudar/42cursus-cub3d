/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:42:13 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/25 18:27:25 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


int skip_space(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    return (i);
}
#include <stdio.h>
void    getelement2(char *str, int *flag)
{
    char    **line;

    line = ft_split(str + 1, ' ');
    int i = 0;
    while (line[i])
    {
        printf("%s\n", line[i]);
        i++;
    }
    *flag = *flag + 1;
}

char    *get_element(char *str, int *flag)
{
    int i;

    i = 2;
    while (str && str[i])
    {
        if (str[i] != ' ')
            break ;
        i++;
    }
    if (i == 2)
        return (NULL);
    *flag = *flag + 1;
    return (ft_strdup(str + i));
}
