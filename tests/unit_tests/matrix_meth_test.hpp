#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_meth : public ::testing::Test {
    protected:
        std::vector<int> matrix_data1 = {-14, 0, 3, 5, 11, 20, 21, 28, 42};
        std::vector<int> matrix_data2 = {-14, 0, 3, 5, 0, 20, 21, 28, 42};
        std::vector<int> matrix_data3 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::vector<int> matrix_data4 = {1, 2, 3, 4, 5, 6};
        std::vector<long> matrix_data5 = {1, 4, 7, 2, 5, 8, 3, 6, 9};
        matrix::sq_matrix_t<int> matrix1{matrix_data1, 3};
        matrix::sq_matrix_t<int> matrix2{matrix_data2, 3};
        matrix::sq_matrix_t<int> matrix3{matrix_data3, 3};
        matrix::imatrix_t<int> matrix4{matrix_data4, 2, 3};
        matrix::imatrix_t<long> matrix5{matrix_data5, 3, 3};
    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_meth, sq_transpose_test) {

    matrix1.transpose();
    ASSERT_TRUE(matrix1[0][0] == -14);
    ASSERT_TRUE(matrix1[0][1] == 5);
    ASSERT_TRUE(matrix1[0][2] == 21);

    ASSERT_TRUE(matrix1[1][0] == 0);
    ASSERT_TRUE(matrix1[1][1] == 11);
    ASSERT_TRUE(matrix1[1][2] == 28);

    ASSERT_TRUE(matrix1[2][0] == 3);
    ASSERT_TRUE(matrix1[2][1] == 20);
    ASSERT_TRUE(matrix1[2][2] == 42);
}

TEST_F(matrix_meth, transpose_test) {

    matrix4.transpose();
    ASSERT_TRUE(matrix4[0][0] == 1);
    ASSERT_TRUE(matrix4[0][1] == 4);

    ASSERT_TRUE(matrix4[1][0] == 2);
    ASSERT_TRUE(matrix4[1][1] == 5);

    ASSERT_TRUE(matrix4[2][0] == 3);
    ASSERT_TRUE(matrix4[2][1] == 6);
}

TEST_F(matrix_meth, raise_to_power_strict_test) {

    auto res_matrix = matrix5.raise_to_power(3);

    ASSERT_TRUE(res_matrix[0][0] == 468);
    ASSERT_TRUE(res_matrix[0][1] == 1062);
    ASSERT_TRUE(res_matrix[0][2] == 1656);
    ASSERT_TRUE(res_matrix[1][0] == 576);
    ASSERT_TRUE(res_matrix[1][1] == 1305);
    ASSERT_TRUE(res_matrix[1][2] == 2034);
    ASSERT_TRUE(res_matrix[2][0] == 684);
    ASSERT_TRUE(res_matrix[2][1] == 1548);
    ASSERT_TRUE(res_matrix[2][2] == 2412);
}

TEST_F(matrix_meth, raise_to_power) {

    int power = 11;
    auto res_matrix = matrix5.raise_to_power(power);
    auto copy_res = matrix5;
    for (int i = 2; i <= power; i++)
        copy_res = copy_res * matrix5;;

    ASSERT_TRUE(copy_res == res_matrix);
}

TEST_F(matrix_meth, find_det) {

    ASSERT_TRUE(matrix1.find_det() == 1099);
    ASSERT_TRUE(matrix2.find_det() == 8260);
    ASSERT_TRUE(matrix3.find_det() == 0);
}

TEST_F(matrix_meth, swap_rows) {

    matrix1.swap_rows(0, 1);

    ASSERT_TRUE(matrix1[0][0] == 5);
    ASSERT_TRUE(matrix1[0][1] == 11);
    ASSERT_TRUE(matrix1[0][2] == 20);

    ASSERT_TRUE(matrix1[1][0] == -14);
    ASSERT_TRUE(matrix1[1][1] == 0);
    ASSERT_TRUE(matrix1[1][2] == 3);

    ASSERT_TRUE(matrix1[2][0] == 21);
    ASSERT_TRUE(matrix1[2][1] == 28);
    ASSERT_TRUE(matrix1[2][2] == 42);
}



