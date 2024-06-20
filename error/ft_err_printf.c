#include "../include/error.h"

void	err_handle_c_to_p(va_list ap, const char *str, unsigned int *i_p,
		int *num_of_bytes_p)
{
	int	return_tmp;

	if (str[*i_p + 1] == 'c')
	{
		return_tmp = err_if_char(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 's')
	{
		return_tmp = err_if_char_p(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 'p')
	{
		return_tmp = err_if_void_p(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
}

void	err_handle_d_to_u(va_list ap, const char *str, unsigned int *i_p,
		int *num_of_bytes_p)
{
	int	return_tmp;

	if (str[*i_p + 1] == 'd' || str[*i_p + 1] == 'i')
	{
		return_tmp = err_if_decimal(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 'u')
	{
		return_tmp = err_if_unsigned_decimal(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
}

void	err_handle_x_to_per(va_list ap, const char *str, unsigned int *i_p,
		int *num_of_bytes_p)
{
	int	return_tmp;

	if (str[*i_p + 1] == 'x')
	{
		return_tmp = err_if_hexadec_low(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 'X')
	{
		return_tmp = err_if_hexadec_up(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == '%')
	{
		if (write(2, "%", 1) < 0)
			*num_of_bytes_p = -1;
		else
			(*num_of_bytes_p)++;
	}
}

int	ft_err_printf(const char *str, ...)
{
	va_list			ap;
	unsigned int	i;
	int				num_of_bytes;

	va_start(ap, str);
	i = 0;
	num_of_bytes = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			err_handle_c_to_p(ap, str, &i, &num_of_bytes);
			err_handle_d_to_u(ap, str, &i, &num_of_bytes);
			err_handle_x_to_per(ap, str, &i, &num_of_bytes);
			i++;
		}
		else
			num_of_bytes += 1 * write(2, &str[i], 1);
		if (num_of_bytes < 0)
			return (num_of_bytes);
		i++;
	}
	va_end(ap);
	return (num_of_bytes);
}
