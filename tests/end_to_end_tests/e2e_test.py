import subprocess
import argparse
import os
import sys
from   subprocess import Popen, PIPE, STDOUT

# -----------------------------------------------------------------------------------------

class TERMINAL_COLORS:
        PURPLE    = '\033[95m'
        OKBLUE    = '\033[94m'
        OKCYAN    = '\033[96m'
        OKGREEN   = '\033[92m'
        YELLOW    = '\033[33m'
        BLUE      = '\033[36m'
        GREEN     = '\033[32m'

        WARNING   = '\033[93m'
        ERROR     = '\033[91m'
        RED       = '\033[91m'
        DEFAULT   = '\033[0m'
        BOLD      = '\033[1m'
        UNDERLINE = '\033[4m'

test_dir = os.path.dirname(os.path.abspath(__file__)) + "/my_chain_test_dat/"
test_chain_data = {
    (test_dir + "0.dat") : [1, 0],
    (test_dir + "1.dat") : [0, 1, 2, 3],
    (test_dir + "2.dat") : [0, 2, 3, 1],
    (test_dir + "3.dat") : [0, 1, 2],
    (test_dir + "4.dat") : [2, 1, 0],
    (test_dir + "5.dat") : [4, 3, 2, 1, 0, 6, 7, 8, 5],
    (test_dir + "6.dat") : [13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 16, 17, 18, 14],
    (test_dir + "7.dat") : [1, 0, 3, 4, 5, 2],
    (test_dir + "8.dat") : [0, 1, 2, 3, 4, 5],
    (test_dir + "9.dat") : [1, 3, 5, 7, 6, 4, 2, 0, 9, 10, 11, 12, 13, 8],
}

test_mul_data = {
    (test_dir + "100.dat") : [1],
    (test_dir + "101.dat") : [1],
    (test_dir + "102.dat") : [1],
    (test_dir + "103.dat") : [1],
    (test_dir + "104.dat") : [1],
    (test_dir + "105.dat") : [1],
    (test_dir + "106.dat") : [1],
}

data_files_names = []

# -----------------------------------------------------------------------------------------

def check_output_data(n_of_test, stdout_data, correct_res, name_of_testing_prog):
    print('\n------------', name_of_testing_prog,'-----------')
    try:
        if stdout_data == correct_res:
            print(TERMINAL_COLORS.GREEN            + \
                f"Test {n_of_test} IS PASSED:\n"   + \
                f"Prog output = {stdout_data}"     + \
            TERMINAL_COLORS.DEFAULT
            )
            return True
        else:
            print(TERMINAL_COLORS.ERROR            + \
                f"Test {n_of_test} IS FAILED:\n"   + \
                f"Prog output   = {stdout_data}\n" + \
                f"Expected      = {correct_res}"   + \
            TERMINAL_COLORS.DEFAULT
            )
            return False
    except:
        print(TERMINAL_COLORS.WARNING                   + \
            f"Test {n_of_test} fall. Prog output:\n"    + \
            stdout_data + "'"                           + \
        TERMINAL_COLORS.DEFAULT
        )
        return False
    print('------------------------------')


def show_total_test_stat(n_of_test, passed_test):
    print('===========TOTAL==============')
    print(TERMINAL_COLORS.OKBLUE                          + \
            f"Total num of tests = {n_of_test}\n"+ \
            f"Num of passed      = {passed_test}"         + \
    TERMINAL_COLORS.DEFAULT
    )
    print('==============================')

# -----------------------------------------------------------------------------------------

def parse_test_data(test_case):
    with open(test_case) as dat_file:
        correct_res = 0
        res_is_reached = False
        data = ""
        for item in dat_file:
            data = item

    start = data.find('(')
    end   = data.find(')')

    try:
        correct_res = data[start + 1:end]
        data = data[start + 1:end]
    except:
        correct_res = 0

    correct_numbers = ''.join(c if c.isdigit() else ' ' for c in correct_res).split()
    return correct_numbers

# -----------------------------------------------------------------------------------------

def run_test(name_of_testing_prog, test_case):
    dat_file = open(test_case)
    pipe = Popen([name_of_testing_prog], stdout = PIPE, stdin = dat_file)

    stdout_data = (pipe.communicate())
    string_data = (stdout_data[0].decode())
    conver_output = string_data.split()

    conver_output = [int(n) for n in conver_output]

    return conver_output


def run_test_data(name_of_testing_prog, test_dat):
    n_of_elems_in_range = 0

    passed_test = 0
    n_of_test   = 0
    # for (test_case, n_of_test) in zip(data_files_names, range(len(data_files_names))):
    for (test_case, n_of_test) in zip(test_dat, range(len(test_dat))):
        n_of_trians = run_test(name_of_testing_prog, test_case)
        if (check_output_data(n_of_test + 1, n_of_trians, test_dat[test_case], name_of_testing_prog)):
            passed_test += 1
    show_total_test_stat(n_of_test, passed_test)


# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
    run_test_data("./build/matrix/mx_order", test_chain_data)
    run_test_data("./build/matrix/mx_mul", test_mul_data)

