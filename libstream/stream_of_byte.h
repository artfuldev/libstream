#ifndef INCLUDE_STREAM_OF_BYTE_H
#define INCLUDE_STREAM_OF_BYTE_H

#include "varray.h"
#include "utils.h"

typedef unsigned char byte;

struct byte_stream {
	int id;
	void(*next)(struct byte_stream *self, byte v);
	void(*error)(struct byte_stream *self, byte e);
	void(*complete)(struct byte_stream *self);
	varray *listeners;
};

typedef struct byte_stream stream_of_byte;
typedef struct byte_stream stream_listener_of_byte;

void stream_of_byte_next(stream_of_byte *stream, byte v);
void stream_of_byte_error(stream_of_byte *stream, byte e);
void stream_of_byte_complete(stream_of_byte *stream);
stream_of_byte* stream_of_byte_create();
stream_listener_of_byte* stream_listener_of_byte_create();
stream_listener_of_byte* stream_add_listener(stream_of_byte *stream, stream_listener_of_byte *listener);

#endif