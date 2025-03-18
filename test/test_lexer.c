#include "minishell.h"

int main(void)
{
    const char *input = "echo \"hello world\" | grep hi >> output.txt";
    t_token *tokens = tokenise(input);

    while (tokens)
    {
        printf("Token: [%s] Type: %d\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
    return 0;
}