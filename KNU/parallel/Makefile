all: prime_mpi prime_openmp prime_sequential

prime_mpi: prime_mpi.c
	mpicc -Wall prime_mpi.c -o $@

prime_openmp: prime_openmp.c
	gcc -Wall -fopenmp prime_openmp.c -o $@

prime_sequential: prime_sequential.c
	gcc -Wall prime_sequential.c -o $@

clean:
	rm -f prime_{sequential,mpi,openmp}

run: all
	@echo -e "\nSequential program\n"
	@./prime_sequential
	@echo -e "\nMPI program\n"
	@mpirun -np 4 ./prime_mpi
	@echo -e "\nOpenMP program\n"
	@./prime_openmp

