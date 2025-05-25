/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:56:35 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/25 21:02:11 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define I32_MAX "2147483647"
#define I32_MAX_LEN 10

#define I32_MIN "2147483648"
#define I32_MIN_LEN 10

int	is_less_max_i32(char *text)
{
	int	i;

	i = 0;
	while ('\0' != text[i])
		i++;
	if (i < I32_MAX_LEN)
		return (1);
	if (i > I32_MAX_LEN)
		return (0);
	i = 0;
	while (i < I32_MAX_LEN)
	{
		if (text[i] > I32_MAX[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_greater_min_i32(char *text)
{
	int	i;

	i = 0;
	while ('\0' != text[i])
		i++;
	if (i < I32_MIN_LEN)
		return (1);
	if (i > I32_MIN_LEN)
		return (0);
	i = 0;
	while (i < I32_MIN_LEN)
	{
		if (text[i] > I32_MIN[i])
			return (0);
		i++;
	}
	return (1);
}

int	does_fit_in_int(char *text)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if ('-' == text[i])
	{
		i++;
		sign = -1;
	}
	else if ('+' == text[i])
		i++;
	while ('0' == text[i] && '\0' != text[i + 1])
		i++;
	if (sign == -1)
		return (is_greater_min_i32(&text[i]));
	return (is_less_max_i32(&text[i]));
}

int	is_int(char *text)
{
	int	i;

	i = 0;
	if (('-' == text[i] || '+' == text[i]) && '\0' != text[i + 1])
		i++;
	while ('0' <= text[i] && text[i] <= '9')
		i++;
	if ('\0' != text[i])
		return (0);
	return (does_fit_in_int(text));
}

int	ft_atoi(char *text, int *res)
{
	int	i;
	int	sign;

	if (!is_int(text))
		return (1);
	*res = 0;
	sign = 1;
	i = 0;
	if ('+' == text[i])
		i++;
	else if ('-' == text[i])
	{
		i++;
		sign = -1;
	}
	while ('\0' != text[i])
	{
		if (-1 == sign)
			*res = (*res) * 10 - (text[i] - '0');
		else
			*res = (*res) * 10 + (text[i] - '0');
		i++;
	}
	return (0);
}
