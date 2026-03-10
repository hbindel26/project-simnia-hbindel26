/*
 * shell.h
 * Author: Hayden Bindel
 * Description: Function declarations for the Simnia shell.
 */

#ifndef SHELL_H
#define SHELL_H

#include "strvec.h"

void prompt(void);
void read_cmd(strvec *cmd);
void exec_cmd(const strvec *cmd);

#endif
