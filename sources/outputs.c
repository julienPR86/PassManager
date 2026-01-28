#include "../includes/manager.h"

void	message_output(int type, char *msg, ...)
{
	va_list	args;

	switch (type)
	{
		case MESSAGE :
			#ifndef output
				#define output stdout
			#endif
			fprintf(output, "\tMessage : ");
			break ;
		case WARNING :
			#ifndef output
				#define output stdout
			#endif
			fprintf(output, "\tWarning : ");
			break ;
		case ERROR :
			#ifndef output
				#define output stderr
			#endif
			fprintf(output, "\tError : ");
			break ;
		default :
			break ;
	}
	#ifndef output
		#define output stdout
	#endif
	va_start(args, msg);
	vfprintf(output, msg, args);
	printf("\n");
	va_end(args);
	return ;
}
