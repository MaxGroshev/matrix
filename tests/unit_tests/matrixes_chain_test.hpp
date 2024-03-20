#pragma once

using namespace matrix;

//-----------------------------------------------------------------------------------------

class matrix_mul_order : public ::testing::Test {
    protected:
        matrix::imatrix_t<int> matrix1{23, 26, 1};
        matrix::imatrix_t<int> matrix2{26, 27, 2};
        matrix::imatrix_t<int> matrix3{27, 20, 3};
        chain_t<imatrix_t<int>> mx_chain1;
        std::vector<int> correct_mx1 = {0, 1};


        matrix::imatrix_t<int> matrix4{5, 10};
        matrix::imatrix_t<int> matrix5{10, 15};
        matrix::imatrix_t<int> matrix6{15, 20};
        matrix::imatrix_t<int> matrix7{20, 25};
        chain_t<imatrix_t<int>> mx_chain2;
        std::vector<int> correct_mx2 = {2, 1, 0};


        matrix::imatrix_t<int> matrix8{100, 5};
        matrix::imatrix_t<int> matrix9{5, 100};
        matrix::imatrix_t<int> matrix10{100, 10};
        matrix::imatrix_t<int> matrix11{10, 1};
        chain_t<imatrix_t<int>> mx_chain3;
        std::vector<int> correct_mx3 = {0, 1, 2};


        matrix::imatrix_t<int> matrix12{4, 10};
        matrix::imatrix_t<int> matrix13{10, 3};
        matrix::imatrix_t<int> matrix14{3, 12};
        matrix::imatrix_t<int> matrix15{12, 20};
        matrix::imatrix_t<int> matrix16{20, 7};
        chain_t<imatrix_t<int>> mx_chain4;
        std::vector<int> correct_mx4 = {1, 3, 2, 0};

    void SetUp() {
        mx_chain1.push_back(matrix1);
        mx_chain1.push_back(matrix2);
        mx_chain1.push_back(matrix3);

        mx_chain2.push_back(matrix4);
        mx_chain2.push_back(matrix5);
        mx_chain2.push_back(matrix6);
        mx_chain2.push_back(matrix7);

        mx_chain3.push_back(matrix8);
        mx_chain3.push_back(matrix9);
        mx_chain3.push_back(matrix10);
        mx_chain3.push_back(matrix11);

        mx_chain4.push_back(matrix12);
        mx_chain4.push_back(matrix13);
        mx_chain4.push_back(matrix14);
        mx_chain4.push_back(matrix15);
        mx_chain4.push_back(matrix16);
    }
};

class matrix_chain_mul : public ::testing::Test {
    protected:
        matrix::imatrix_t<int> matrix1{1, 2, 1};
        matrix::imatrix_t<int> matrix2{2, 3, 2};
        matrix::imatrix_t<int> matrix3{3, 4, 3};
        matrix::imatrix_t<int> matrix4{4, 5, 4};

    void SetUp() {
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(matrix_mul_order, get_num_of_mul1) {

    int chain_size = mx_chain1.size();
    imatrix_t<std::pair<int, int>> cache {chain_size + 1, chain_size + 1, {-1, -1}};
    ASSERT_TRUE(mx_chain1.get_num_of_mul(cache, 1, chain_size) == 26000);

    mx_chain1.find_best_order(cache, 1, chain_size);
    ASSERT_TRUE(mx_chain1.get_mul_order() == correct_mx1);
//
//     std::cout  << "------------------------------\n";
//     std::cout  << "Print of matrix:\n";
//     std::cout  << "Column_size: " << cache.column_size_ << '\n';
//     std::cout  << "Row_size:    " << cache.row_size_;
//
//     for (int i = 0; i < cache.column_size_ * cache.row_size_; i++) {
//         if (i % cache.row_size_ == 0)
//             std::cout << '\n';
//         std::cout << "[{" << cache.data_[i].first << " , " << cache.data_[i].second << "}] ";
//     }
//     std::cout << "\n------------------------------";
//     std::cout << '\n';
}

TEST_F(matrix_mul_order, get_num_of_mul2) {

    int chain_size = mx_chain2.size();
    imatrix_t<std::pair<int, int>> cache {chain_size + 1, chain_size + 1, {-1, -1}};
    ASSERT_TRUE(mx_chain2.get_num_of_mul(cache, 1, chain_size) == 4750);

    mx_chain2.find_best_order(cache, 1, chain_size);
    ASSERT_TRUE(mx_chain2.get_mul_order() == correct_mx2);

}

TEST_F(matrix_mul_order, get_num_of_mul3) {

    int chain_size = mx_chain3.size();
    imatrix_t<std::pair<int, int>> cache {chain_size + 1, chain_size + 1, {-1, -1}};
    ASSERT_TRUE(mx_chain3.get_num_of_mul(cache, 1, chain_size) == 2000);

    mx_chain3.find_best_order(cache, 1, chain_size);
    ASSERT_TRUE(mx_chain3.get_mul_order() == correct_mx3);
}

TEST_F(matrix_mul_order, get_num_of_mul4) {

    int chain_size = mx_chain4.size();
    imatrix_t<std::pair<int, int>> cache {chain_size + 1, chain_size + 1, {-1, -1}};
    ASSERT_TRUE(mx_chain4.get_num_of_mul(cache, 1, chain_size) == 1344);

    mx_chain4.find_best_order(cache, 1, chain_size);
    ASSERT_TRUE(mx_chain4.get_mul_order() == correct_mx4);
}

TEST_F(matrix_chain_mul, mx_mul1) {

    chain_t<imatrix_t<int>> mx_chain;
    mx_chain.push_back(matrix1);
    mx_chain.push_back(matrix2);
    mx_chain.push_back(matrix3);
    mx_chain.push_back(matrix4);

    matrix::imatrix_t<int> res_matrix = mx_chain.mul();
    res_matrix.print();
    ASSERT_TRUE(res_matrix[0][0] == 576);
    ASSERT_TRUE(res_matrix[0][1] == 576);
    ASSERT_TRUE(res_matrix[0][2] == 576);
    ASSERT_TRUE(res_matrix[0][3] == 576);
    ASSERT_TRUE(res_matrix[0][4] == 576);
}
