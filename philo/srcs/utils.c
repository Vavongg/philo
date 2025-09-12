/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:17:02 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/12 11:11:54 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*is_valid(const char *str)
{
	int			len;
	const char	*nb;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		print_error("error : only positive value");
	if (!ft_isdigit(*str))
		print_error("error : wrong input");
	nb = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		print_error("error : value too big");
	return (nb);
}

long	ft_atol(const char *str)
{
	long	nb;

	nb = 0;
	str = is_valid(str);
	while (ft_isdigit(*str))
		nb = (nb * 10) + (*str++ - 48);
	if (*str != '\0')
		print_error("error : wrong input");
	if (nb > INT_MAX)
		print_error("error : value too big");
	return (nb);
}
