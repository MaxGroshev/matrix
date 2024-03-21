#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_cow : public ::testing::Test {
    protected:
        std::vector<int> matrix_data1 = {-14, 0, 3, 5, 11, 20, 21, 28, 42};
        std::vector<int> matrix_data2 = {-1432, 323, 33, 52, 151, 820, 921, 828, 492};
        std::vector<int> matrix_data3 = {-14342, 35253, 336, 562, 1751, 8820, 8921, 8428, 4392};
        matrix::lazy_matrix_t<int> matrix1{matrix_data1, 3, 3};
        matrix::lazy_matrix_t<int> matrix2{matrix_data2, 3, 3};
        matrix::lazy_matrix_t<int> matrix3{matrix_data3, 3, 3};

    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_cow, copy_constructor) {

    matrix::lazy_matrix_t<int> copy_matrix{matrix1};

    ASSERT_TRUE(matrix1.row_size_ == copy_matrix.row_size_);
    ASSERT_TRUE(matrix1.data_->data_() == copy_matrix.data_->data_());


    ASSERT_TRUE(matrix1[0][0] == copy_matrix[0][0]);
    ASSERT_TRUE(matrix1[0][1] == copy_matrix[0][1]);
    ASSERT_TRUE(matrix1[0][2] == copy_matrix[0][2]);

    ASSERT_TRUE(matrix1[1][0] == copy_matrix[1][0]);
    ASSERT_TRUE(matrix1[1][1] == copy_matrix[1][1]);
    ASSERT_TRUE(matrix1[1][2] == copy_matrix[1][2]);

    ASSERT_TRUE(matrix1[2][0] == copy_matrix[2][0]);
    ASSERT_TRUE(matrix1[2][1] == copy_matrix[2][1]);
    ASSERT_TRUE(matrix1[2][2] == copy_matrix[2][2]);
}

TEST_F(matrix_cow, copy_assignment) {

    matrix::lazy_matrix_t<int> copy_matrix{matrix2};

    copy_matrix = matrix1;

    ASSERT_TRUE(matrix1.row_size_ == copy_matrix.row_size_);
    ASSERT_TRUE(matrix1.data_->data_() == copy_matrix.data_->data_());

    ASSERT_TRUE(matrix1[0][0] == copy_matrix[0][0]);
    ASSERT_TRUE(matrix1[0][1] == copy_matrix[0][1]);
    ASSERT_TRUE(matrix1[0][2] == copy_matrix[0][2]);

    ASSERT_TRUE(matrix1[1][0] == copy_matrix[1][0]);
    ASSERT_TRUE(matrix1[1][1] == copy_matrix[1][1]);
    ASSERT_TRUE(matrix1[1][2] == copy_matrix[1][2]);

    ASSERT_TRUE(matrix1[2][0] == copy_matrix[2][0]);
    ASSERT_TRUE(matrix1[2][1] == copy_matrix[2][1]);
    ASSERT_TRUE(matrix1[2][2] == copy_matrix[2][2]);
}

TEST_F(matrix_cow, complicated_copy_assignment) {

    matrix::lazy_matrix_t<int> copy_matrix{matrix2};

    matrix1 = matrix2;
    ASSERT_TRUE(matrix1.data_->data_() == matrix2.data_->data_());

    matrix2 = matrix3;
    ASSERT_TRUE(matrix2.data_->data_() == matrix3.data_->data_());
    ASSERT_TRUE(matrix1.data_->data_() != matrix2.data_->data_());


    ASSERT_TRUE(matrix1[0][0] == copy_matrix[0][0]);
    ASSERT_TRUE(matrix1[0][1] == copy_matrix[0][1]);
    ASSERT_TRUE(matrix1[0][2] == copy_matrix[0][2]);

    ASSERT_TRUE(matrix1[1][0] == copy_matrix[1][0]);
    ASSERT_TRUE(matrix1[1][1] == copy_matrix[1][1]);
    ASSERT_TRUE(matrix1[1][2] == copy_matrix[1][2]);

    ASSERT_TRUE(matrix1[2][0] == copy_matrix[2][0]);
    ASSERT_TRUE(matrix1[2][1] == copy_matrix[2][1]);
    ASSERT_TRUE(matrix1[2][2] == copy_matrix[2][2]);


    ASSERT_TRUE(matrix2[0][0] == matrix3[0][0]);
    ASSERT_TRUE(matrix2[0][1] == matrix3[0][1]);
    ASSERT_TRUE(matrix2[0][2] == matrix3[0][2]);
    ASSERT_TRUE(matrix2[1][0] == matrix3[1][0]);
    ASSERT_TRUE(matrix2[1][1] == matrix3[1][1]);
    ASSERT_TRUE(matrix2[1][2] == matrix3[1][2]);
    ASSERT_TRUE(matrix2[2][0] == matrix3[2][0]);
    ASSERT_TRUE(matrix2[2][1] == matrix3[2][1]);
    ASSERT_TRUE(matrix2[2][2] == matrix3[2][2]);
}


