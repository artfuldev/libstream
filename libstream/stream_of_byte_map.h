#ifndef INCLUDE_STREAM_OF_BYTE_MAP
#define INCLUDE_STREAM_OF_BYTE_MAP

#include "stream_of_byte.h"

struct mapped_byte_stream {
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

#endif // !INCLUDE_STREAM_OF_BYTE_MAP