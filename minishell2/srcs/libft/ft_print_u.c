/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:31:13 by janhan            #+#    #+#             */
/*   Updated: 2024/03/01 19:52:47 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_putnbr_u(unsigned int num, int *out_count, int *flag)
{
	char	c;

	if (num <= 0 || *flag == ERROR)
		return ;
	ft_putnbr_u(num / 10, out_count, flag);
	c = num % 10 + '0';
	if (*flag == ERROR)
		return ;
	if (write(1, &c, 1) == -1)
		*flag = ERROR;
	else
		*out_count += 1;
}

void	ft_print_u(va_list *out_ap, int *out_count, int *flag)
{
	unsigned int	num;

	num = va_arg(*out_ap, unsigned int);
	if (num == 0)
	{
		if (write(1, "0", 1) == -1)
			*flag = ERROR;
		else
			*out_count += 1;
		return ;
	}
	ft_putnbr_u(num, out_count, flag);
}
