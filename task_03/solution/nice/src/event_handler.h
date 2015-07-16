#include <stdlib.h>
#include <epoll.h>

typedef struct eh_ctx eh_ctx;

typedef struct event_handler {
	int (* get_fd)(struct event_handler *self);
	int (* handle_event)(struct event_handler self, const struct epoll_event* e);
	void (* destroy)(struct event_handler * self);
}event_handler;
