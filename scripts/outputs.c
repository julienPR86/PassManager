#include "../headers/manager.h"

void	error_output(char *error)
{
	if (NULL == error)
		return ;
	fprintf(stderr, "\tError : %s", error);
	return ;
}