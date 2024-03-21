#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_big_five : public ::testing::Test {
    protected:
        std::vector<int> matrix_data1 = {-14, 0, 3, 5, 11, 20, 21, 28, 42};
        matrix::sq_matrix_t<int> matrix1{matrix_data1, 3};

    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_big_five, copy_constructor) {

    matrix::sq_matrix_t<int> copy_matrix{matrix1};

    ASSERT_TRUE(matrix1.row_size_ == copy_matrix.row_size_);

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

TEST_F(matrix_big_five, copy_assignment) {

    std::cout << "Inited test\n";
    matrix::sq_matrix_t<int> matrix2{matrix_data1, 3};
    std::cout << "Inited mx\n";

    matrix2 = matrix1;
    std::clog << "End of copy\n" << std::endl;
    ASSERT_TRUE(matrix1.row_size_ == matrix2.row_size_);

    ASSERT_TRUE(matrix1[0][0] == matrix2[0][0]);
    ASSERT_TRUE(matrix1[0][1] == matrix2[0][1]);
    ASSERT_TRUE(matrix1[0][2] == matrix2[0][2]);
    ASSERT_TRUE(matrix1[1][0] == matrix2[1][0]);
    ASSERT_TRUE(matrix1[1][1] == matrix2[1][1]);
    ASSERT_TRUE(matrix1[1][2] == matrix2[1][2]);
    ASSERT_TRUE(matrix1[2][0] == matrix2[2][0]);
    ASSERT_TRUE(matrix1[2][1] == matrix2[2][1]);
    ASSERT_TRUE(matrix1[2][2] == matrix2[2][2]);
}

TEST_F(matrix_big_five, move_constructor) {

    matrix::sq_matrix_t<int> matrix2{matrix_data1, 3};
    matrix::sq_matrix_t<int> move_matrix = std::move(matrix2);

    ASSERT_TRUE(move_matrix[0][0] == -14);
    ASSERT_TRUE(move_matrix[0][1] == 0);
    ASSERT_TRUE(move_matrix[0][2] == 3);
    ASSERT_TRUE(move_matrix[1][0] == 5);
    ASSERT_TRUE(move_matrix[1][1] == 11);
    ASSERT_TRUE(move_matrix[1][2] == 20);
    ASSERT_TRUE(move_matrix[2][0] == 21);
    ASSERT_TRUE(move_matrix[2][1] == 28);
    ASSERT_TRUE(move_matrix[2][2] == 42);
}

TEST_F(matrix_big_five, move_assignment) {

    matrix::sq_matrix_t<int> matrix2{matrix_data1, 3};
    matrix::sq_matrix_t<int> move_matrix = std::move(matrix2);
    ASSERT_TRUE(move_matrix[0][0] == -14);
    ASSERT_TRUE(move_matrix[0][1] == 0);
    ASSERT_TRUE(move_matrix[0][2] == 3);
    ASSERT_TRUE(move_matrix[1][0] == 5);
    ASSERT_TRUE(move_matrix[1][1] == 11);
    ASSERT_TRUE(move_matrix[1][2] == 20);
    ASSERT_TRUE(move_matrix[2][0] == 21);
    ASSERT_TRUE(move_matrix[2][1] == 28);
    ASSERT_TRUE(move_matrix[2][2] == 42);
}
