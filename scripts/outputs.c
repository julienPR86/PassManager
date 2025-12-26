#include "../headers/manager.h"

void	message_output(int type, char *msg, ...)
{
	va_list	args;

	switch (type)
	{
		case MESSAGE :
			#define output stdout
			fprintf(output, "\tMessage : ");
			break ;
		case WARNING :
			#define output stdout
			fprintf(output, "\tWarning : ");
			break ;
		case ERROR :
			#define output stderr
			fprintf(output, "\tError : ");
			break ;
		default :
			#define output stdout
			break ;
	}
	va_start(args, msg);
	vfprintf(output, msg, args);
	printf("\n");
	va_end(args);
	return ;
}
