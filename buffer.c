#define _POSIX_C_SOURCE  200809L

#include <stdlib.h>
#include <string.h>

#include "buffer.h"

/**
 * String accumulation buffer.  Members should not be referenced except by buffer functions.
 */
struct buffer {
    char *data; /**< Accumulated data for this buffer */
    int size; /**< Number of characters this buffer can hold */
    int idx;  /**< Current insertion point into this buffer */
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
    if (buf->idx < buf->size) {
        buf->data[buf->idx++] = c;
    }
}

char* buffer_as_string(struct buffer *buf)
{
    return strdup(buf->data);
}
