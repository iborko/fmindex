#!/usr/bin/python
# -*- coding: utf-8

import logging
import numpy as np
import matplotlib.pyplot as plt


log = logging.getLogger(__name__)


def plot_res_seq_len():
    log.info("Procesing results for variable sequence length")

    res_seq_len_cpu = np.loadtxt("test_res_seq_len_cpu.txt")
    log.debug("Loaded results:\n%s", res_seq_len_cpu)

    #   transform the first column to it's true nature
    res_seq_len_cpu[:, 0] = 2 ** res_seq_len_cpu[:, 0]
    #   transform the last column to microseconds per read
    res_seq_len_cpu[:, 1] *= 10 ** 6 / 10 ** 5
    res_seq_len_cpu[:, 2] *= 10 ** 6 / 10 ** 5

    log.debug("Plotting search time")
    plt.figure(figsize=(12, 9), dpi=72)

    plt.plot(res_seq_len_cpu[:, 0], res_seq_len_cpu[:, 1], "o-",
             label=u"Stablo valića")
    plt.plot(res_seq_len_cpu[:, 0], res_seq_len_cpu[:, 2], "o-",
             label=u"Trivijalna Occ")
    plt.xlim([res_seq_len_cpu[0, 0] / 2, res_seq_len_cpu[-1, 0] * 2])
    plt.xscale('log')
    plt.xlabel("Duljina indeksiranog niza")
    margin = res_seq_len_cpu[0, 2]
    plt.ylim([res_seq_len_cpu[0, 2] - margin, res_seq_len_cpu[-1, 1] + margin])
    plt.ylabel(u"Vrijeme pretraživanja / \u00B5s")
    plt.grid()
    plt.legend(loc=2)
    plt.savefig("test_res_seq_len_cpu.pdf", bbox_inches='tight')

    log.debug("Plotting memory consumption")
    res_seq_len_mem = np.loadtxt("test_res_seq_len_mem.txt")
    log.debug("Loaded results:\n%s", res_seq_len_mem)
    res_seq_len_mem[:, 0] = 2 ** res_seq_len_mem[:, 0]
    plt.figure(figsize=(12, 9), dpi=72)

    plt.plot(res_seq_len_mem[:, 0], res_seq_len_mem[:, 1], "o-",
             label=u"Stablo valića")
    plt.plot(res_seq_len_mem[:, 0], res_seq_len_mem[:, 2], "o-",
             label=u"Trivijalna Occ")
    plt.xlim([res_seq_len_mem[0, 0] / 2, res_seq_len_mem[-1, 0] * 2])
    plt.xscale('log')
    plt.xlabel(u"Duljina indeksiranog niza")
    plt.ylabel(u"Utrošak memorije / MB")
    plt.yscale("log")
    plt.grid()
    plt.legend(loc=2)

    plt.savefig("test_res_seq_len_mem.pdf", bbox_inches='tight')


def plot_res_query_len():
    log.info("Procesing results for variable query length")

    res_query_len = np.loadtxt("test_res_query_len.txt")
    log.debug("Loaded results:\n%s", res_query_len)

    #   transform the last column to microseconds per read
    res_query_len[:, 1] *= 10 ** 6 / 10 ** 5

    plt.figure(figsize=(12, 9), dpi=72)

    plt.plot(res_query_len[:, 0], res_query_len[:, 1], "o-")
    plt.xlim([res_query_len[0, 0] / 2, res_query_len[-1, 0] * 2])
    plt.xscale('log')
    plt.xlabel(u"Duljina očitka")
    plt.ylim([res_query_len[0, 1] / 2, res_query_len[-1, 1] * 2])
    plt.yscale('log')
    plt.ylabel(u"Vrijeme pretrazivanja / \u00B5s")
    plt.grid()

    plt.savefig("test_res_query_len.pdf", bbox_inches='tight')


def main():
    logging.basicConfig(level=logging.DEBUG)
    log.info("Generating plots for FM-index test results")

    plot_res_seq_len()
    plot_res_query_len()


if __name__ == '__main__':
    main()
