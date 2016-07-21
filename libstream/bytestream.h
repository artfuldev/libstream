#ifndef INCLUDE_BYTESTREAM_H
#define INCLUDE_BYTESTREAM_H

typedef unsigned char byte;

#include <stdio.h>
#include "varray.h"

int counter_stream = 0;

#pragma region Utils

void*
xmalloc(size_t size)
{
	void *ret = malloc(size);
	return ret;
}

#pragma endregion

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

void
stream_of_byte_next(stream_of_byte *stream, byte v) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_listener_of_byte *listener = ((stream_listener_of_byte *)varray_get(array, i));
		listener->next(listener, v);
	}
};

void
stream_of_byte_error(stream_of_byte *stream, byte e) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_listener_of_byte *listener = ((stream_listener_of_byte *)varray_get(array, i));
		listener->error(listener, e);
	}
};

void
stream_of_byte_complete(stream_of_byte *stream) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_listener_of_byte *listener = ((stream_listener_of_byte *)varray_get(array, i));
		listener->complete(listener);
	}
};

stream_of_byte*
stream_of_byte_create() {
	stream_of_byte* stream = xmalloc(sizeof(stream_of_byte));
	stream->id = counter_stream++;
	varray_init(&(stream->listeners));
	stream->next = stream_of_byte_next;
	stream->error = stream_of_byte_error;
	stream->complete = stream_of_byte_complete;
	return stream;
}

stream_listener_of_byte*
stream_listener_of_byte_create() {
	stream_listener_of_byte* stream = xmalloc(sizeof(stream_listener_of_byte));
	stream->id = counter_stream++;
	varray_init(&(stream->listeners));
	stream->next = stream_of_byte_next;
	stream->error = stream_of_byte_error;
	stream->complete = stream_of_byte_complete;
	return stream;
}

stream_listener_of_byte*
stream_add_listener(stream_of_byte *stream, stream_listener_of_byte *listener) {
	varray* array = stream->listeners;
	varray_push(array, listener);
	int length = varray_length(array);
	return (stream_listener_of_byte *)varray_get(array, length - 1);
}

#pragma endregion

#pragma region Operators

typedef byte (*mapper_function_from_byte_to_byte)(byte value);

struct mapped_byte_stream {
	int id;
	void(*next)(struct byte_stream *self, byte v);
	void(*error)(struct byte_stream *self, byte e);
	void(*complete)(struct byte_stream *self);
	varray *listeners;
	byte(*map)(byte value);
};

typedef struct mapped_byte_stream mapped_stream_of_byte;

void
mapped_stream_of_byte_next(stream_of_byte *stream, byte v) {
	mapped_stream_of_byte* mapped_stream = (mapped_stream_of_byte*)stream;
	byte mapped = mapped_stream->map(v);
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_listener_of_byte *listener = ((stream_listener_of_byte *)varray_get(array, i));
		listener->next(listener, mapped);
	}
};

mapped_stream_of_byte*
mapped_stream_of_byte_create(mapper_function_from_byte_to_byte map) {
	mapped_stream_of_byte* stream = xmalloc(sizeof(mapped_stream_of_byte));
	stream->id = counter_stream++;
	varray_init(&(stream->listeners));
	stream->next = mapped_stream_of_byte_next;
	stream->error = stream_of_byte_error;
	stream->complete = stream_of_byte_complete;
	stream->map = map;
	return stream;
}

stream_of_byte*
stream_of_byte_map(stream_of_byte *stream, mapper_function_from_byte_to_byte mapper) {
	mapped_stream_of_byte* mapped_stream = mapped_stream_of_byte_create(mapper);
	stream_listener_of_byte* mapped_listener = (stream_listener_of_byte*)mapped_stream;
	return (stream_of_byte*)stream_add_listener(stream, mapped_listener);
}

#pragma endregion

#endif