#include <cstddef>
#include <gtest/gtest.h>
#include "headers/SingleList.hpp"
#include <vector>
#include <string>


TEST(SingleListTest, PushPopFront)
{
    SingleList<int> lst;
    EXPECT_TRUE(lst.empty());
    
    lst.push_front(10);
    EXPECT_FALSE(lst.empty());
    EXPECT_EQ(lst.front(), 10);

    lst.push_front(20);
    EXPECT_EQ(lst.front(), 20);

    lst.pop_front();
    EXPECT_EQ(lst.front(), 10);

    lst.pop_front();
    EXPECT_TRUE(lst.empty());
}

TEST(SingleListTest, InsertEraseAfter)
{
    SingleList<int> lst;
    lst.push_front(1);
    lst.push_front(2); // list: 2 -> 1

    SingleList<int>::iterator it = lst.begin();
    lst.insert_after(it, 3); // list: 2 -> 3 -> 1

    it = lst.begin();
    ++it;
    EXPECT_EQ(*it, 3);

    lst.erase_after(lst.begin()); // erase 3
    it = lst.begin();
    ++it;
    EXPECT_EQ(*it, 1);
}

TEST(SingleListTest, CopyConstructorAssignment)
{
    SingleList<int> lst;
    lst.push_front(5);
    lst.push_front(10); // list: 10 -> 5

    SingleList<int> lst2(lst); // copy ctor
    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2.front(), 10);

    SingleList<int> lst3;
    lst3 = lst; // operator=
    EXPECT_EQ(lst3.size(), 2);
    EXPECT_EQ(lst3.front(), 10);
}

TEST(SingleListTest, ComparisonOperators)
{
    SingleList<int> lst1, lst2;
    lst1.push_front(1);
    lst1.push_front(2); // 2->1
    lst2.push_front(1);
    lst2.push_front(2); // 2->1

    EXPECT_TRUE(lst1 == lst2);
    EXPECT_FALSE(lst1 != lst2);

    lst2.push_front(3);
    EXPECT_TRUE(lst1 < lst2);
    EXPECT_TRUE(lst2 > lst1);
}

TEST(SingleListTest, ClearAndEmpty)
{
    SingleList<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    EXPECT_FALSE(lst.empty());

    lst.clear();
    EXPECT_TRUE(lst.empty());
}

TEST(SingleListTest, Resize)
{
    SingleList<int> lst;
    lst.resize(3, 7);
    EXPECT_EQ(lst.size(), 3);

    SingleList<int>::iterator it = lst.begin();
    EXPECT_EQ(*it, 7);
    ++it;
    EXPECT_EQ(*it, 7);
    ++it;
    EXPECT_EQ(*it, 7);

    lst.resize(1, 0);
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.front(), 7);
}

TEST(SingleListTest, PushPopFront1)
{
    SingleList<int> lst;
    EXPECT_TRUE(lst.empty());

    lst.push_front(10);
    EXPECT_FALSE(lst.empty());
    EXPECT_EQ(lst.front(), 10);

    lst.push_front(20);
    EXPECT_EQ(lst.front(), 20);

    lst.pop_front();
    EXPECT_EQ(lst.front(), 10);

    lst.pop_front();
    EXPECT_TRUE(lst.empty());
}

TEST(SingleListTest, InsertAfterEraseAfter1)
{
    SingleList<int> lst;
    lst.push_front(1);
    lst.push_front(2); // 2 -> 1

    SingleList<int>::iterator it = lst.begin();
    lst.insert_after(it, 3); // 2 -> 3 -> 1

    it = lst.begin();
    ++it;
    EXPECT_EQ(*it, 3);

    lst.erase_after(lst.begin()); // erase 3
    it = lst.begin();
    ++it;
    EXPECT_EQ(*it, 1);
}

TEST(SingleListTest, CopyConstructorAssignment1)
{
    SingleList<int> lst;
    lst.push_front(5);
    lst.push_front(10); // 10 -> 5

    SingleList<int> lst2(lst); // copy ctor
    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2.front(), 10);

    SingleList<int> lst3;
    lst3 = lst; // assignment
    EXPECT_EQ(lst3.size(), 2);
    EXPECT_EQ(lst3.front(), 10);
}

TEST(SingleListTest, ComparisonOperators1)
{
    SingleList<int> lst1, lst2;
    lst1.push_front(1);
    lst1.push_front(2); // 2 -> 1
    lst2.push_front(1);
    lst2.push_front(2); // 2 -> 1

    EXPECT_TRUE(lst1 == lst2);
    EXPECT_FALSE(lst1 != lst2);

    lst2.push_front(3);
    EXPECT_TRUE(lst1 < lst2);
    EXPECT_TRUE(lst2 > lst1);
    EXPECT_TRUE(lst1 <= lst2);
    EXPECT_TRUE(lst2 >= lst1);
}

TEST(SingleListTest, ClearAndEmpty1)
{
    SingleList<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    EXPECT_FALSE(lst.empty());

    lst.clear();
    EXPECT_TRUE(lst.empty());
}

TEST(SingleListTest, Resize1)
{
    SingleList<int> lst;
    lst.resize(3, 7); // fill 3 elements with 7
    EXPECT_EQ(lst.size(), 3);

    SingleList<int>::iterator it = lst.begin();
    EXPECT_EQ(*it, 7);
    ++it;
    EXPECT_EQ(*it, 7);
    ++it;
    EXPECT_EQ(*it, 7);

    lst.resize(1, 0); // shrink to 1
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.front(), 7);
}

TEST(SingleListTest, Reverse1)
{
    SingleList<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    lst.push_front(3); // 3 -> 2 -> 1

    lst.reverse(); // should be 1 -> 2 -> 3
    SingleList<int>::iterator it = lst.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3);
}

TEST(SingleListTest, Merge1)
{
    SingleList<int> lst1, lst2;
    lst1.push_front(2);
    lst1.push_front(1); // 1 -> 2
    lst2.push_front(4);
    lst2.push_front(3); // 3 -> 4

    lst1.merge(lst2); // lst1: 1 -> 2 -> 3 -> 4
    EXPECT_EQ(lst1.size(), 4);
    EXPECT_TRUE(lst2.empty());

    SingleList<int>::iterator it = lst1.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3); ++it;
    EXPECT_EQ(*it, 4);
}

TEST(SingleListTest, Unique1)
{
    SingleList<int> lst;
    lst.push_front(2);
    lst.push_front(2);
    lst.push_front(1); // 1 -> 2 -> 2

    lst.unique(); // remove duplicates
    EXPECT_EQ(lst.size(), 2);

    SingleList<int>::iterator it = lst.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2);
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

