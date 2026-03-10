#ifndef STRVEC_H
#define STRVEC_H
/*
 * strvec.h
 * \author Nathan Eloe
 * \brief a Null Terminated Null Terminated Array Array "class"
 */

typedef struct _ntntcaa
{
	char ** _vec;
	int _capacity;
	int _size;
} strvec;

void strvec_init(strvec * svec);
void strvec_free(strvec * svec);
void strvec_push(strvec * svec, const char* str);
char* strvec_get(const strvec svec, int idx);
int strvec_size(const strvec svec);
int strvec_capacity(const strvec svec);
#endif


