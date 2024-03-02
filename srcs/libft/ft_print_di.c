/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:53:27 by janhan            #+#    #+#             */
/*   Updated: 2024/03/01 19:52:47 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_putnum_recursive(unsigned int num, int *out_count, int *flag)
	{
	char	c;

	if (num <= 0 || *flag == ERROR)
		return ;
	ft_putnum_recursive(num / 10, out_count, flag);
	c = num % 10 + '0';
	if (*flag == ERROR)
		return ;
	if (write(1, &c, 1) == -1)
		*flag = ERROR;
	else
		*out_count += 1;
}

static void	ft_putnbr_alt(int n, int *out_count, int *flag)
{
	unsigned int	num;

	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			*flag = ERROR;
		else
		{
			*out_count += 1;
			n *= -1;
			num = (unsigned int)n;
		}
	}
	else if (n == 0)
	{
		if (write(1, "0", 1) == -1)
			*flag = ERROR;
		else
			*out_count += 1;
		return ;
	}
	else
		num = (unsigned int)n;
	if (*flag != ERROR)
		ft_putnum_recursive(num, out_count, flag);
}

void	ft_print_di(va_list *out_ap, int *out_count, int *flag)
{
	int	num;

	num = va_arg(*out_ap, int);
	if (num == INT32_MIN)
	{
		if (write(1, "-2147483648", 11) == -1)
		{
			*flag = ERROR;
			return ;
		}
		else
			*out_count += 11;
		return ;
	}
	ft_putnbr_alt(num, out_count, flag);
}
