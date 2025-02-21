//
// Created by User on 21.02.2025.
//
#include "library.h"
#include <gtest/gtest.h>

TEST(AddingTest, DefaultTest1)
{
    YoungDiagram::YoungTable youngTable;

    // adding elements
    EXPECT_EQ(youngTable.AddToTable(youngTable, 3), YoungDiagram::ResultCode::Success);
    EXPECT_EQ(youngTable.AddToTable(youngTable, 4), YoungDiagram::ResultCode::Success);
    EXPECT_EQ(youngTable.AddToTable(youngTable, 9), YoungDiagram::ResultCode::Success);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {3, 4, 9}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(AddingTest, DefaultTest2)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {3, 4, 9}
    };

    // adding elements
    EXPECT_EQ(youngTable.AddToTable(youngTable, 2), YoungDiagram::ResultCode::Success);
    EXPECT_EQ(youngTable.AddToTable(youngTable, 5), YoungDiagram::ResultCode::Success);
    EXPECT_EQ(youngTable.AddToTable(youngTable, 1), YoungDiagram::ResultCode::Success);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 4, 5},
            {2, 9},
            {3}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(AddingTest, DefaultTest3)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 2, 9},
            {3, 4},
            {5}
    };

    // adding elements
    EXPECT_EQ(youngTable.AddToTable(youngTable, 8), YoungDiagram::ResultCode::Success);
    EXPECT_EQ(youngTable.AddToTable(youngTable, 7), YoungDiagram::ResultCode::Success);
    EXPECT_EQ(youngTable.AddToTable(youngTable, 6), YoungDiagram::ResultCode::Success);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 2, 6},
            {3, 4, 7},
            {5, 8},
            {9}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(AddingTest, WrongOrderTest)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {3, 4, 9},
            {1, 2}
    };

    // adding elements
    EXPECT_EQ(youngTable.AddToTable(youngTable, 6), YoungDiagram::ResultCode::WrongTableError);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {3, 4, 9},
            {1, 2}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(AddingTest, DublicateInTableTest)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 2, 9},
            {3, 3}
    };

    // adding elements
    EXPECT_EQ(youngTable.AddToTable(youngTable, 6), YoungDiagram::ResultCode::WrongTableError);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 2, 9},
            {3, 3}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(AddingTest, WrongFormTest)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 2},
            {3, 4, 5, 6},
            {7}
    };

    // adding elements
    EXPECT_EQ(youngTable.AddToTable(youngTable, 9), YoungDiagram::ResultCode::WrongTableError);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 2},
            {3, 4, 5, 6},
            {7}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(AddingTest, AddingDublicateTest)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 2, 9},
            {3, 4}
    };

    // adding elements
    EXPECT_EQ(youngTable.AddToTable(youngTable, 9), YoungDiagram::ResultCode::DublicateError);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 2, 9},
            {3, 4}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

//==============================DELETE TESTS=======================

TEST(DeleteTest, DefaultDeleteTest1)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 4, 5},
            {2, 9},
            {3}
    };

    EXPECT_EQ(youngTable.DeleteFromTable(youngTable, 3, 1), YoungDiagram::ResultCode::Success);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {2, 4, 5},
            {3, 9}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(DeleteTest, DefaultDeleteTest2)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 4, 5},
            {2, 9},
            {3}
    };

    EXPECT_EQ(youngTable.DeleteFromTable(youngTable, 2, 2), YoungDiagram::ResultCode::Success);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 4, 9},
            {2},
            {3}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(DeleteTest, DefaultDeleteTest3)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 4, 5},
            {2, 9},
            {3}
    };

    EXPECT_EQ(youngTable.DeleteFromTable(youngTable, 1, 3), YoungDiagram::ResultCode::Success);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 4},
            {2, 9},
            {3}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(DeleteTest, WrongPositionTest)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 4, 5},
            {2, 9},
            {3}
    };

    EXPECT_EQ(youngTable.DeleteFromTable(youngTable, 5, 5), YoungDiagram::ResultCode::WrongPositionToDeleteError);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 4, 5},
            {2, 9},
            {3}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

TEST(DeleteTest, WrongTableTest)
{
    YoungDiagram::YoungTable youngTable;
    youngTable.Table = {
            {1, 4, 2},
            {5, 9},
            {7}
    };

    EXPECT_EQ(youngTable.DeleteFromTable(youngTable, 1, 3), YoungDiagram::ResultCode::WrongTableError);

    // create an expected table
    YoungDiagram::YoungTable expectedTable;
    expectedTable.Table = {
            {1, 4, 2},
            {5, 9},
            {7}
    };

    // compare tables
    EXPECT_EQ(youngTable.Table, expectedTable.Table);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}