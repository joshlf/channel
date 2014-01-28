#include "channel.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct channel {
	pthread_mutex_t send_mtx, receive_mtx;
	bool sender_here, receiver_here;
	void *buffer;
	size_t size;
};

struct channel *newChannel(size_t size) {
	struct channel *c = malloc(sizeof(*c));
	pthread_mutex_init(&(c->send_mtx), NULL);
	pthread_mutex_init(&(c->receive_mtx), NULL);

	c->sender_here = c->receiver_here = false;
	c->buffer = NULL;
	c->size = size;

	return c;
}

void channel_receive(struct channel *c, void *buffer) {
	// Make sure you're the only receiver
	// vying for information
	pthread_mutex_lock(&(c->receive_mtx));

	// Signal to the sender that we're
	// ready to receive data.
	c->buffer = buffer;

	// Spin waiting for the sender to signal
	// that they're done writing data.
	while (c->buffer);

	pthread_mutex_unlock(&(c->receive_mtx));
}

void channel_send(channel c, const void *data) {
	// Make sure you're the only sender
	// vying to send information
	pthread_mutex_lock(&(c->send_mtx));

	// Spin waiting for the receiver to signal
	// that they're ready to accept data.
	while (!c->buffer);

	memcpy(c->buffer, data, c->size);

	// Signal to the receiver that
	// we're done writing data.
	c->buffer = NULL;

	pthread_mutex_unlock(&(c->send_mtx));
}