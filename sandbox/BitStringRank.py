"""
Defines a class that performs constant-time
ranking on bit strings, as well as some tests.

IMPORTANT:
This implementation is for algorithm explanation
only, it is not for production use, due to
it's memory consumption. It is very important
for a bit string to be stored as efficiently as possible,
which this implementation dues not guarantee.
"""
import numpy as np
import logging

log = logging.getLogger(__name__)


class BitStringRank(object):
    """
    Class  that performs constant-time
    ranking on bit strings.

    A  bit-string 'rank' for a given index
    is the number of bits set to {0, 1} up until
    and including the index.
    """

    def __init__(self, string, l):
        """
        Creates the BitStringRank object.

        :param string: An iterable consisting of 0s and 1s,
            can be numeric or text.

        :param l: Bucket size.
        """
        super(BitStringRank, self).__init__()

        self.string = [bool(c) for c in string]
        self.n = len(string)
        self.l = l

        #   create the buckets
        self.buckets = np.zeros(self.n / l + 1, np.uint8)
        self.superbuckets = np.zeros(self.n / l ** 2 + 1, np.int)

        #   populate the buckets with values
        current_sum = 0
        #   iterate through the string
        for ind, value in enumerate(self.string):

            #   if we are entering a new bucket
            #   then store the results
            if (ind % l == 0) & (ind != 0):

                #   indexes of bucket and superbucket
                #   for current index
                bucket_ind = ind / self.l
                superbucket_ind = bucket_ind / self.l

                #   update superbucket when crossing
                #   the superbucket boundary
                if ind % l ** 2 == 0:
                    self.superbuckets[superbucket_ind] = current_sum

                #   update the bucket relative to the current
                #   superbucket
                self.buckets[bucket_ind] = current_sum - \
                    self.superbuckets[superbucket_ind]

            #   increment current sum
            current_sum += value

    def rank(self, i):
        """
        Returns the number of bits set (having the value 1)
        in the first i bits of this bit string.

        :param i: See above.
        """
        assert i <= self.n

        if i == 0:
            return 0

        bucket_ind = i / self.l
        superbucket_ind = bucket_ind / self.l
        return self.superbuckets[superbucket_ind] + \
            self.buckets[bucket_ind] + \
            sum(self.string[bucket_ind * self.l: i])
