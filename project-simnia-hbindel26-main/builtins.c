/*
 * builtins.c
 * Author: Hayden Bindel
 * Description: Built-in command implementations and registry definitions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include "builtins.h"
#include "strvec.h"

/* Helper to get home directory */
static const char* home_dir(void) {
	const char* h = getenv("HOME");
	if (h && *h) return h;
	struct passwd* pw = getpwuid(getuid());
	return (pw && pw->pw_dir) ? pw->pw_dir : NULL;
}

/* Implementation of the built-in cd command */
void _cd(const strvec *cmd) {
	int n = strvec_size(*cmd);

	if (n >= 3) {
		fprintf(stderr, "cd: too many arguments\n");
		return;
	}

	const char* target = (n == 1) ? home_dir() : strvec_get(*cmd, 1);
	if (!target) {
		fprintf(stderr, "cd: cannot determine home directory\n");
		return;
	}

	if (chdir(target) == -1) {
		perror("cd");
	}
}

/* Built-in registry */
const char* BUILTINS[] = { "cd", NULL };
builtin_f   FCNS[]     = { _cd,  NULL };

