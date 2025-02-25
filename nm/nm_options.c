/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:20:29 by asenat            #+#    #+#             */
/*   Updated: 2018/10/16 13:57:39 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm/nm.h"

#include "libft/string/string.h"
#include "libft/output/output.h"
#include <unistd.h>

static void	unknown_cmd(const char *cmd)
{
	ft_putstr_fd("Unknown command line argument '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("'.\n", STDERR_FILENO);
	ft_putstr_fd("Usage: ./ft_nm -uUrpj [FILE ...]\n", STDERR_FILENO);
}

t_opt		nm_opt_parser(t_opt curr_opt, const char *arg)
{
	t_opt ret;

	ret = 0;
	(void)curr_opt;
	if (!ft_strcmp(arg, "-r"))
		ret += OPT_REVERSE;
	else if (!ft_strcmp(arg, "-p"))
		ret += OPT_NO_SORT;
	else if (!ft_strcmp(arg, "-u"))
		ret += OPT_ONLY_UNDF + OPT_JUST_SYM;
	else if (!ft_strcmp(arg, "-U"))
		ret += OPT_NO_UNDF;
	else if (!ft_strcmp(arg, "-j"))
		ret += OPT_JUST_SYM;
	else if (arg[0] == '-')
	{
		unknown_cmd(arg);
		return (-1);
	}
	return (ret);
}
