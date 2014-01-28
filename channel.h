#ifndef CHANNEL_INC
#define CHANNEL_INC

#include <stddef.h>

typedef struct channel *channel;

// Create a new channel for data
// with the given size in number
// of bytes.
channel newChannel(size_t size);

// Receive data from the channel.
// The buffer must be long enough
// to hold a full datum, as defined
// when newChannel was called to
// create this particular channel.
// 
// If the buffer is not long enough,
// the behavior of receive is undefined,
// although it will likely result
// in a segmentation fault or memory
// becoming invalid.
// 
// The call blocks until data is
// available to be received from
// a matching call to send. When
// the call returns, the contents
// of the buffer will be the data
// that was sent. Any bytes beyond
// the end of the data will not
// be modified.
void channel_receive(channel c, void *buffer);

// Send data on the channel. The
// buffer must be long enough to
// hold a full datum, as defined
// when newChannel was called to
// create this particular channel.
// 
// If the buffer is not long enough,
// the behavior of receive is undefined,
// although it will likely result
// in a segmentation fault.
// 
// The call blocks until a receiver
// is available to receive the data.
// The buffer will not be modified.
void channel_send(channel c, const void *data);

#endif