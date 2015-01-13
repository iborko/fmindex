import argparse
import random

parser = argparse.ArgumentParser(
    description='Generate genetic reads from sequence')
parser.add_argument('-n', type=int, help='number of reads to generate',
                    default=1000)
parser.add_argument('-l', type=int, help='length of one read', default=70)
parser.add_argument('input_file', type=argparse.FileType('r'))
parser.add_argument('output_file', type=argparse.FileType('w'))

args = parser.parse_args()

# read input file
reading_header = True
header = ''
sequence = ''
for line in args.input_file:
    line = line.replace('\n', '')
    if line[0] == '>' or line[0] == ';':
        if reading_header:
            header += line[1:]
        else:
            break
    else:
        if reading_header:
            reading_header = False
        sequence += line

if args.l >= len(sequence):
    print "Sequence too short"
    exit(1)

print "Sequence length", len(sequence)

f = args.output_file
for i in xrange(args.n):
    start = random.randint(0, len(sequence) - args.l - 1)
    f.write('@ %s _%d_%d_0:%d\n' % (header, start, start+args.l, i))
    f.write(sequence[start:start+args.l] + '\n')
    f.write('+\n')
    # f.write('I' * args.l + '\n')  # write quality markers
    f.write('I\n')  # no quality markers
