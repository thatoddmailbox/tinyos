#include <string.h>

size_t strlen(const char * str) {
	size_t length = 0;
	while (*str) {
		str++;
		length++;
	}
	return length;
}