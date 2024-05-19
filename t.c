/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:04:49 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/17 14:04:51 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  for > i need to open with the flags O_WRONLY | O_CREAT | O_TRUNC
  for >> i need to open with the flags O_WRONLY | O_CREAT | O_APPEND
  for << its a herdoc
  for < i just need to open the file
*/
