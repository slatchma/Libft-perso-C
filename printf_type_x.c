/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   printf_type_x.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slatchma <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/05 17:50:39 by slatchma     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/12 00:19:14 by slatchma    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_conversion(t_modul *analyze, va_list ap)
{
	uintmax_t	recup;

	if (analyze->prefix == 'z')
		recup = (size_t)va_arg(ap, uintmax_t *);
	else if (analyze->prefix == 'j')
		recup = (uintmax_t)va_arg(ap, uintmax_t *);
	else if (analyze->prefix == 'L')
		recup = (unsigned long long)va_arg(ap, uintmax_t *);
	else if (analyze->prefix == 'l')
		recup = (unsigned long)va_arg(ap, uintmax_t *);
	else if (analyze->prefix == 'H')
		recup = (unsigned char)va_arg(ap, uintmax_t *);
	else if (analyze->prefix == 'h')
		recup = (unsigned short)va_arg(ap, uintmax_t *);
	else
		recup = (unsigned int)va_arg(ap, uintmax_t *);
	if (recup)
		analyze->testfree = 1;
	if ((analyze->prefix == 'l' && analyze->type == 'u') ||
		(analyze->type == 'X'))
		return (ft_itoa_base(recup, 16, "0123456789ABCDEF"));
	else
		return (ft_itoa_base(recup, 16, "0123456789abcdef"));
}

static void	ft_x_len(t_modul *analyze, int *len, char *str)
{
	if (analyze->precision < (int)ft_strlen(str) &&
		!(analyze->precision == 0 && str[0] == '0'))
		analyze->precision = (int)ft_strlen(str);
	if (analyze->flag_hast == 1 && str[0] != '0')
		analyze->precision = analyze->precision + 2;
	if (analyze->width < analyze->precision)
		analyze->width = analyze->precision;
	*len = analyze->width;
}

static void	ft_type_x_three(t_modul analyze, char *str, char *strout, int i)
{
	while (analyze.precision > 0)
	{
		strout[i] = '0';
		analyze.precision = analyze.precision - 1;
		i--;
	}
	if (analyze.flag_zero == 1)
		i = -1;
	if (analyze.flag_hast == 1 && str[0] != '0')
	{
		strout[i + 1] = '0';
		strout[i + 2] = 'x';
	}
	if (analyze.flag_hast == 1 && (analyze.prefix == 'l' ||
	analyze.type == 'X') && str[0] != '0')
		strout[i + 2] = 'X';
}

static int	ft_type_x_two(t_modul analyze, char *str, char *strout, int len)
{
	int i;
	int j;

	if (analyze.flag_neg == 1)
		i = analyze.precision;
	else
		i = len;
	j = ft_strlen(str) - 1;
	while (i-- && j >= 0 && analyze.precision != 0)
	{
		strout[i] = str[j];
		j--;
		analyze.precision = analyze.precision - 1;
	}
	ft_type_x_three(analyze, str, strout, i);
	ft_putstr(strout);
	return (ft_strlen(strout));
}

int			ft_type_x(t_modul analyze, va_list ap, char tampon[2096])
{
	char	*str;
	char	*strout;
	int		len;

	str = ft_conversion(&analyze, ap);
	ft_x_len(&analyze, &len, str);
	if ((strout = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	strout = ft_memset(strout, ' ', (size_t)len);
	strout[len] = '\0';
	if (analyze.flag_zero == 1)
		strout = ft_memset(strout, '0', (size_t)len);
	ft_putstr(tampon);
	len = ft_type_x_two(analyze, str, strout, len) + ft_strlen(tampon);
	free(strout);
	if (analyze.testfree == 1)
		free(str);
	return (len);
}
