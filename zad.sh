#!/bin/bash
#SBATCH -n 1
#SBATCH -c 6
#SBATCH -o output.txt
hostname
./program 10 60 100 1