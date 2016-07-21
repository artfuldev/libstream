#pragma once

typedef unsigned char byte;

#include <stdio.h>
#include <stdbool.h>

int counter_stream = 0;

#pragma region Listener

struct struct_byte_listener {
	int id;
	void(*next)(struct struct_byte_listener *self, byte v);
	void(*error)(struct struct_byte_listener *self, byte e);
	void(*complete)(struct struct_byte_listener *self);
};

typedef struct struct_byte_listener ByteListener;

void func_next_listener_default(ByteListener *self, int v) {
};
void func_error_listener_default(ByteListener *self, int e) {
};
void func_complete_listener_default(ByteListener *self) {
};

void init_listener(ByteListener *listener) {
	listener->id = counter_stream++;
	listener->next = func_next_listener_default;
	listener->error = func_error_listener_default;
	listener->complete = func_complete_listener_default;
}

#pragma endregion

#pragma region Stream

struct struct_byte_stream {
	int id;
	void(*next)(struct struct_byte_stream *self, byte v);
	void(*error)(struct struct_byte_stream *self, byte e);
	void(*complete)(struct struct_byte_stream *self);
	ByteListener listeners[20];
};

typedef struct struct_byte_stream ByteStream;

void add_listener_stream(ByteStream *stream, ByteListener *listener) {
	int i = 0;
	while (stream->listeners[i].id) {
		i++;
	}
	stream->listeners[i] = *listener;
}

void func_next_stream_default(ByteStream *stream, byte v) {
	int i = 0;
	while (stream->listeners[i].id) {
		stream->listeners[i].next(&(stream->listeners[i]), v);
		i++;
	}
};
void func_error_stream_default(ByteStream *stream, byte e) {
	int i = 0;
	while (stream->listeners[i].id) {
		stream->listeners[i].error(&(stream->listeners[i]), e);
		i++;
	}
};
void func_complete_stream_default(ByteStream *stream) {
	int i = 0;
	while (stream->listeners[i].id) {
		stream->listeners[i].complete(&(stream->listeners[i]));
		i++;
	}
};

void init_stream(ByteStream *stream) {
	stream->id = counter_stream++;
	ByteListener listener = { 2 };
	init_listener(&listener);
	add_listener_stream(stream, &listener);
	stream->next = func_next_stream_default;
	stream->error = func_error_stream_default;
	stream->complete = func_complete_stream_default;
}

#pragma endregion

#pragma region Operators



#pragma endregion