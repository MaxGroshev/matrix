#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_cow : public ::testing::Test {
    protected:
        std::vector<int> matrix_data1 = {-14, 0, 3, 5, 11, 20, 21, 28, 42};
        matrix::imatrix_t<int> matrix1{matrix_data1, 3, 3};

    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_cow, copy_constructor) {

    matrix::imatrix_t<int> copy_matrix{matrix1};

    ASSERT_TRUE(matrix1.row_size_ == copy_matrix.row_size_);
    ASSERT_TRUE(matrix1.data_ == copy_matrix.data_);
    // std::cout << "I AM HERE" << std::endl;
}

// TEST_F(matrix_cow, copy_assignment) {
//
//     matrix::sq_matrix_t<int> copy_matrix = matrix1;
//
//     ASSERT_TRUE(matrix1.row_size_ == copy_matrix.row_size_);
//
//     ASSERT_TRUE(matrix1[0][0] == copy_matrix[0][0]);
//     ASSERT_TRUE(matrix1[0][1] == copy_matrix[0][1]);
//     ASSERT_TRUE(matrix1[0][2] == copy_matrix[0][2]);
//
//     ASSERT_TRUE(matrix1[1][0] == copy_matrix[1][0]);
//     ASSERT_TRUE(matrix1[1][1] == copy_matrix[1][1]);
//     ASSERT_TRUE(matrix1[1][2] == copy_matrix[1][2]);
//
//     ASSERT_TRUE(matrix1[2][0] == copy_matrix[2][0]);
//     ASSERT_TRUE(matrix1[2][1] == copy_matrix[2][1]);
//     ASSERT_TRUE(matrix1[2][2] == copy_matrix[2][2]);
// }
