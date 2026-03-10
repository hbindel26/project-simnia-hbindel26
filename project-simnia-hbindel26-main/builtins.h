/*
* builtins.h
* Author: Hayden Bindel
* Description: built-in command declarations and registry for simnia shell
*/

#ifndef BUILTINS_H
#define BUILTINS_H

#include "strvec.h"


typedef void (*builtin_f)(const strvec *cmd);

extern const char* BUILTINS[];
extern builtin_f FCNS[];

void _cd(const strvec *cmd);

#endif
