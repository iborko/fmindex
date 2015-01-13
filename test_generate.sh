#!/bin/bash

# Generates random syntetic sequenes of length [2^13, 2^23]


# generate numbers of short sequences to generate
read_n=()
for p in {13..23}
do
    read_n+=($((2 ** p)))
done

for l in "${read_n[@]}"
do
    echo "python test_data/sequence_generator.py -l ${l} test_data/synt_${l}.fa"
    python test_data/sequence_generator.py -l ${l} test_data/synt_${l}.fa
done
