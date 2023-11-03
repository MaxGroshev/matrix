#pragma once

using namespace avl;

//-----------------------------------------------------------------------------------------

class big_five : public ::testing::Test {
    protected:
    avl::tree_t<int, int> tree;
    std::vector<int> correct_tree = {-14, 0, 3, 5, 11, 20, 21, 28, 42, 60};
    void SetUp() {
        std::array<int, 10> data = {5, 20, 21, -14, 0, 3, 42, 11, 60, 28};
        for (const auto& key : data) {
            tree.insert(key, key);
        }
    }
};

//-----------------------------------------------------------------------------------------

TEST_F(big_five, constructor_test) {
    std::vector<int> storage;
    tree.store_inorder_walk(&storage);
    ASSERT_TRUE(storage == correct_tree);
}

TEST_F(big_five, copy_constructor_test) {
    tree_t<int, int> pine {tree};
    std::vector<int> tree_storage;
    std::vector<int> pine_storage;
    tree.store_inorder_walk(&tree_storage);
    pine.store_inorder_walk(&pine_storage);

    ASSERT_TRUE(tree_storage == correct_tree);
    ASSERT_TRUE(pine_storage == correct_tree);
}
