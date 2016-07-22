// libstream.cpp : Defines the entry point for the console application.
//

#include "stream_of_byte.h"
#include "stream_of_byte_map.h"

void printf_next(stream_of_byte *stream, byte value) {
	printf("recieved %d\n", value);
}

byte map_2x(byte value) {
	return 2 * value;
}

int main() {
	stream_of_byte* stream = stream_of_byte_create();
	stream_of_byte* listener = stream_of_byte_create();
	listener->next = printf_next;
	stream_add_listener(stream, listener);
	stream_of_byte* mapped_stream = stream_of_byte_map(stream, map_2x);
	stream_add_listener(mapped_stream, listener);
	for (int i = 0; i < 10; i++)
		stream->next(stream, i);
	getchar();
	return 0;
}

