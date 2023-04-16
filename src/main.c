#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define BUFSIZE 1024

void prompt() {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    char cwd[PATH_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    getcwd(cwd, PATH_MAX);

    printf("\033[0;32m"); // set color to green
    printf("%s@%s ", username, hostname);
    printf("\033[0m"); // reset color

    printf("\033[0;35m"); // set color to blue
    printf("%s", cwd);
    printf("\033[0m"); // reset color

    printf(" » ");
}

char *read_line() {
    int bufsize = BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a char
        c = getchar();
        if (c == 0x0C) {
            system("clear");
            continue;
        }

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int cd(char *tokens[]) {
    if (tokens[1] == NULL) {
        chdir(getenv("HOME"));
    } else {
        if(chdir(tokens[1]) != 0) {
            perror("cd failed");
        }
    }
    return 0;
}

void int_handler(int dummy) {
}

int main(int argc, char** argv) {

    char *response;
    int status;
    pid_t pid;

    signal(SIGINT, int_handler);

    while (1) {
        prompt();

        response = read_line();

        if (strcmp(response, "exit") == 0) {
            printf("exit\n");
            return 0;
        }

        // Identify command type
        int token_count = 0;
        for (int i = 0; i < strlen(response); i++) {
            if (response[i] == ' ') {
                token_count++;
            }
        }

        int i = 0;
        char *p = strtok(response, " ");
        char *tokens[token_count+2];
        while (p != NULL) {
            tokens[i++] = p;
            p = strtok(NULL, " ");
        }
        tokens[token_count+1] = NULL;

        if (strcmp(tokens[0], "cd") == 0) {
            cd(tokens);
            continue;
        }

        // create the NEW process to run the command
        pid = fork();

        if (pid == 0) {
            // child process
            if (execvp(tokens[0], tokens) == -1) {
                perror("failed to execute");
            }
            exit(EXIT_FAILURE);
        } else {
            // parent process
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return 0;
}
