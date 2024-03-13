/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:00:25 by janhan            #+#    #+#             */
/*   Updated: 2024/03/01 19:52:47 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_printf_pointer(void *arg, char type, int *res)
{
	if (type == 's')
		ft_print_s((char *)arg, res);
	else if (type == 'p')
		ft_print_p(arg, res);
}

static void	ft_printf_unsinged_int(unsigned int arg, char type, int *res)
{
	if (type == 'x' || type == 'X')
		ft_print_x(arg, type, res);
	else if (type == 'u')
		ft_print_u(arg, res);
}

static void	ft_printf_int(int arg, char type, int *res)
{
	if (type == 'c')
		ft_print_c(arg, res);
	else if (type == 'd' || type == 'i')
		ft_print_di(arg, res);
}

static int	ft_print(va_list va, const char *format, int res)
{
	int	i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c' || format[i] == 'd' || format[i] == 'i')
				ft_print_int(va_arg(va, int), format[i], &res);
			else if (format[i] == 'x' || format[i] == 'X' || format[i] == 'u')
				ft_print_u(va_arg(va, unsigned), format[i], &res);
			else if (format[i] == 's' || format[i] == 'p')
				ft_print_pointer(va_arg(va, void *), format[i], &res);
			else if (format[i] == '%')
				ft_print_char('%', &res);
			else
				return (-1);
		}
	}
}

int	ft_printf_err(const char *format, ...)
{
	va_list	va;
	int		res;

	va_start(va, format);
	res = ft_print(va, format, 0);
	va_end(va);
	return (res);
}
