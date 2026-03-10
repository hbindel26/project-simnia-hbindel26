/*
 * strvec->c
 * \author Nathan Eloe
 * \brief implementation of the string vector
 */

#include <stdlib.h>
#include <string.h>
#include "strvec.h"

void strvec_init(strvec * svec)
{
	svec->_vec = (char**) calloc(4, sizeof(char*));
	svec->_capacity = 4;
	svec->_size = 0;
}

void strvec_free(strvec * svec)
{
	int i=0;
	while (svec->_vec && svec->_vec[i])
	{
		free(svec->_vec[i]);
		i+=1;
	}
	free(svec->_vec);
	svec->_vec = NULL;
	svec->_capacity = 0;
	svec->_size = 0;
}

void strvec_push(strvec * svec, const char* str)
{
	if (svec->_size + 1 >= svec->_capacity)
	{
		if (svec->_capacity == 0)
			svec->_capacity = 2;
		svec->_vec = (char**)realloc(svec->_vec, svec->_capacity * 2 * sizeof(char*));
		svec->_capacity *= 2;
	}

	svec->_vec[svec->_size] = (char*)calloc(strlen(str)+1, sizeof(char));
	strcpy(svec->_vec[svec->_size], str);
	svec->_size += 1;
	svec->_vec[svec->_size] = NULL;
}

char* strvec_get(const strvec svec, int idx)
{
	if (idx < 0 || idx >= svec._size)
		return NULL;
	return svec._vec[idx];
}

int strvec_size(const strvec svec)
{
	return svec._size;
}

int strvec_capacity(const strvec svec)
{
	return svec._capacity;
}