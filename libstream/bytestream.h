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
stream_next(stream_of_byte *stream, byte v) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_listener_of_byte *listener = ((stream_listener_of_byte *)varray_get(array, i));
		listener->next(&listener, v);
	}
};

void
stream_error(stream_of_byte *stream, byte e) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_listener_of_byte *listener = ((stream_listener_of_byte *)varray_get(array, i));
		listener->error(&listener, e);
	}
};

void
stream_complete(stream_of_byte *stream) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_listener_of_byte *listener = ((stream_listener_of_byte *)varray_get(array, i));
		listener->complete(&listener);
	}
};

stream_of_byte*
stream_create() {
	stream_of_byte* stream = xmalloc(sizeof(stream_of_byte));
	stream->id = counter_stream++;
	varray_init(&(stream->listeners));
	stream->next = stream_next;
	stream->error = stream_error;
	stream->complete = stream_complete;
	return stream;
}

stream_listener_of_byte*
stream_create_listener() {
	stream_listener_of_byte* stream = xmalloc(sizeof(stream_listener_of_byte));
	stream->id = counter_stream++;
	varray_init(&(stream->listeners));
	stream->next = stream_next;
	stream->error = stream_error;
	stream->complete = stream_complete;
	return stream;
}

stream_listener_of_byte*
stream_add_listener(stream_of_byte *stream, stream_listener_of_byte *listener) {
	printf("received");
	varray* array = stream->listeners;
	varray_push(array, listener);
	int length = varray_length(array);
	return (stream_listener_of_byte *)varray_get(array, length - 1);
}

#pragma endregion

#pragma region Operators



#pragma endregion

#endif