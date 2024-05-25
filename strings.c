/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:53:50 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/25 21:51:51 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len;
	char	*ptr;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(ft_strlen(str) + 1);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < len)
	{
		if (s1[i] != s2[i])
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	r;
	int	i;
	int	s;

	r = 0;
	i = 0;
	s = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * s);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

int	ft_strnstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && (str[i + j] == to_find[j]))
			j++;
		if (to_find[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcpy(char *dest, char *src)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen((char *)src);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

t_cmd	*new_list(void *cmd)
{
	t_cmd	*ptr;

	ptr = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ptr)
		return (NULL);
	ptr->cmd = cmd;
	ptr->next = NULL;
	return (ptr);
}

char	*nops_strdup(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (str[i] == ' ')
		i++;
	ptr = (char *)malloc(ft_strlen(str) + 2 - i);
	if (!ptr)
		return (NULL);
	j = 0;
	while (str[i])
	{
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
