/*
 * shell.c
 * Author: Hayden Bindel
 * Description: Implements basic shell functionality for Simnia.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "builtins.h"

void prompt(void) {
	char hostname[128];
	char cwd[256];
	gethostname(hostname, sizeof(hostname));
	const char* username = getlogin();
	getcwd(cwd, sizeof(cwd));
	printf("\033[1;32m%s@%s\033[0m:\033[1;33m%s\033[0m $> ",
       username, hostname, cwd);

	fflush(stdout);
}

void read_cmd(strvec *cmd) {
	char *buffer = calloc(256, sizeof(char));
	size_t buffsize = 256;
    	getline(&buffer, &buffsize, stdin);

// reset strvec before storing new input
	strvec_free(cmd);
	strvec_init(cmd);
// tokenize user input
	char *ptr = strtok(buffer, " \n");
	while (ptr) {
		strvec_push(cmd, ptr);
		ptr = strtok(NULL, " \n");
	}
// Debugging: print tokens read
	printf("DEBUG: read_cmd() found %d tokens:\n", strvec_size(*cmd));
	for (int i = 0; i < strvec_size(*cmd); i++) {
    		printf("  token[%d] = '%s'\n", i, strvec_get(*cmd, i));
	}

	free(buffer);
}

void exec_cmd(const strvec *cmd) {
    if (strvec_size(*cmd) == 0) {
        return;  // nothing to run
    }
    // Check if command is a built-in before forking
    for (int i = 0; BUILTINS[i] != NULL; i++) {
        if (strcmp(strvec_get(*cmd, 0), BUILTINS[i]) == 0) {
            FCNS[i](cmd);   // Call the built-in function
            return;         // Do not fork/exec for built-ins
        }
    }

    pid_t cpid = fork();
    if (cpid == 0) {
        // ---- Child process ----
        int n = strvec_size(*cmd);
        char **argv = malloc((n + 1) * sizeof(char *));
        if (!argv) {
            perror("malloc");
            _exit(errno);
        }

        for (int i = 0; i < n; i++) {
            argv[i] = (char *)strvec_get(*cmd, i);
        }
        argv[n] = NULL;

        // Debugging: print what we’re about to exec
        fprintf(stderr, "About to exec: %s\n", argv[0]);
        for (int i = 0; argv[i] != NULL; i++) {
            fprintf(stderr, "  arg[%d] = %s\n", i, argv[i]);
        }

        execvp(argv[0], argv);

        // If we get here, exec failed
        perror(argv[0]);
        _exit(errno);
    } 
    else if (cpid < 0) {
        perror("fork");
    } 
    else {
        int status;
        do {
            waitpid(cpid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

