#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

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

int main(int argc, char** argv) {

    char response[100];

    do {
        prompt();

        scanf("%s", response);

        // Identify command type

        // Prepare the parameters for the command

        // create the NEW process to run the command
        // fork()

        // if child
            // execute specific command
            // //execl()

            // nothing should happen here unless execl failed

        // else
            // parent
            // wait for child

        // start again
    } while (strcmp(response, "exit") != 0);

    return 0;
}
