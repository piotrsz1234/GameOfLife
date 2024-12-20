#!/bin/bash

./scripts/compile.sh

for filename in new_scripts/*; do
    rm "$filename"
done

./generate

for filename in new_scripts/*; do
    sbatch "$filename"
done

#./serial 300 20 0 > ./outputs/serialN=300_1.txt
#./serial 3000 20 0 > ./outputs/serialN=3000_1.txt
#./serial 30000 20 0 > ./outputs/serialN=30000_1.txt

#./serial 300 20 0 > ./outputs/serialN=300_2.txt
#./serial 3000 20 0 > ./outputs/serialN=3000_2.txt
#./serial 30000 20 0 > ./outputs/serialN=30000_2.txt

#./serial 300 20 0 > ./outputs/serialN=300_3.txt
#./serial 3000 20 0 > ./outputs/serialN=3000_3.txt
#./serial 30000 20 0 > ./outputs/serialN=30000_3.txt
