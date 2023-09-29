import subprocess
import argparse
import os
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

test_data = {

}

# -----------------------------------------------------------------------------------------

def check_output_data(n_of_test, stdout_data, correct_res):
    print('------------------------------')
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
    print(TERMINAL_COLORS.OKBLUE                  + \
            f"Total num of tests = {n_of_test}\n" + \
            f"Num of passed      = {passed_test}" + \
    TERMINAL_COLORS.DEFAULT
    )
    print('==============================')


# -----------------------------------------------------------------------------------------

def run_triangles(name_of_testing_prog, test_case):
    dat_file = open(test_case)

    pipe = Popen([name_of_testing_prog], stdout = PIPE, stdin = dat_file)

    stdout_data = (pipe.communicate())
    string_data = str(stdout_data[0].decode())
    conver_output = string_data.split()
    conver_output = [int(n) for n in conver_output]

    return conver_output


def run_test_data(test_data, name_of_testing_prog):
    n_of_trians = []

    passed_test = 0
    n_of_test = 0
    for (test_case, n_of_test) in zip(test_data, range(len(test_data))):
        n_of_trians = run_triangles(name_of_testing_prog, test_case)
        if (check_output_data(n_of_test + 1, n_of_trians, test_data[test_case])):
            passed_test += 1
    show_total_test_stat(n_of_test + 1, passed_test)

# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
    # dir = os.path.abspath(__file__)
    print(dir)
    run_test_data(test_data, "")
