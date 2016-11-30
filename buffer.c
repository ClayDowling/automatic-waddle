#define _POSIX_C_SOURCE  200809L

#include <stdlib.h>
#include <string.h>

#include "buffer.h"

struct buffer {
    char *data;
    int size;
    int idx;
};

struct buffer *buffer_create(int size)
{
    struct buffer *buf;

    buf = (struct buffer*)calloc(1, sizeof(struct buffer));
    buf->size = size;
    buf->data = (char*)calloc(1, size + 1);

    return buf;
}

void buffer_release(struct buffer *buf)
{
    if (buf) {
        free(buf->data);
        free(buf);
    }
}

void buffer_append(struct buffer *buf, char c)
{
    buf->data[buf->idx++] = c;
}

char* buffer_as_string(struct buffer *buf)
{
    return strdup(buf->data);
}
