#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TOKEN_BUFFER_SIZE 1024
#define SPECIAL_CHARS "|<>"

char    **add_token(char **tokens, int *count, const char *token)
{
    tokens = realloc(tokens, sizeof(char *) * (*count + 1));
    if (!tokens)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    tokens[*count] = strdup(token);
    if (!tokens[*count])
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    (*count)++;
    return (tokens);
}

const char    *get_env_value(const char *var)
{
    const char  *value;

    value = getenv(var);
    return (value ? value : "");
}

void    handle_env_var(char *token_buffer, int *token_idx, const char *input,
        int *i)
{
    char    var_name[TOKEN_BUFFER_SIZE];
    int     var_idx;

    var_idx = 0;
    (*i)++;  /* Skip the '$' character */
    if (input[*i] == '?')
    {
        /* Handle special parameter '$?' */
        const char *exit_status = "0"; /* Replace with actual exit status */
        strcpy(&token_buffer[*token_idx], exit_status);
        *token_idx += strlen(exit_status);
        (*i)++;
        return ;
    }
    while (isalnum(input[*i]) || input[*i] == '_')
    {
        var_name[var_idx++] = input[*i];
        (*i)++;
    }
    var_name[var_idx] = '\0';
    {
        const char  *value = get_env_value(var_name);
        strcpy(&token_buffer[*token_idx], value);
        *token_idx += strlen(value);
    }
}

char    **lexer(const char *input, int *num_tokens)
{
    char    **tokens;
    int     length;
    char    token_buffer[TOKEN_BUFFER_SIZE];
    int     token_idx;
    int     i;
    char    c;

    tokens = NULL;
    *num_tokens = 0;
    length = (int)strlen(input);
    token_idx = 0;
    i = 0;
    while (i < length)
    {
        c = input[i];
        if (isspace(c))
        {
            if (token_idx > 0)
            {
                token_buffer[token_idx] = '\0';
                tokens = add_token(tokens, num_tokens, token_buffer);
                token_idx = 0;
            }
            i++;
            continue ;
        }
        if (c == '\"' || c == '\'')
        {
            {
                char    quote;

                quote = c;
                i++; /* Skip opening quote */
                while (i < length && input[i] != quote)
                {
                    if (token_idx >= TOKEN_BUFFER_SIZE - 1)
                    {
                        fprintf(stderr, "Error: token buffer overflow.\n");
                        exit(EXIT_FAILURE);
                    }
                    token_buffer[token_idx++] = input[i++];
                }
                if (i >= length || input[i] != quote)
                {
                    fprintf(stderr, "Error: unclosed quote detected.\n");
                    exit(EXIT_FAILURE);
                }
                i++; /* Skip closing quote */
            }
            continue ;
        }
        if (strchr(SPECIAL_CHARS, c))
        {
            if (token_idx > 0)
            {
                token_buffer[token_idx] = '\0';
                tokens = add_token(tokens, num_tokens, token_buffer);
                token_idx = 0;
            }
            {
                char special_token[3] = {0};

                special_token[0] = c;
                if ((c == '>' || c == '<') && (i + 1 < length) &&
                    input[i + 1] == c)
                {
                    special_token[1] = c;
                    special_token[2] = '\0';
                    i += 2;
                }
                else
                {
                    special_token[1] = '\0';
                    i++;
                }
                tokens = add_token(tokens, num_tokens, special_token);
            }
            continue ;
        }
        if (c == '$')
        {
            handle_env_var(token_buffer, &token_idx, input, &i);
            continue ;
        }
        if (c == '\\')
        {
            /* Minimal escape processing: skip backslash and add next char */
            if (i + 1 < length)
            {
                i++;
                c = input[i];
            }
        }
        if (token_idx >= TOKEN_BUFFER_SIZE - 1)
        {
            fprintf(stderr, "Error: token buffer overflow.\n");
            exit(EXIT_FAILURE);
        }
        token_buffer[token_idx++] = c;
        i++;
    }
    if (token_idx > 0)
    {
        token_buffer[token_idx] = '\0';
        tokens = add_token(tokens, num_tokens, token_buffer);
    }
    return (tokens);
}

#ifdef TEST_LEXER
int main(void)
{
    const char  *tests[] = {
        "echo \"hello world\" > output.txt | cat -e",
        "ls>file.txt",               /* adjacent tokens without spaces */
        "echo 'single quoted text'",  /* single quotes */
        "   ",                        /* whitespace only */
        /* "echo \"unclosed quote", */ /* unclosed quote (should error) */
        "echo \"cat lol.c | cat > lol.c\"",
        "echo $HOME",                /* environment variable */
        "echo $? > result.txt",      /* special parameter */
        "cat << EOF",                /* redirection with delimiter */
        "cat >> output.txt",         /* append redirection */
        "",                          /* empty input */
        "echo >>> file",             /* multiple consecutive special chars */
        "echo 'single' \\\"double\\\"",
        "echo \"$HOME\"",            /* env variable in quotes */
        "'cat | cat | ls'",
        "'cat file | grep bla | more'"
    };
    int         num_tests;
    int         t;
    int         count;
    char        **tokens;
    int         i;

    num_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    t = 0;
    while (t < num_tests)
    {
        printf("Test case %d: %s\n", t, tests[t]);
        count = 0;
        tokens = lexer(tests[t], &count);
        i = 0;
        while (i < count)
        {
            printf("  Token[%d]: %s\n", i, tokens[i]);
            free(tokens[i]);
            i++;
        }
        free(tokens);
        printf("\n");
        t++;
    }
    return (0);
}
#endif
