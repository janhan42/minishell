/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:06:45 by janhan            #+#    #+#             */
/*   Updated: 2024/03/01 19:52:47 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_putaddress(int *out_count, size_t address, int *flag)
{
	char	*lowhex;
	char	c;

	if (address <= 0 || *flag == ERROR)
		return ;
	lowhex = "0123456789abcdef";
	ft_putaddress(out_count, address / 16, flag);
	c = lowhex[address % 16];
	if (write(1, &c, 1) == -1)
		*flag = ERROR;
	else
		*out_count += 1;
}

void	ft_print_address(va_list *out_ap, int *out_count, int *flag)
{
	size_t	address;

	address = (size_t)va_arg(*out_ap, void *);
	if (address == 0)
	{
		if (write(1, "0x0", 3) == -1)
			*flag = ERROR;
		else
			*out_count += 3;
		return ;
	}
	else
	{
		if (write(1, "0x", 2) == -1)
			*flag = ERROR;
		else
		{
			*out_count += 2;
			ft_putaddress(out_count, address, flag);
		}
	}
}
