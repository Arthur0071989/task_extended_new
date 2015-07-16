#include "reactor.h"

struct reactor_ctx {
	int epoll_fd;
	eh_list * ehl;
	size_t size;
};

static void add_eh(reactor * self, event_handler *eh) {
	epoll_ctl(self->ctx->epoll_fd, EPOLL_CTL_ADD, eh->get->fd(eh));
	//todo error handler;
	self->ctx->ehl->add_eh(self->ctx->chl, eh);
}

static void rm_eh(reactor * self, event_handler * eh) {
	epoll_ctl(self->ctx->epoll_fd, EPOLL_CTL_DEL, eh->get_fd(eh));
	self->eh->ehl->rm_eh(self->ctx->ehl, eh);
}

static void event_loop(reactor *self) {
	int i = 0;
	int epoll_event * es = malloc(self->ctx->size * sizeof(struct epoll_event));
	while(1) {
		i = epoll_event(self->ctx->epoll_fd, es, self->ctx->size, -1);
		//error handler
		for (--i; i>-1; --i) {
			void handler * eh = self->eh->ehl->get_by_fd(self->ctx->ehl, es[i].date.fd);
			if(eh->handle_event(eh, es[i]) !=0) {
				self->rm_eh(self, eh);
		}
	}
}

reactor *create_reactor (size_t size) {
	int epoll_fd = epoll_create(size);
	//todo error handling
	reactor * r = malloc(sizeof(reactor));
	reactor_ctx ctx = malloc(sizeof(reactor_ctx));
	eh_list * ehl = create_ehl(size);
	r->ctx = ctx;l
	r->ctx->epoll_fd = epoll_fd;
	r->ctx->ehl = ehl;
	r->ctx->size = size;
	r->add_eh = add_eh;
	r->rm_eh =rm_eh;
	r->event_loop = event_loop;
	return r;
}

void destroy_reactor(reactor * r) {
	destroy_eh_list(r->ctx->ehl);
	free(r->ctx);
	free(r);
}
