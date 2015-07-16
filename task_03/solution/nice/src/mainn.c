#include "reactor.h"
#include "server_eh.h"

int main(int c, char **v) {

	int port = atoi(v[2]);
	int size = atoi(v[1]);
	reactor *r = create_reactor(size); //rozmiar w arg ile klientow supportuje
	event_handler * seh = create_server_eh(r, port, size);
	r->add_eh (r, seh);
	r->event_loop(r);
	return 0;
}
