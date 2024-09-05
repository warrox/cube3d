/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:24:01 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 15:09:21 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	error_split_sett(t_data *data)
{
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	free(data->file);
	error_msg("Fail to allocate memory for split_settings!");
}

void	error_order(t_data *data)
{
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	free(data->file);
	error_msg("Wrong order!");
}