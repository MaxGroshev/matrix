#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_op : public ::testing::Test {
    protected:
        std::vector<int> matrix_data1 = {-14, 0, 3, 5, 11, 20, 21, 28, 42};
        std::vector<int> matrix_data2 = {1, 1, 1, 0, 0, 0, -1, -1, -1};
        std::vector<int> matrix_data3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> matrix_data4 = {1, 2, 3, 4, 5, 6};
        matrix::sq_matrix_t<int> matrix1{matrix_data1, 3};
        matrix::sq_matrix_t<int> matrix2{matrix_data2, 3};
        matrix::sq_matrix_t<int> matrix3{matrix_data3, 3};
        matrix::imatrix_t<int> matrix4{matrix_data4, 3, 2};

    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_op, brackets_test) {

    ASSERT_TRUE(matrix1[0][0] == -14);
    ASSERT_TRUE(matrix1[0][1] == 0);
    ASSERT_TRUE(matrix1[0][2] == 3);

    ASSERT_TRUE(matrix1[1][0] == 5);
    ASSERT_TRUE(matrix1[1][1] == 11);
    ASSERT_TRUE(matrix1[1][2] == 20);

    ASSERT_TRUE(matrix1[2][0] == 21);
    ASSERT_TRUE(matrix1[2][1] == 28);
    ASSERT_TRUE(matrix1[2][2] == 42);
}

TEST_F(matrix_op, add_matrix) {

    matrix::imatrix_t<int> res_matrix = matrix1 + matrix2;
    ASSERT_TRUE(res_matrix[0][0] == -13);
    ASSERT_TRUE(res_matrix[0][1] == 1);
    ASSERT_TRUE(res_matrix[0][2] == 4);

    ASSERT_TRUE(res_matrix[1][0] == 5);
    ASSERT_TRUE(res_matrix[1][1] == 11);
    ASSERT_TRUE(res_matrix[1][2] == 20);

    ASSERT_TRUE(res_matrix[2][0] == 20);
    ASSERT_TRUE(res_matrix[2][1] == 27);
    ASSERT_TRUE(res_matrix[2][2] == 41);
}

TEST_F(matrix_op, sub_matrix) {

    matrix::imatrix_t<int> res_matrix = matrix1 - matrix2;
    ASSERT_TRUE(res_matrix[0][0] == -15);
    ASSERT_TRUE(res_matrix[0][1] == -1);
    ASSERT_TRUE(res_matrix[0][2] == 2);

    ASSERT_TRUE(res_matrix[1][0] == 5);
    ASSERT_TRUE(res_matrix[1][1] == 11);
    ASSERT_TRUE(res_matrix[1][2] == 20);

    ASSERT_TRUE(res_matrix[2][0] == 22);
    ASSERT_TRUE(res_matrix[2][1] == 29);
    ASSERT_TRUE(res_matrix[2][2] == 43);
}

TEST_F(matrix_op, sq_mul_matrix) {

    matrix::imatrix_t<int> res_matrix = matrix1 * matrix3;
    ASSERT_TRUE(res_matrix[0][0] == 7);
    ASSERT_TRUE(res_matrix[0][1] == -4);
    ASSERT_TRUE(res_matrix[0][2] == -15);

    ASSERT_TRUE(res_matrix[1][0] == 189);
    ASSERT_TRUE(res_matrix[1][1] == 225);
    ASSERT_TRUE(res_matrix[1][2] == 261);

    ASSERT_TRUE(res_matrix[2][0] == 427);
    ASSERT_TRUE(res_matrix[2][1] == 518);
    ASSERT_TRUE(res_matrix[2][2] == 609);
}

TEST_F(matrix_op, mul_matrix) {

    matrix::imatrix_t<int> res_matrix = matrix3 * matrix4;
    ASSERT_TRUE(res_matrix[0][0] == 22);
    ASSERT_TRUE(res_matrix[0][1] == 28);

    ASSERT_TRUE(res_matrix[1][0] == 49);
    ASSERT_TRUE(res_matrix[1][1] == 64);

    ASSERT_TRUE(res_matrix[2][0] == 76);
    ASSERT_TRUE(res_matrix[2][1] == 100);
}

TEST_F(matrix_op, mul_matrix_on_num_1) {

    matrix::imatrix_t<int> res_matrix = matrix1 * 2;
    ASSERT_TRUE(res_matrix[0][0] == -28);
    ASSERT_TRUE(res_matrix[0][1] == 0);
    ASSERT_TRUE(res_matrix[0][2] == 6);

    ASSERT_TRUE(res_matrix[1][0] == 10);
    ASSERT_TRUE(res_matrix[1][1] == 22);
    ASSERT_TRUE(res_matrix[1][2] == 40);

    ASSERT_TRUE(res_matrix[2][0] == 42);
    ASSERT_TRUE(res_matrix[2][1] == 56);
    ASSERT_TRUE(res_matrix[2][2] == 84);
}

TEST_F(matrix_op, mul_matrix_on_num_2) {

    matrix::imatrix_t<int> res_matrix = 2 * matrix1;
    ASSERT_TRUE(res_matrix[0][0] == -28);
    ASSERT_TRUE(res_matrix[0][1] == 0);
    ASSERT_TRUE(res_matrix[0][2] == 6);

    ASSERT_TRUE(res_matrix[1][0] == 10);
    ASSERT_TRUE(res_matrix[1][1] == 22);
    ASSERT_TRUE(res_matrix[1][2] == 40);

    ASSERT_TRUE(res_matrix[2][0] == 42);
    ASSERT_TRUE(res_matrix[2][1] == 56);
    ASSERT_TRUE(res_matrix[2][2] == 84);
}
