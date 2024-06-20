#include "../include/error.h"

int	err_if_unsigned_decimal(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_err_put_unsigned_int(arg, p);
	return (count);
}

int	err_if_hexadec_low(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_err_put_hexadec_low(arg, p);
	return (count);
}

int	err_if_hexadec_up(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_err_put_hexadec_up(arg, p);
	return (count);
}
