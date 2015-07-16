#include "server_eh.h"

struct eh_ctx {
	int fd;
	reactor * r;
};

static int get_fd(event_handler * self) {
	return self->ctx->fd;
}

static int handle_event(event_handler *self, const struct epoll_event * e) {
	event_handler * eh_eh = 0;
	int eh_fd  = -1;
	struct sockaddr_in eh_addr;
	sockaddrlen_t eh_addr_len = sizeof(struct sockaddr_in);
	memset(&eh_addr, 0, eh_addr_len);
	eh_fd = accept(self->ctx->fd, &eh_addr, &eh_addr_len);
	if(eh_fd < 0){
		printf("Cannot accept client /n");
		exit(1); //close app
	}
	eh_eh = create_client_eh(eh_fd);
	self->ctx->r->add_eh(r, eh_eh);
	return 0;
}

event_handler * create_server_eh (reactor * r) {
	event_handler seh = malloc(sizeof(event_handler));
	eh_ctx * ctx = malloc(sizeof(eh_ctx));
	ctx->fd=socket(AF_INET, S_NONBLOCK|SOCK_STREAM, 0);
	//error handling
	// bind (ctx->fd,...);
	// listen(ctx->fd,..);

	seh->ctx = ctx;
	seh->get_fd = get_fd;
	seh->handle_event = handle_event;
	seh->destroy = destroy_server_eh;
	return seh;
}

static void destroy_server_eh (event_handler *self) {
	free(self->ctx);
	free(self);
}

