import subprocess
import argparse
import random
import numpy as np
import os
import sys

# -----------------------------------------------------------------------------------------

def print_test_data(args, test_data):
    dat_file = open(args.file, "w")

    dat_file.write("%d\n\n"%  args.size)
    for i in range(len(test_data)):
        for j in range(len(test_data[i])):
            dat_file.write("%d "%  test_data[i][j])
        dat_file.write("\n")
    dat_file.write("\n(%d)"%  (args.determinant))

    dat_file.close()


def generate_test_data(args):
    diag_matrix     = []
    allowed_values = list(range(args.diaposon[0], args.diaposon[1]))
    allowed_values.remove(0)

    for i in range(args.size):
        row = []
        for j in range(args.size):
            if (i == 0 and j == 0):
                row.append(args.determinant)
            elif (j < i):
                row.append(0)
            elif (i == j):
                row.append(1)
            else:
                row.append(random.choice(allowed_values))
        diag_matrix.append(row)

    np_matrix  = np.array(diag_matrix)
    print (np.linalg.det(np_matrix), '\n')
    # print(np_matrix)
    rand_matrix = randomize_matrix(args, np_matrix)
    # print (rand_matrix)
    # print (np.linalg.det(rand_matrix), '\n')
    rand_matrix = np.transpose(rand_matrix)
    # print (np.linalg.det(rand_matrix), '\n')
    rand_matrix = randomize_matrix(args, rand_matrix)
    # print (np.linalg.det(rand_matrix), '\n')

    return rand_matrix

def calculate_diag_matrix_det(diag_matrix):
    det = 1
    for i in range(args.size):
        det *= diag_matrix[i][i]
    return det

def randomize_matrix(args, np_matrix):
    allowed_values = list(range(0, args.size))

    i = 0
    while (i < len(allowed_values) * 10):
        rand_row1 = random.choice(allowed_values)
        rand_row2 = random.choice(allowed_values)
        if (rand_row2 == rand_row1):
            continue
        np_matrix[[rand_row2, rand_row1]] = np_matrix[[rand_row1, rand_row2]]
        i += 2

    return np_matrix


# -----------------------------------------------------------------------------------------

def add_parse_arguments(parser):
    parser.add_argument("-s",  "--size",    type = int, default = 10)
    parser.add_argument('-det',"--determinant", type = int, default = 50)
    parser.add_argument('-d',  "--diaposon",nargs = 2, type = int, default = [-10, 10])
    parser.add_argument('-f',  '--file',    type = str, default =
                    os.path.dirname(os.path.abspath(__file__)) + '/my_test_data/gen_test.dat')

# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    add_parse_arguments(parser)
    args = parser.parse_args()
    # check_args(args)

    test_data = generate_test_data(args)
    print_test_data(args, test_data)

