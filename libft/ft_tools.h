/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:49:16 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/12 00:17:14 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOOLS_H
# define FT_TOOLS_H

# include <stddef.h>

int		ft_atoi(const char *str);
int		ft_atoi_n(const char *str, size_t n);
int		ft_check_base(char *base);
int		ft_get_signed_nb_len(long nb, int base);
size_t	ft_abs(long nb);

#endif
