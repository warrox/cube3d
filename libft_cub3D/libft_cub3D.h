/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_cub3D.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:56:22 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 12:17:26 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CUB3D_H
# define LIBFT_CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_itoa(int nbr);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int		ft_strlen(char *str);
char	*ft_strrchr(char *str, int searchedChar);
void	*ft_calloc(size_t nmeb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *haystack, char *needle);

int		ft_printf(const char *input, ...);
int		print_char(char c);
int		print_hexa(unsigned int nb, const char form);
int		print_int(int nb);
int		print_percent(void);
int		print_pointer(unsigned long long ptr);
int		print_string(char *str);
int		print_unsigned(unsigned int nb);

char	*get_next_line(int fd);
void	*gnl_calloc(size_t nmeb, size_t size);
char	*gnl_strjoin(char const *s1, char const *s2);
void	*gnl_memcpy(void *dest, const void *src, size_t n);
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(char *s, int c);

#endif