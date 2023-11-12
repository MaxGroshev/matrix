#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_meth : public ::testing::Test {
    protected:
        std::vector<int> matrix_data1 = {-14, 0, 3, 5, 11, 20, 21, 28, 42};
        std::vector<int> matrix_data2 = {-14, 0, 3, 5, 0, 20, 21, 28, 42};
        std::vector<int> matrix_data3 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        matrix::sq_matrix_t<int> matrix1{matrix_data1, 3};
        matrix::sq_matrix_t<int> matrix2{matrix_data2, 3};
        matrix::sq_matrix_t<int> matrix3{matrix_data3, 3};
    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_meth, transpose_test) {

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

TEST_F(matrix_meth, find_det) {

    ASSERT_TRUE(matrix1.find_det() == 1099);
    ASSERT_TRUE(matrix2.find_det() == 8260);
    ASSERT_TRUE(matrix3.find_det() == 0);
}



