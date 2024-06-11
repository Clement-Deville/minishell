#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


// Function to update the prompt
void update_prompt(const char *new_prompt) {
    rl_message("%s", new_prompt);
    rl_on_new_line();
    rl_redisplay();
}

int main() {
    char *input;

    // Initial prompt
    rl_message("Initial Prompt> ");
    rl_redisplay();

    while ((input = readline("")) != NULL) {
        if (strcmp(input, "change") == 0) {
            // Update the prompt to a new value
            update_prompt("New Prompt> ");
        }
        // Handle input and add to history
        if (*input) {
            add_history(input);
        }
        free(input);
    }

    return 0;
}
