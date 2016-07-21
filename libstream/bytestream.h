#pragma once

typedef unsigned char byte;

#include <stdio.h>
#include <stdbool.h>

int counter_stream = 0;

#pragma region Stream

#define MAX_ALLOWED_LISTENERS 255

struct struct_byte_stream {
	int id;
	byte subscriptions;
	void(*next)(struct struct_byte_stream *self, byte v);
	void(*error)(struct struct_byte_stream *self, byte e);
	void(*complete)(struct struct_byte_stream *self);
	struct struct_byte_stream *listeners;
};


typedef struct struct_byte_stream ByteStream;

ByteStream(*byte_stream_array_pointer)[];

void add_listener_stream(ByteStream *stream, ByteStream *listener) {
	ByteStream *ptr = stream->listeners;
	while (ptr) {
		ptr++;
	}
	*ptr = *listener;
}

void func_next_stream_default(ByteStream *stream, byte v) {
	ByteStream *ptr = stream->listeners;
	while (ptr) {
		ptr->next(ptr, v);
		ptr++;
	}
};
void func_error_stream_default(ByteStream *stream, byte e) {
	ByteStream *ptr = stream->listeners;
	while (ptr) {
		ptr->error(ptr, e);
		ptr++;
	}
};
void func_complete_stream_default(ByteStream *stream) {
	ByteStream *ptr = stream->listeners;
	while (ptr) {
		ptr->complete(ptr);
		ptr++;
	}
};

void init_stream(ByteStream *stream) {
	stream->id = counter_stream++;
	stream->listeners = calloc(MAX_ALLOWED_LISTENERS, sizeof(ByteStream));
	stream->next = func_next_stream_default;
	stream->error = func_error_stream_default;
	stream->complete = func_complete_stream_default;
}

ByteStream* add_listener(ByteStream *stream, ByteStream *listener) {
	int listenersCount = stream->subscriptions;
	ByteStream *ptr = &(stream->listeners);
	ByteStream *attachedListener = NULL;
	while (ptr != NULL) {
		ptr++;
	}
	stream->subscriptions++;
	return attachedListener;
}

#pragma endregion

#pragma region Operators



#pragma endregion