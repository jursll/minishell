/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/11 15:02:35 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtin.h"

t_builtin g_builtin[] = {
//	{"echo", &builtin_echo},
	{"cd", &builtin_cd},
	{"pwd", &builtin_pwd},
	{"export", &builtin_export},
//	{"unset", &builtin_unset},
	{"env", &builtin_env},
//	{"exit", &builtin_exit},
	{NULL, NULL}					// Marks the end of the array
};
