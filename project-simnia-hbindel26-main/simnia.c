/*
 * simnia.c
 * Author: Hayden Bindel
 * Description: Main loop for the Simnia shell.
 */

#include <string.h>
#include "shell.h"
#include "strvec.h"

int main(void) {
	strvec cmd;
	strvec_init(&cmd);

	do {
		prompt();
		read_cmd(&cmd);
		exec_cmd(&cmd);
	} while (strvec_size(cmd) > 0 && strcmp(strvec_get(cmd, 0), "exit") != 0);

	strvec_free(&cmd);
	return 0;
}


