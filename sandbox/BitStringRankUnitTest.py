"""
Unit teseting for BitStringRank class
"""
import numpy as np
from numpy.random import randint
import logging
from time import time
from BitStringRank import BitStringRank

log = logging.getLogger(__name__)


def main():
    """
    Unit testing for the BitStringRank class.
    """

    logging.basicConfig(level=logging.INFO)
    log.info('Testing BitStringRank')

    #   this is for manual checking of buckets
    str = '01010010101001010100'
    bs = BitStringRank(str, 3)
    log.debug('For s: %s', str)
    log.debug('Buckets : %r, superbuckets: %r', bs.buckets, bs.superbuckets)

    #   following is a test of implementation correctness (validation)
    #   trivial ranking imlplementation, for testing the BitStringRank
    def trivial_rank(string, i):
        return sum(string[:i])

    #   create strings of various lengths
    for str_len in range(200, 250):
        random_string = np.random.randint(0, 2, str_len)
        random_string_br = BitStringRank(random_string, 6)
        log.debug('Testing on %r', random_string)

        #   compare ranking equality for various indices
        for i in range(str_len + 1):
            if random_string_br.rank(i) == trivial_rank(random_string, i):
                log.debug('Test passed')
            else:
                raise

    log.info('Validation tests passed')

    #   test BitStringRankSpeed on long strings
    #   first create some strings
    str_cnt = 100
    for str_len in (1000, 10000):

        log.info('\n\n\t***Testing on strings of length %d', str_len)
        test_string = [randint(0, 2, str_len) for i in range(str_cnt)]

        #   measure BitString creation time
        t0 = time()
        test_string_br = [BitStringRank(s, 64) for s in test_string]
        log.info('Created BitStringRank objects in %.2f secs', time() - t0)

        #   indices we will test on
        test_ind_cnt = 100
        test_indices = np.random.randint(0, str_len, test_ind_cnt)

        #   test the BitString performance
        t0 = time()
        for br in test_string_br:
            for test_ind in test_indices:
                br.rank(test_ind)
        log.info('BitStringRank implementation time: %.2f secs', time() - t0)

        #   test trivial implementation performance
        t0 = time()
        for s in test_string:
            for test_ind in test_indices:
                trivial_rank(s, test_ind)
        log.info('Trivial implementation time: %.2f secs', time() - t0)

if __name__ == '__main__':
    main()
