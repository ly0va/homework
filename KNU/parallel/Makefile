all: prime_mpi prime_openmp prime_sequential

prime_mpi: prime_mpi.c
	mpicc -O2 -Wall $^ -o $@

prime_openmp: prime_openmp.c
	gcc -O2 -Wall -fopenmp $^ -o $@

prime_sequential: prime_sequential.c
	gcc -O2 -Wall $^ -o $@

clean:
	rm -f prime_{sequential,mpi,openmp}

run: all
	@echo -e "\nSequential program\n"
	@./prime_sequential
	@echo -e "\nMPI program\n"
	@mpiexec -np 4 ./prime_mpi
	@echo -e "\nOpenMP program\n"
	@./prime_openmp

