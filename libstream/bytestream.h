#ifndef INCLUDE_BYTESTREAM_H
#define INCLUDE_BYTESTREAM_H

typedef unsigned char byte;

#include <stdio.h>
#include "varray.h"
#include "utils.h"

#pragma region Stream

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

#pragma endregion

#pragma region Operators

struct mapped_byte_stream {
	int id;
	void(*next)(struct byte_stream *self, byte v);
	void(*error)(struct byte_stream *self, byte e);
	void(*complete)(struct byte_stream *self);
	varray *listeners;
	byte(*map)(byte value);
};

typedef struct mapped_byte_stream mapped_stream_of_byte;
typedef byte(*mapper_function_from_byte_to_byte)(byte value);

void mapped_stream_of_byte_next(stream_of_byte *stream, byte v);
mapped_stream_of_byte* mapped_stream_of_byte_create(mapper_function_from_byte_to_byte map);
stream_of_byte* stream_of_byte_map(stream_of_byte *stream, mapper_function_from_byte_to_byte mapper);

#pragma endregion

#endif