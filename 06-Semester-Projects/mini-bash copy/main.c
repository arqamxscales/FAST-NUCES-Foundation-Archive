#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[]) (char **) = {&shell_cd, &shell_help, &shell_exit};

int shell_num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mini-bash: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("mini-bash");
        }
    }
    return 1;
}

int shell_help(char **args) {
    (void)args; // Fixes unused parameter warning
    printf("Mini-Bash\nType program names and arguments, and hit enter.\n");
    printf("Built-in commands: cd, help, exit\n");
    return 1;
}

int shell_exit(char **args) {
    (void)args; // Fixes unused parameter warning
    return 0;
}

int shell_launch(char **args) {
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("mini-bash");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("mini-bash");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int shell_execute(char **args) {
    if (args[0] == NULL) { return 1; }
    for (int i = 0; i < shell_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return shell_launch(args);
}

char *shell_read_line(void) {
    char *line = NULL;
    size_t bufsize = 0; // Changed to size_t to fix pointer sign warning
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

char **shell_split_line(char *line) {
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    if (!tokens) { exit(EXIT_FAILURE); }
    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void shell_loop(void) {
    char *line;
    char **args;
    int status;
    do {
        printf("mini-bash> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);
        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    (void)argc; // Fixes unused parameter warning
    (void)argv; // Fixes unused parameter warning
    shell_loop();
    return EXIT_SUCCESS;
}
