#include <string.h>

#include <memory.h>

char * strdup(const char * str) {
	size_t length = strlen(str);
	char * new_string = (char *) ALLOC(length + 1);
	memcpy(new_string, str, length);
	new_string[length] = '\0';
	return new_string;
}