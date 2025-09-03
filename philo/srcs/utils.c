/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:17:02 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/03 20:40:18 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_error(const char *msg)
{
	printf(RED"%s\n"RESET, msg);
	exit(EXIT_FAILURE);
}

static const char	*is_valid(const char *str)
{
	int			len;
	const char	*nb;

	len = 0;
	while(ft_isspace(*str))
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
		print_error("error : Only numbers");
	if (nb > INT_MAX)
		print_error("error : value too big");
	return (nb);
}
