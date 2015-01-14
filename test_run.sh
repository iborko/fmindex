#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Argument missing: path to file"
    exit
fi

echo "Processing file" $1

# check if there are any .reads* files
existing_files=`eval "find test_data/ -regex '${1}.reads.*' -type f | wc -l"`

# generate sizes of short sequences to generate (number of searches fmindex will do)
read_n=()
for p in 1000 5000 10000 50000 100000 500000 1000000
do
    read_n+=($p)
done

# if there is no reads, generate them
if [ $existing_files -eq 0 ]
then
    echo "Generating reads"
    for n in "${read_n[@]}"
    do
        echo "python test_data/read_generator.py -l 80 -n ${n} ${1} ${1}.reads${n}"
        python test_data/read_generator.py -l 80 -n ${n} ${1} ${1}.reads${n}
    done
fi

# evaluate
for n in "${read_n[@]}"
do
    echo "/usr/bin/time -v bin/fmindex ${1} ${1}.reads${n} 1 20 2>&1"
    /usr/bin/time -v bin/fmindex ${1} ${1}.reads${n} 1 20 2>&1 1>${1}.out${n} | grep -E 'User time|Maximum resident'
done
