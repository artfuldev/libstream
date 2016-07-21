// libstream.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "bytestream.h"

void printf_next(byte value) {
	printf("recieved %d\n", value);
}

int main() {
	stream_of_byte *stream = stream_create();
	stream_listener_of_byte *listener = stream_create_listener();
	listener->next = printf_next;
	stream_add_listener(stream, listener);
	for (int i = 0; i < 10; i++)
		stream->next(stream, i);
	return 0;
}

