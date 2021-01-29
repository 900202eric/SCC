#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "must provide exacty 2 argument!\n");
		return 1;
	}

	unsigned long long r = atoll(argv[1]);
	unsigned long long k = atoll(argv[2]);
	unsigned long long pixel = 0;

	MPI_Init(NULL, NULL);
	
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);
	
	unsigned long long  local_size = 0;
	local_size = (r + world_size - world_rank - 1) / world_size;

	unsigned long long  local_pixel = 0;
	for(unsigned long long x = 0; x < local_size; x++){
		unsigned long long s = world_size * x + world_rank;
		unsigned long long y = ceil(sqrtl(r*r - s*s));
		local_pixel += y;
		local_pixel %= k;
	}
	
	unsigned long long  global_pixel = 0;
	MPI_Reduce(&local_pixel, &global_pixel, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	
	global_pixel %= k;

	MPI_Finalize();
	
	if(world_rank == 0)
		printf("%llu\n", (4 * global_pixel) % k);
}
