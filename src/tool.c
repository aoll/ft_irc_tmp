/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 23:03:21 by alex              #+#    #+#             */
/*   Updated: 2017/11/27 23:03:32 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int	x_int(int err, int res, char *str, char *file, int line)
{
  if (res == err)
    {
      fprintf(stderr, "%s error (%s, %d): %s\n",
	      str, file, line, strerror(errno));
      exit (1);
    }
  return (res);
}

void	*x_void(void *err, void *res, char *str, char *file, int line)
{
  if (res == err)
    {
      fprintf(stderr, "%s error (%s, %d): %s\n",
	      str, file, line, strerror(errno));
      exit (1);
    }
  return (res);
}
