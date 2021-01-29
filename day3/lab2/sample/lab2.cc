#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

struct ThreadArgument{
	int core_rank;
	int cout_size;
	unsigned long long r;
	unsigned long long k;
	unsigned long long ncpu;
};

void* calculate(void* arg){
	struct ThreadArgument* local_arg = (ThreadArgument*)arg;
	unsigned long long *local_pixel = (unsigned long long*) malloc(sizeof(unsigned long long));
	*local_pixel = 0;
	unsigned long long size = local_arg->cout_size;
	unsigned long long ncpu = local_arg->ncpu;
	unsigned long long rank = local_arg->core_rank;
	unsigned long long r = local_arg->r;
	unsigned long long k = local_arg->k;
	// printf("size: %llu\n", size);
	for (unsigned long long x = 0; x < size; x++){
		// unsigned long long rank = local_arg->core_rank;
		// unsigned long long r = local_arg->r;
		// unsigned long long k = local_arg->k;
		unsigned long long s = ncpu * x + rank;
		unsigned long long y = ceil(sqrtl(r*r - s*s));
		*local_pixel += y;
		// *local_pixel %= k;
		// printf("%llu %llu %llu %llu\n", r, k, s, y);
	}
	*local_pixel %= k;
	pthread_exit(local_pixel);
}

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "must provide exactly 2 arguments!\n");
		return 1;
	}

	unsigned long long r = atoll(argv[1]);
	unsigned long long k = atoll(argv[2]);
	unsigned long long pixels = 0;
	cpu_set_t cpuset;
	sched_getaffinity(0, sizeof(cpuset), &cpuset);
	unsigned long long ncpus = CPU_COUNT(&cpuset);
	unsigned long long global_pixel = 0;
	struct ThreadArgument arg[ncpus];
	// printf("ncpu: %llu\n", ncpus);
	pthread_t thread[ncpus];
	for(int t = 0; t < ncpus; t++){
		unsigned local_size = (r + ncpus - t - 1) / ncpus;
		arg[t].r = r;
		arg[t].k = k;
		arg[t].core_rank = t;
		arg[t].cout_size = local_size;
		arg[t].ncpu = ncpus;
		pthread_create(&thread[t], 0, calculate, &arg[t]);
	}

	for(int t = 0; t < ncpus; t++){
		unsigned long long *local_result;
		pthread_join(thread[t], (void**)&local_result);
		global_pixel += *local_result;
		// global_pixel %= k;
		free(local_result);
	}
	global_pixel %= k;

	printf("%llu\n", (4 * global_pixel) % k);
}
