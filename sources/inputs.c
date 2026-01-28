#include "../includes/manager.h"

char	*input(char *msg)
{
	char	c;
	char	*str;
	t_uint	index;

	str = (char *)malloc(sizeof(char) * (MAX_STRING_LENGTH + 1));
	if (NULL == str)
		return (NULL);
	if (NULL != msg)
		printf("%s", msg);
	c = 0;
	index = 0;
	while (c != '\n' && c != '\r' && index < MAX_STRING_LENGTH)
	{
		c = getc(stdin);
		*(str + index) = c;
		index++;
	}
	*(str + index - 1) = '\0';
	if (index >= MAX_STRING_LENGTH)
		empty_stdin();
	return (str);
}

void	empty_stdin(void)
{
	char	c;

	c = 0;
	while (c != '\n' && c != '\r')
		c = getc(stdin);
	return ;
}
