"""
Defines a binary wavelet tree class,
as well as some tests.
"""

from BitStringRank import BitStringRank
import numpy as np
import logging

log = logging.getLogger(__name__)


def calc_pivot(alph, counts):
    """
    Calculates the ideal pivot given an
    alphabeth and character counts.

    The ideal pivot is such that will give
    the least difference of the number of characters
    that are less then pivot and those that are
    greater or equal to the pivot.

    :param alph: All the characters
        in the string, ***sorted ascending***.

    :param counts: A dict of characters
        to their counts in the string.
    """
    scores = np.zeros(len(alph))
    for ind, char in enumerate(alph):

        #   calculate the number of 0s and 1s
        sum_before = sum([counts[c] for c in alph[:ind]])
        sum_after = sum([counts[c] for c in alph[ind:]])

        #   calculate diff between numbers of 0s and 1s
        scores[ind] = abs(sum_before - sum_after)

        #   if current score is worse then prev, then prev is
        #   the best, continuing will only give worse scores
        if (ind > 0) & (scores[ind] > scores[ind - 1]):
            return alph[ind - 1]

    return alph[-1]


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
        alph = sorted(set(string))

        #   get char counts in the string
        counts = dict(zip(alph, [0] * len(alph)))
        for c in string:
            counts[c] += 1

        #   construct a binary Wavelet tree
        #   each node is a tuple of form
        #       (pivot, BitStringRank, left-child, right-child)
        def create_node(string, alph, counts):

            #   if alph consists of less then 2 characters
            #   then there is no need for this node
            if len(alph) < 2:
                return None

            #   we'll need this a lot
            str_len = len(string)

            #   get the optimal pivot for this node
            pivot = calc_pivot(alph, counts)

            #   create the bitstring (and it's inverse)
            bitstring = [c >= pivot for c in string]

            #   create strings for each node
            #   determine their sizes based on bitstring rank
            bistring_rank = BitStringRank(bitstring, l)
            right_string = [0] * bistring_rank.rank(str_len)
            left_string = [0] * (str_len - len(right_string))

            #   populate strings for each node with appropriate values
            left_ind = 0
            right_ind = 0
            for c in string:
                if c >= pivot:
                    right_string[right_ind] = c
                    right_ind += 1
                else:
                    left_string[left_ind] = c
                    left_ind += 1

            #   calculate the alphabeths for both nodes
            left_alph = alph[:alph.index(pivot)]
            right_alph = alph[alph.index(pivot):]

            #   create the actual nodes
            left_node = create_node(left_string, left_alph, counts)
            right_node = create_node(right_string, right_alph, counts)

            #   return this node
            return (pivot, bistring_rank, left_node, right_node)

        self.root = create_node(string, alph, counts)

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

        #   go down the tree
        node = self.root

        rank = i
        while (node is not None) & (rank != 0):

            #   rank in the bitstring for this node
            rank_prev = rank
            rank = node[1].rank(rank_prev)

            #   check if c is less then pivot
            if c < node[0]:
                #   we need the count of zeros
                rank = rank_prev - rank
                log.debug('Rank in node (left) (%c) = %d', node[0], rank)
                node = node[2]

            #   c is greater or equal to pivot
            else:
                log.debug('Rank in node (right) (%c) = %d', node[0], rank)
                node = node[3]

        return rank
