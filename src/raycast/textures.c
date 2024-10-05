/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 09:56:26 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 09:56:32 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	load_texture(t_data *data)
{
	data->no.img = mlx_xpm_file_to_image(data->mlx.p_mlx,
			data->file->path->path_no, &data->no.width, &data->no.height);
	data->no.addr = mlx_get_data_addr(data->no.img, &data->no.bpp,
			&data->no.line_lengh, &data->no.endian);
	if (!data->no.img)
		printf("Failed to load north texture\n");
	data->so.img = mlx_xpm_file_to_image(data->mlx.p_mlx,
			data->file->path->path_so, &data->so.width, &data->so.height);
	data->so.addr = mlx_get_data_addr(data->so.img, &data->so.bpp,
			&data->so.line_lengh, &data->so.endian);
	if (!data->so.img)
		printf("Failed to load south texture\n");
	data->ea.img = mlx_xpm_file_to_image(data->mlx.p_mlx,
			data->file->path->path_ea, &data->ea.width, &data->ea.height);
	data->ea.addr = mlx_get_data_addr(data->ea.img, &data->ea.bpp,
			&data->ea.line_lengh, &data->ea.endian);
	if (!data->ea.img)
		printf("Failed to load east texture\n");
	data->we.img = mlx_xpm_file_to_image(data->mlx.p_mlx,
			data->file->path->path_we, &data->we.width, &data->we.height);
	data->we.addr = mlx_get_data_addr(data->we.img, &data->we.bpp,
			&data->we.line_lengh, &data->we.endian);
	if (!data->we.img)
		printf("Failed to load west texture\n");
}
