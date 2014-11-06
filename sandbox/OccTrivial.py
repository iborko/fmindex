"""
Provides a trivial Occurence table implementation,
for testing purposes.
"""
import numpy as np
import logging


log = logging.getLogger(__name__)


class OccTrivial(object):

    def __init__(self, string):

        super(OccTrivial, self).__init__()

        #   get the string alphabet
        self.alphabet = sorted(set(string))
        int_string = [self.alphabet.index(x) for x in string]

        self.occ = np.zeros((len(self.alphabet), len(string) + 1), dtype=np.int)

        for ind in range(1, len(string) + 1):

            self.occ[:, ind] = self.occ[:, ind - 1].copy()
            self.occ[int_string[ind - 1], ind] += 1

    def rank(self, c, i):
        return self.occ[self.alphabet.index(c), i]


def main():
    logging.basicConfig(level=logging.DEBUG)
    log.info('Displaying a basic Trivial Occ table')

    string = 'TGGACCACGTTGCAGCCCCA'
    occ = OccTrivial(string)

    log.info('Occ for string %s is :\n%r', string, occ.occ)

if __name__ == '__main__':
    main()
