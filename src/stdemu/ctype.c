#include <ctype.h>

int isalnum(int c) {
	return isalpha(c) || isdigit(c);
}

int isalpha(int c) {
	return isupper(c) || islower(c);
}

int iscntrl(int c) {
	return (c < 32) || (c == 127);
}

int isdigit(int c) {
	return (c >= '0' && c <= '9');
}

int isgraph(int c) {
	return isalpha(c) || ispunct(c);
}

int islower(int c) {
	return (c >= 'a' && c <= 'z');
}

int isprint(int c) {
	return isalpha(c) || ispunct(c) || (c == ' ');
}

int ispunct(int c) {
	switch (c) { // big thing
		case '!': // F
		case '"': // U
		case '#': // C
		case '$': // K
		case '%': //
		case '&': // T
		case '\'': //H
		case '(': // A
		case ')': // T
		case '*': // '
		case '+': // S
		case ',': //
		case '-': // U
		case '.': // G
		case '/': // L
		case ':': // Y
		case ';': //
		case '<': // C
		case '=': // O
		case '>': // D
		case '?': // E
		case '@':
		case '[':
		case '\\':
		case '^':
		case '_':
		case '`':
		case '{':
		case '|':
		case '}':
		case '~':
			return 1;
			break;
		
		default:
			return 0;
	}
	return 0;
}

int isspace(int c) {
	return (c == '\t') || (c == '\n') || (c == '\f') || (c == '\r') || (c == ' ');
}

int isupper(int c) {
	return (c >= 'A') && (c <= 'Z');
}

int isxdigit(int c) {
	return isdigit(c) || (c >= 'A' && c <= 'F');
}

int tolower(int c) {
	if (c >= 'A' && c <= 'Z') {
		return c - ('A' - 'a');
	}
	return c;
}

int toupper(int c) {
	if (c >= 'a' && c <= 'z') {
		return c + ('A' - 'a');
	}
	return c;
}
