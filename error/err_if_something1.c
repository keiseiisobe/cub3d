#include "../include/error.h"

int	err_if_char(va_list ap)
{
	int	arg;

	arg = va_arg(ap, int);
	return (write(2, &arg, 1));
}

int	err_if_char_p(va_list ap)
{
	unsigned int	i;
	char			*arg;

	arg = va_arg(ap, char *);
	if (arg == NULL)
	{
		if (write(2, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	i = 0;
	while (arg[i])
	{
		if (write(2, &arg[i], 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	err_if_void_p(va_list ap)
{
	uintptr_t	arg;
	int			count;
	int			*p;

	count = 0;
	p = &count;
	arg = (uintptr_t)va_arg(ap, void *);
	if (write(2, "0x", 2) < 0)
		return (-1);
	count += 2;
	count = ft_err_put_address(arg, p);
	return (count);
}

int	err_if_decimal(va_list ap)
{
	int	arg;
	int	count;
	int	*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, int);
	count = ft_err_put_int(arg, p);
	return (count);
}
