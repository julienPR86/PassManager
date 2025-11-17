#include "../headers/manager.h"

void	message_output(char *msg)
{
	if (NULL == msg)
		return ;
	printf("\t%s", msg);
	return ;
}

void	error_output(char *error)
{
	if (NULL == error)
		return ;
	fprintf(stderr, "\tError : %s", error);
	return ;
}