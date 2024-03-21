#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_cow_op : public ::testing::Test {
    protected:
        std::vector<int> matrix_data1 = {-14, 0, 3, 5, 11, 20, 21, 28, 42};
        std::vector<int> matrix_data2 = {1, 1, 1, 0, 0, 0, -1, -1, -1};
        std::vector<int> matrix_data3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> matrix_data4 = {1, 2, 3, 4, 5, 6};
        matrix::lazy_matrix_t<int> matrix1{matrix_data1, 3, 3};
        matrix::lazy_matrix_t<int> matrix2{matrix_data2, 3, 3};
        matrix::lazy_matrix_t<int> matrix3{matrix_data3, 3, 3};
        matrix::imatrix_t<int> matrix4{matrix_data4, 3, 2};

    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_cow_op, add_matrix) {

    matrix::lazy_matrix_t<int> copy_before{matrix3};
    matrix3 = matrix1 + matrix2;
    ASSERT_TRUE(matrix3[0][0] == -13);
    ASSERT_TRUE(matrix3[0][1] == 1);
    ASSERT_TRUE(matrix3[0][2] == 4);
    ASSERT_TRUE(matrix3[1][0] == 5);
    ASSERT_TRUE(matrix3[1][1] == 11);
    ASSERT_TRUE(matrix3[1][2] == 20);
    ASSERT_TRUE(matrix3[2][0] == 20);
    ASSERT_TRUE(matrix3[2][1] == 27);
    ASSERT_TRUE(matrix3[2][2] == 41);

    matrix::lazy_matrix_t<int> copy_after{matrix_data3, 3, 3};
    ASSERT_TRUE(copy_before == copy_after);
}


TEST_F(matrix_cow_op, mul_matrix) {

    matrix::lazy_matrix_t<int> copy_before{matrix3};

    matrix3 = matrix3 * matrix4;
    ASSERT_TRUE(matrix3[0][0] == 22);
    ASSERT_TRUE(matrix3[0][1] == 28);
    ASSERT_TRUE(matrix3[1][0] == 49);
    ASSERT_TRUE(matrix3[1][1] == 64);
    ASSERT_TRUE(matrix3[2][0] == 76);
    ASSERT_TRUE(matrix3[2][1] == 100);

    matrix::lazy_matrix_t<int> copy_after{matrix_data3, 3, 3};
    ASSERT_TRUE(copy_before == copy_after);
}

TEST_F(matrix_cow_op, mul_matrix_on_num_1) {


    matrix::lazy_matrix_t<int> copy_before{matrix1};
    matrix::lazy_matrix_t<int> copy_before2{matrix1};
    matrix3 = matrix1 * 2;

    ASSERT_TRUE(matrix3[0][0] == -28);
    ASSERT_TRUE(matrix3[0][1] == 0);
    ASSERT_TRUE(matrix3[0][2] == 6);
    ASSERT_TRUE(matrix3[1][0] == 10);
    ASSERT_TRUE(matrix3[1][1] == 22);
    ASSERT_TRUE(matrix3[1][2] == 40);
    ASSERT_TRUE(matrix3[2][0] == 42);
    ASSERT_TRUE(matrix3[2][1] == 56);
    ASSERT_TRUE(matrix3[2][2] == 84);

    matrix::lazy_matrix_t<int> copy_after{matrix_data1, 3, 3};
    ASSERT_TRUE(copy_before == copy_after);
    ASSERT_TRUE(copy_before == copy_before2);

}

