#include <pthread.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include "philo.h"

int	main(int argc, char **argv) {
	t_context ctx;

	if (init_ctx(&ctx, argc, argv))
		return (1);
	exit_ctx(&ctx);
	return (0);
}
