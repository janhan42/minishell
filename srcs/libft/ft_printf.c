/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:37:19 by janhan            #+#    #+#             */
/*   Updated: 2024/03/01 19:52:47 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_print_format(const char format,
va_list *out_ap, int *out_count, int *flag)
{
	if (format == 'c')
		ft_print_char(out_ap, out_count, flag);
	else if (format == 's')
		ft_print_str(out_ap, out_count, flag);
	else if (format == 'd' || format == 'i')
		ft_print_di(out_ap, out_count, flag);
	else if (format == 'x' || format == 'X')
		ft_print_hex(out_ap, out_count, format, flag);
	else if (format == 'p')
		ft_print_address(out_ap, out_count, flag);
	else if (format == 'u')
		ft_print_u(out_ap, out_count, flag);
	else if (format == '%')
	{
		if ((write(1, "%", 1)) == -1)
			*flag = ERROR;
		else
			*out_count += 1;
	}
}

static void	ft_parse_type(const char *format,
va_list *out_ap, int *out_count, int *flag)
{
	size_t	i;

	i = 0;
	while (format[i] != '\0' && *flag != ERROR)
	{
		if (format[i] == '%')
		{
			++i;
			ft_print_format(format[i], out_ap, out_count, flag);
		}
		else
		{
			if ((write(1, &format[i], 1)) == -1)
				*flag = 1;
			else
				*out_count += 1;
		}
		++i;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		flag;

	flag = 0;
	count = 0;
	va_start(ap, format);
	ft_parse_type(format, &ap, &count, &flag);
	va_end(ap);
	if (flag == ERROR)
		return (-1);
	else
		return (count);
}
