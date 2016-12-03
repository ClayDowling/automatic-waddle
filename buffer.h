#ifndef POSTINFIX_BUFFER_H
#define POSTINFIX_BUFFER_H

/**
 * @file buffer.h
 *
 * Character accumulation buffers.  Similar in concept to a string, but because the only operation
 * necessary is appending, we can skip all of the other functions required to support a true string
 * class.
 */

struct buffer;

/**
 * Create an initialized buffer
 * @param size of the buffer
 * @return Initialized buffer.  Caller is responsible for calling buffer_release to free resources
 */
struct buffer *buffer_create(int size);

/**
 * Free resources associated with a buffer
 * @param buf Buffer to be released
 */
void buffer_release(struct buffer *buf);

/**
 * Append character to a buffer
 * @param buf Buffer to append to
 * @param c character to append
 */
void buffer_append(struct buffer *buf, char c);

/**
 * Return buffer as a string
 * @param buf Buffer to retrieve
 * @return String representation of the buffer.  Caller is responsible for freeing.
 */
char *buffer_as_string(struct buffer *buf);

#endif //POSTINFIX_BUFFER_H
