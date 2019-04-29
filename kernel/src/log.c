#include "log.h"

void _print_int(uint32_t num, int base) {
	if (num == 0) {
		term_get_current()->putc('0');
		return;
	}

	const char * digits = "0123456789abcdef";
	uint32_t shifter = 1;
	for (int i = 0; i < 7; i++) {
		shifter *= base;
	}
	int leading_zeros = 1;
	while (shifter > 0) {
		int digit = (num / shifter) % base;
		shifter = shifter / base;

		if (digit == 0 && leading_zeros) {
			continue;
		} else {
			leading_zeros = 0;
		}

		term_get_current()->putc(digits[digit]);
	}
}

void khexdump(void * data, uint32_t size) {
	uint32_t last_line = size % LOG_HEXDUMP_LINE_SIZE;
	uint32_t lines = size / LOG_HEXDUMP_LINE_SIZE;
	if (last_line > 0) {
		lines += 1;
	}

	void * data_pointer = data;
	for (uint32_t i = 0; i < lines; i++) {
		kprintf("0x%x | ", data_pointer);
		uint32_t line_size = LOG_HEXDUMP_LINE_SIZE;
		if (i == lines - 1 && last_line > 0) {
			line_size = last_line;
		}

		for	(uint32_t j = 0; j < line_size; j++) {
			uint8_t data_byte = *((uint8_t *) data_pointer);
			if (data_byte < 0x10) {
				kprintf("0");
			}
			kprintf("%x ", data_byte);
			data_pointer++;
		}

		kprintf("| ");

		data_pointer -= line_size;

		for	(uint32_t j = 0; j < line_size; j++) {
			uint8_t data_byte = *((uint8_t *) data_pointer);
			if (data_byte > 0x1f && data_byte < 0x80) {
				term_get_current()->putc(data_byte);
			} else {
				term_get_current()->putc('.');
			}
			data_pointer++;
		}

		kprintf(" |\n");
	}
}

void kputs(char * message) {
	while (*message) {
		term_get_current()->putc(*message);
		message++;
	}
} 

void kprintf(const char * format, ...) {
	va_list args;
	va_start(args, format);

	uint8_t in_specifier = 0;
	while (*format) {
		if (*format == '%') {
			in_specifier = 1;
		} else {
			if (in_specifier) {
				if (*format == 's') {
					kputs(va_arg(args, char *));
				} else if (*format == 'd') {
					_print_int(va_arg(args, int), 10);
				} else if (*format == 'x') {
					_print_int(va_arg(args, int), 16);
				} else {
					kputs("(ERROR: UNKNOWN FORMAT SPECIFIER)");
				}
				in_specifier = 0;
			} else {
				term_get_current()->putc(*format);
			}
		}
		format++;
	}

	va_end(args);
}