// libstream.cpp : Defines the entry point for the console application.
//

#include "bytestream.h"

void printf_next(byte value) {
	printf("recieved %d\n", value);
}

int main() {
	ByteStream stream = { 0 };
	init_stream(&stream);
	ByteStream listener = { 0 };
	init_stream(&listener);
	listener.next = printf_next;
	add_listener(&stream, &listener);
	for (int i = 0; i < 10; i++)
		stream.next(&stream, i);
	return 0;
}

