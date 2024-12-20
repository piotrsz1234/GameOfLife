#!/bin/bash

gcc generate.c -o generate
mpicc Utils.h Utils.c cluster.c -o clusterMp -O3 -fopenmp
mpicc Utils.h Utils.c cluster.c -o cluster -O3
mpicc Utils.h Utils.c nonBlocking.c -o ncluster -O3
mpicc Utils.h Utils.c nonBlocking.c -o nclusterMp -O3 -fopenmp
gcc Utils.h Utils.c serial.c -o serial -O3