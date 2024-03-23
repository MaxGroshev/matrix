import subprocess
import argparse
import random
import numpy as np
import os
import sys

# -----------------------------------------------------------------------------------------

def print_test_data(args, test_data):
    dat_file = open(args.data, "w")


    dat_file.write(" %d\n\n"%  args.power)
    dat_file.write(" %d   %d\n\n"%  (args.size[0], args.size[1]))
    for i in range (0, args.size[0]):
        row = test_data[i]
        for j in range (0, args.size[1]):
            dat_file.write("%d "% row[j])
        dat_file.write("\n")

    dat_file.write("\n")
    dat_file.close()



    ans_file = open(args.ans, "w")

    ans_file.write("%d"%  1)

    ans_file.close()



def gen_mx(args):

    matrix = []
    for i in range(0, args.size[0]):
        row = []
        for j in range(0, args.size[1]):
            row.append(random.randint(args.diaposon[0], args.diaposon[1]))
        matrix.append(row)

    return matrix


# -----------------------------------------------------------------------------------------

def add_parse_arguments(parser):
    parser.add_argument("-p",  "--power",       type = int, default = 5)
    parser.add_argument("-s",  "--size",        nargs = 2, type = int, default = [3, 3])
    parser.add_argument('-d',  "--diaposon",    nargs = 2, type = int, default = [-10, 10])
    parser.add_argument('-dat',  '--data',        type = str, default =
                    os.path.dirname(os.path.abspath(__file__)) + '/my_cow_dat/gen_test.dat')
    parser.add_argument('-ans',  '--ans',        type = str, default =
                os.path.dirname(os.path.abspath(__file__)) + '/my_cow_ans/gen_test.dat')

# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    add_parse_arguments(parser)
    args = parser.parse_args()
    # check_args(args)

    test_data = gen_mx(args)
    print_test_data(args, test_data)


