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

    def __init__(self, string, bucket_size):
        """
        Creates the BitStringRank object.

        :param string: An iterable consisting of 0s and 1s,
            can be numeric or text.

        :param bucket_size: Bucket size.
        """
        super(BitStringRank, self).__init__()
        assert(bucket_size > 1)

        self.string = [bool(c) for c in string]
        self.n = len(string)
        self.bucket_size = bucket_size
        superbucket_size = bucket_size ** 2

        #   create the buckets
        self.buckets = np.zeros(self.n / bucket_size + 1, np.uint8)
        self.superbuckets = np.zeros(self.n / bucket_size ** 2 + 1, np.int)

        #   populate the buckets with values
        current_sum = 0
        #   iterate through the string
        for ind, value in enumerate(self.string):

            #   increment current sum
            current_sum += value

            #   when at the last element of the current bucket
            #   update the next bucket's size
            if (ind % bucket_size == (bucket_size - 1)):

                #   index of the next bucket
                bucket_ind = ind / self.bucket_size + 1
                #   index of the superbucket the next bucket belongs to
                superbucket_ind = bucket_ind / self.bucket_size

                #   update superbucket when crossing
                #   the superbucket boundary
                if ind % superbucket_size == (superbucket_size - 1):
                    self.superbuckets[superbucket_ind] = current_sum

                #   update the bucket relative to it's superbucket
                self.buckets[bucket_ind] = current_sum - \
                    self.superbuckets[superbucket_ind]

    def rank(self, i):
        """
        Returns the number of bits set (having the value 1)
        in the first i bits of this bit string.

        :param i: See above.
        """
        assert (i >= 0) & (i <= self.n)

        bucket_ind = i / self.bucket_size
        superbucket_ind = bucket_ind / self.bucket_size
        return self.superbuckets[superbucket_ind] + \
            self.buckets[bucket_ind] + \
            sum(self.string[bucket_ind * self.bucket_size: i])
