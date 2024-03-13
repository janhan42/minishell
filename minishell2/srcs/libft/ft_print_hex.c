/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:09:11 by janhan            #+#    #+#             */
/*   Updated: 2024/03/01 19:52:46 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_putup_alt(va_list *out_ap, int *out_count,
unsigned int num, int *flag)
{
	char	*uphex;
	char	c;

	if (num <= 0 || *flag == ERROR)
		return ;
	uphex = "0123456789ABCDEF";
	ft_putup_alt(out_ap, out_count, num / 16, flag);
	c = uphex[num % 16];
	if (*flag == ERROR)
		return ;
	if (write(1, &c, 1) == -1)
		*flag = ERROR;
	else
		*out_count += 1;
}

static void	ft_putlow_alt(va_list *out_ap,
int *out_count, unsigned int num, int *flag)
{
	char	*lowhex;
	char	c;

	if (num <= 0)
		return ;
	lowhex = "0123456789abcdef";
	ft_putlow_alt(out_ap, out_count, num / 16, flag);
	c = lowhex[num % 16];
	if (*flag == ERROR)
		return ;
	if (write(1, &c, 1) == -1)
		*flag = ERROR;
	else
		*out_count += 1;
}

void	ft_print_hex(va_list *out_ap, int *out_count,
const char type, int *flag)
{
	unsigned int	num;

	num = va_arg(*out_ap, unsigned int);
	if (num == 0)
	{
		*out_count += write(1, "0", 1);
		return ;
	}
	if (type == 'x')
		ft_putlow_alt(out_ap, out_count, num, flag);
	else if (type == 'X')
		ft_putup_alt(out_ap, out_count, num, flag);
}
