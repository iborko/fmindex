"""
Unit testing for wavelet tree
Occ table implementation.
"""
import logging
from WaveletTree import WaveletTree
from OccTrivial import OccTrivial
from numpy.random import randint


log = logging.getLogger(__name__)


def main():
    logging.basicConfig(level=logging.DEBUG)
    log.info('Wavelet tree unit testing')

    #   we will randomize strings with the following chars
    alph = 'ABCDEFGHIJ'
    #   create random strings
    str_cnt = 100
    rand_alphs = [randint(3, len(alph)) for i in range(str_cnt)]
    str_len_min = 10
    str_len_max = 20
    random_strings = [[alph[x] for x in randint(
        0,
        rand_alph,
        randint(str_len_min, str_len_max))] for rand_alph in rand_alphs]

    #   testing validation (that wavelets work as they should)
    for rand_string in random_strings:
        log.debug('Testing string: %s', "".join(rand_string))

        #   build occurence tables
        occ_trivial = OccTrivial(rand_string)
        occ_wave_tree = WaveletTree(rand_string, 10)

        #   the alphabeth used in this sentence, and it's length
        rand_str_alph = list(set(rand_string))
        str_len = len(rand_string)

        #   randomly pick characters and indices
        for i in range(100):
            c = rand_str_alph[randint(len(rand_str_alph))]
            i = randint(str_len)

            rank_in_triv = occ_trivial.rank(c, i)
            rank_in_tree = occ_wave_tree.rank(c, i)

            log.debug('\tOcc(%c, %d), WL-tree: %d, trivial: %d',
                      c, i, rank_in_tree, rank_in_triv)

            if rank_in_tree != rank_in_triv:
                raise "Occ table discrepancy"

    log.info('Passed validation testing')


if __name__ == '__main__':
    main()
