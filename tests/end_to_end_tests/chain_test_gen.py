import subprocess
import argparse
import random
import numpy as np
import os
import sys

# -----------------------------------------------------------------------------------------

class test_data_t:
    sz_order = []
    mx_order = []

# -----------------------------------------------------------------------------------------

def print_test_data(args, test_data):
    dat_file = open(args.file, "w")

    for i in range(len(test_data.sz_order)):
        dat_file.write("%d "%  test_data.sz_order[i])

    dat_file.write("\n")

    if (args.mode == "mxo"):
        dat_file.write("%d\n\n"%  args.count)
        for i in range (0, args.count):
            matrix = test_data.mx_order[i]
            for j in range (test_data.sz_order[i]):
                row = matrix[j]
                for k in range (test_data.sz_order[i + 1]):
                    dat_file.write("%d "% row[k])
                dat_file.write("\n")
            dat_file.write("\n\n")

    dat_file.close()


def generate_test_data(args):
    test_data = test_data_t()

    test_order = gen_test_order(args)
    test_data.sz_order = test_order

    if (args.mode == "mxo"):
        test_mx_order = gen_mx_order(test_order, args)
        test_data.mx_order = test_mx_order

    return test_data

def gen_test_order(args):
    order = []
    for i in range(1, args.count):
        if (i == 1):
            order.append(args.res_dimension[0])
        order.append(random.randint(1, args.res_dimension[1]))

    order.append(args.res_dimension[1])
    return order

def gen_mx_order(test_order, args):
    matrixes = []

    for i in range(0, args.count):
        matrix = []
        column_size = test_order[i]
        row_size    = test_order[i + 1]

        for i in range(0, column_size):
            row = []
            for j in range(0, row_size):
                row.append(random.randint(args.diaposon[0], args.diaposon[1]))
            matrix.append(row)
        matrixes.append(matrix)

    return matrixes


# -----------------------------------------------------------------------------------------

def add_parse_arguments(parser):
    parser.add_argument("-c",  "--count",         type = int, default = 5)
    parser.add_argument('-m',  "--mode",          type = str, default = "o")
    parser.add_argument('-rd',  "--res_dimension",nargs = 2, type = int, default = [10, 10])
    parser.add_argument('-d',  "--diaposon",      nargs = 2, type = int, default = [-10, 10])
    parser.add_argument('-f',  '--file',          type = str, default =
                    os.path.dirname(os.path.abspath(__file__)) + '/my_chain_test_dat/gen_test.dat')

# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    add_parse_arguments(parser)
    args = parser.parse_args()
    # check_args(args)

    test_data = generate_test_data(args)
    print_test_data(args, test_data)

