import argparse
import random

parser = argparse.ArgumentParser(
    description='Generate random genetic sequence')
parser.add_argument('-l', type=int, help='length of the sequence', default=1000)
parser.add_argument('output_file', type=argparse.FileType('w'))

args = parser.parse_args()

length = args.l
alphabet = 'ACGT'

# generate random string
s = ''.join(random.choice(alphabet) for _ in range(length))

# write FASTA header + sequence to file
f = args.output_file
f.write('>Random generated sample %d, length %d\n' %
        (random.randint(0, 10000), args.l))
f.write(s)

print "Generated sequence of length", length
