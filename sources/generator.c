#include "../includes/manager.h"

const char	*digits = "0123456789";
const char	*lower = "abcdefghijklmnopqrstuvwxyz";
const char	*upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char	*specials = "!@#$%^&*()?|-+`,.<>";

char	*gen_pw(t_uint len)
{
	char	*pw;
	t_uint	index;
	size_t	set_len;

	if (len <= 3)
		return (NULL);
	pw = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == pw)
		return (NULL);
	index = 0;
	set_len = strlen(digits);
	for (t_uint i = 0; i < (len / 4) && index < len; i++, index++)
		*(pw + index) = *(digits + (rand() % set_len));
	set_len = strlen(specials);
	for (t_uint i = 0; i < (len / 4) && index < len; i++, index++)
		*(pw + index) = *(specials + (rand() % set_len));
	set_len = strlen(upper);
	for (t_uint i = 0; i < (len / 4) && index < len; i++, index++)
		*(pw + index) = *(upper + (rand() % set_len));
	set_len = strlen(lower);
	for (t_uint i = 0; i < (len / 4 + len % 4) && index < len; i++, index++)
		*(pw + index) = *(lower + (rand() % set_len));
	*(pw + index) = '\0';
	strshuffle(pw);
	return (pw);
}