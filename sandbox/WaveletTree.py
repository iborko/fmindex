"""
Defines a binary wavelet tree class,
as well as some tests.
"""

from BitStringRank import BitStringRank
import numpy as np
import logging

log = logging.getLogger(__name__)


class WaveletTree(object):
    """
    A binary wavelet tree. It's purpose is to
    allow fast (log(|alphabeth|)) ranking.
    Ranking is determening the number of occurrences
    of a character in a (sub)string.
    """

    def __init__(self, string, l):
        """
        Creates the wavelet tree.

        :param string: The string (in any alphabeth)
            that the tree should represent.

        :param l: Bucket size for BitStringRank objects
            used for node rank queries.
        """
        super(WaveletTree, self).__init__()

        #   get the string alphabet
        self.alphabet = sorted(set(string))

        #   convert the string to alphabet indices
        assert len(self.alphabet) <= (1 << 7)
        int_string = np.array(
            [self.alphabet.index(x) for x in string], np.uint8)

        #   construct a binary Wavelet tree
        #   each node is a tuple of form
        #       (pivot, BitStringRank, left-child, right-child)
        def create_node(string, alphabet):

            #   if alphabet consists of less then 2 characters
            #   then there is no need for this node
            if len(alphabet) < 2:
                return None

            #   first look for the character that gives the
            #   best node balance (similar number of 0s and 1s)
            median = int(round(np.median(string)))
            pivots = (median - 1, median, median + 1)
            bitstrings = [string >= c for c in pivots]

            #   best pivot is one that gives the least deviation
            #   from (string_size / 2)
            best_ind = np.argmin(
                [(sum(c) - (string.size / 2)) ** 2 for c in bitstrings])

            #   found the best balancing pivot, use it
            pivot = pivots[best_ind]
            bitstring = bitstrings[best_ind]

            #   create left and right nodes
            #   first see which alphabets they consist of
            left_alphabet = alphabet[:alphabet.index(pivot)]
            right_alphabet = alphabet[alphabet.index(pivot):]
            #   then create the actual nodes
            left_node = create_node(
                string[np.logical_not(bitstring)], left_alphabet)
            right_node = create_node(
                string[bitstring], right_alphabet)

            #   return this node
            return (pivot, BitStringRank(bitstring, l), left_node, right_node)

        self.root = create_node(int_string, range(len(self.alphabet)))

    def rank(self, c, i):
        """
        Returns the number of occurrences of
        letter c up until index i in the string
        this wavelet tree represents.

        :param c: The character for which
            rank is souht.
        :param i: Index up until which the rank
            is sought.
        """

        #   we use an integer alphabet, so convert
        int_c = self.alphabet.index(c)
        log.debug('Rank for %c(%d), %d', c, int_c, i)

        #   go down the tree
        node = self.root

        rank = i
        while (node is not None) & (rank != 0):

            #   rank in the bitstring for this node
            rank_prev = rank
            rank = node[1].rank(rank_prev)

            #   check if c is less then pivot
            if int_c < node[0]:
                #   we need the count of zeros
                rank = rank_prev - rank
                log.debug('Rank in node (left) (%d) = %d', node[0], rank)
                node = node[2]

            #   c is greater or equal to pivot
            else:
                log.debug('Rank in node (right) (%d) = %d', node[0], rank)
                node = node[3]

        return rank
