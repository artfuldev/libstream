// libstream.cpp : Defines the entry point for the console application.
//

#include "bytestream.h"

int main() {
	ByteStream stream = { 0 };
	init_stream(&stream);
	stream.next(&stream, 11);
	return 0;
}

