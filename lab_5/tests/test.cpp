#include <numeric>
#include <gtest/gtest.h>
#include "../src/LinkedList.h"
#include "../src/CustomMemoryResource.h"

template<class T>
bool cmp(LinkedList<T, std::pmr::polymorphic_allocator<T>> list1, std::vector<T> list2) {
    if (list1.get_size() != list2.size()) return false;
    auto i = 0;
    for (auto item1 : list1) {
        if (item1 != list2[i]) return false;
        ++i;
    }
    return true;
}

TEST(ListTests, ShouldCreateListCorrectly){
    CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto list1 = LinkedList<int, std::pmr::polymorphic_allocator<int>>({1,2,3}, allocator);
    auto list2 = std::vector<int>({1,2,3});

    EXPECT_TRUE(cmp(list1, list2));
}

TEST(ListTests, ShouldCreateListCorrectlyWithPushBack){
    CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto list1 = LinkedList<int, std::pmr::polymorphic_allocator<int>>(allocator);

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    auto list2 = std::vector<int>({1,2,3});

    EXPECT_TRUE(cmp(list1, list2));
}

TEST(ListTests, ShouldRemoveItemCorrectly){
    CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto list1 = LinkedList<int, std::pmr::polymorphic_allocator<int>>({1,2,3}, allocator);
    list1.pop_front();
    auto list2 = std::vector<int>({2,3});

    EXPECT_TRUE(cmp(list1, list2));
}

TEST(ListTests, ShouldCreateCorrectlyWithComplicatedType){
    CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<std::pair<int, int>> allocator(&customResource);

    auto list1 = LinkedList<std::pair<int, int>, std::pmr::polymorphic_allocator<std::pair<int, int>>>(allocator);

    list1.push_back(std::pair(1,2));
    list1.push_back(std::pair(3,4));
    list1.push_back(std::pair(5,6));

    auto list2 = std::vector<std::pair<int, int>>({
        std::pair(1,2),
        std::pair(3,4),
        std::pair(5,6)
    });

    EXPECT_TRUE(cmp(list1, list2));
}

TEST(AllocatorTests, ShouldCreateUsedBlocksCorrectly){
    CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto list1 = LinkedList<int, std::pmr::polymorphic_allocator<int>>({1,2,3}, allocator);

    auto blocks = customResource.get_used_blocks();

    ASSERT_EQ(blocks.size(), 3);
    ASSERT_EQ(*blocks.begin(), Block(0, sizeof(int)));

    list1.push_back(4);
    list1.push_back(5);

    blocks = customResource.get_used_blocks();

    ASSERT_EQ(blocks.size(), 5);
    ASSERT_EQ(*blocks.begin(), Block(0, sizeof(int)));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}