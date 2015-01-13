# FMindex implementation using wavelet trees

### Goals
  1. implement the simplest FM-index using just basic data structures
  2. implement FM-index using wavelet trees

### How to get source
`git clone --recursive https://github.com/iborko/fmindex`

### Build instructions
  * run `make`
  * executables will be located in `bin` folder (`bin/fmindex`, `bin/test`)

### Usage
Binary will be located in `bin` folder (`fmindex`). Usage:  
&nbsp;&nbsp;&nbsp;&nbsp;`fmindex <sequence> <reads> [<occurrence_table> [<bucket_size>]]`

  * `<sequence>` - path to the sequence on which the search will be made, FASTA format
  * `<reads>` - path to the reads that will be searched, FASTQ format
  * `<occurrence_table>` - can be `0` (matrix occurrence table), `1` (wavelet tree based occurrence table)
  * `<bucket_size>` - bucket size for bit string rank in wavelet tree, optional, default is 20

Example:  
&nbsp;&nbsp;&nbsp;&nbsp;`fmindex Esch_coli_536.fna Esch_coli_536_reads.fq 1 40`  


Script `test_run.sh` can be used to run program on one of the example sequence. Example sequences are located in the `test_data` folder.

Example of run:  
&nbsp;&nbsp;&nbsp;&nbsp;`test_run.sh test_data/Esch_coli_536.fna`  
This script will generate sets of (1000, 5000, 10000, 50000, 100000, 500000, 1000000) reads and run the `fmindex` on them, measuring CPU time and memory using `time` program.

### References
  1 Jochen Singer: A Wavelet Tree Based FM-Index for Biological Sequences in SeqAn, [link](http://www.mi.fu-berlin.de/wiki/pub/ABI/FMIndexThesis/FMIndex.pdf)

