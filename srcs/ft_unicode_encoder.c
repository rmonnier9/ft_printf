/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode_encoder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:29:51 by rmonnier          #+#    #+#             */
/*   Updated: 2016/12/01 18:39:33 by rmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *ft_unicode_string_encoder(wchar_t *unicode_str)
{
	char		*encoding;
	char		*to_add;
	char		*tmp;

	encoding = ft_strdup("");
	while (*unicode_str)
	{
		to_add = ft_unicode_encoder((wint_t)(*unicode_str));
		tmp = encoding;
		encoding = ft_strjoin(encoding, to_add);
		free(to_add);
		free(tmp);
		unicode_str++;
	}
	return (encoding);
}

char *ft_unicode_encoder(wint_t unicode)
{
	char *encoding;

	encoding = (char*)ft_strnew(5);
	if (unicode <= 127)
		encoding[0] = unicode;
	else if (unicode <= 2047)
	{
		encoding[0] = (192 | (unicode & 1984) >> 6);
		encoding[1] = (128 | (unicode & 63));
	}
	else if (unicode <= 65535)
	{
		encoding[0] = (224 | (unicode >> 12));
		encoding[1] = (128 | ((unicode >> 6) & 63));
		encoding[2] = (128 | (unicode & 63));
	}
	else if (unicode <= 1114111)
	{
		encoding[0] = (240 | (unicode >> 18));
		encoding[1] = (128 | ((unicode >> 12) & 63));
		encoding[2] = (128 | ((unicode >> 6) & 63));
		encoding[3] = (128 | (unicode & 63));
	}
	return (encoding);
}