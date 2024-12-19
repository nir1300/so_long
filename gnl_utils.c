// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   gnl_utils.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/04 19:06:17 by nrumpfhu          #+#    #+#             */
// /*   Updated: 2024/12/10 14:58:08 by nrumpfhu         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "so_long.h"


// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		n;
// 	char	*new;

// 	n = 0;
// 	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	i = 0;
// 	if (new != NULL)
// 	{
// 		while (s1[n])
// 			new[i++] = s1[n++];
// 		n = 0;
// 		while (s2[n])
// 			new[i++] = s2[n++];
// 		new[i] = '\0';
// 		return (new);
// 	}
// 	return (NULL);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

// char	*ft_strdup(const char *s)
// {
// 	int		i;
// 	char	*new;

// 	new = (char *)malloc(ft_strlen((char *)s) + 1);
// 	if (new == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		new[i] = s[i];
// 		i++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }
