import subprocess
import argparse
import random
import os
import sys

# -----------------------------------------------------------------------------------------

def print_test_data(args, test_data):
    dat_file = open(args.file, "w")

    dat_file.write("%d\n\n"%  args.size)
    for (data) in (test_data.values()) :
        for i in range(len(data)):
            for j in range(len(data[i])):
                dat_file.write("%d "%  data[i][j])
            dat_file.write("\n")
    for (det) in (test_data.keys()):
        dat_file.write("\n(%d)"%  (det))

    dat_file.close()


def generate_test_data(args):
    diag_matrix     = []
    diag_matrix_set = set(diag_matrix)
    allowed_values = list(range(args.diaposon[0], args.diaposon[1]))
    allowed_values.remove(0)

    for i in range(args.size):
        row = []
        for j in range(args.size):
            if (j < i):
                row.append(0)
            else:
                row.append(random.choice(allowed_values))
        diag_matrix.append(row)

    print(diag_matrix)

    det = calculate_diag_matrix_det(diag_matrix)
    det, rondomized_matrix = randomize_matrix(args, diag_matrix, det)

    print (rondomized_matrix)

    test_data = {det : rondomized_matrix}
    return test_data

def calculate_diag_matrix_det(diag_matrix):
    det = 1
    for i in range(args.size):
        det *= diag_matrix[i][i]
    return det

def randomize_matrix(args, diag_matrix, det):
    allowed_values = list(range(0, args.size - 1))

    i = 0
    while (i < len(allowed_values)):
        rand_row1 = random.choice(allowed_values)
        rand_row2 = random.choice(allowed_values)
        if (rand_row2 != rand_row1):
            det *= -1
        tmp = diag_matrix[rand_row1]
        diag_matrix[rand_row1] = diag_matrix[rand_row2]
        diag_matrix[rand_row2] = tmp
        i += 2

    return det, diag_matrix


# -----------------------------------------------------------------------------------------

def add_parse_arguments(parser):
    parser.add_argument("-s", "--size",     type = int, default = 10)
    parser.add_argument('-d', "--diaposon",nargs = 2, type = int, default = [-3, 3])
    parser.add_argument('-f', '--file',     type = str, default =
                    os.path.dirname(os.path.abspath(__file__)) + '/my_test_data/gen_test.dat')

# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    add_parse_arguments(parser)
    args = parser.parse_args()
    # check_args(args)

    test_data = generate_test_data(args)
    print_test_data(args, test_data)

