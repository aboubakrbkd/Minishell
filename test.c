/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:14:46 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/20 15:33:14 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expand_and_execute(const char *command) {
    // Step 1: Tokenization (a very simplified version)
    char *tokens[100];  // assuming there won't be more than 100 tokens
    int token_count = 0;

    char *command_copy = strdup(command);
    char *token = strtok(command_copy, " ");
    while (token != NULL) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }
    tokens[token_count] = NULL;

    // Step 2: Variable Expansion
    for (int i = 0; i < token_count; i++) {
        if (tokens[i][0] == '$') {
            char *var_name = tokens[i] + 1;  // skip the $
            char *var_value = getenv(var_name);
            if (var_value != NULL) {
                tokens[i] = var_value;
            } else {
                tokens[i] = "";  // if the variable is not found, replace with an empty string
            }
        }
    }

    // Step 3: Command Execution (here we'll just print the final command)
    printf("Executing command: ");
    for (int i = 0; i < token_count; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");

    free(command_copy);
}

int main() {
    const char *command = "echo $USER $OLDPWD";
    expand_and_execute(command);
    return 0;
}


