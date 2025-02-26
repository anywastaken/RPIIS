#include "set.h"

#include <gtest/gtest.h>

TEST(INCORRECT, file_patch1){
	ASSERT_THROW(Intersection("../sets/input/bad_1.txt"), exception);
	ASSERT_THROW(Intersection("../sets/input/bad_2.txt"), exception);
	ASSERT_THROW(Intersection("../sets/input/bad_3.txt"), exception);
}

TEST(INCORRECT, file_patch2){
	ASSERT_THROW(Intersection("../sets/input/bad_4.txt"), exception);
	ASSERT_THROW(Intersection("../sets/input/bad_5.txt"), exception);
	ASSERT_THROW(Intersection("../sets/input/bad_6.txt"), exception);
}

TEST(INCORRECT, file_patch3){
	ASSERT_THROW(Intersection("../sets/input/bad_7.txt"), exception);
	ASSERT_THROW(Intersection("../sets/input/bad_8.txt"), exception);
	ASSERT_THROW(Intersection("../sets/input/bad_9.txt"), exception);
	ASSERT_THROW(Intersection("../sets/input/bad_10.txt"), exception);
}

TEST(CORRECT, file_1){
	Intersection("../sets/input/good_1.txt");
	Intersection("../sets/input/good_2.txt");
	Intersection("../sets/input/good_3.txt");
	Intersection("../sets/input/good_4.txt");
	Intersection("../sets/input/good_5.txt");
	ifstream fin;
	fin.open("../sets/result/RESULT(good_1).txt");
	string input;
	getline(fin, input);
	fin.close();
	ASSERT_EQ("Result={4,{3,4}}",input);
}

TEST(CORRECT, file_2){
	Intersection("../sets/input/good_2.txt");
	ifstream fin;
	fin.open("../sets/result/RESULT(good_2).txt");
	string input;
	getline(fin, input);
	fin.close();
	ASSERT_EQ("Result={2,{}}",input);
}

TEST(CORRECT, file_3){
	Intersection("../sets/input/good_3.txt");
	ifstream fin;
	fin.open("../sets/result/RESULT(good_3).txt");
	string input;
	getline(fin, input);
	fin.close();
	ASSERT_EQ("Result={1,2,7,a}",input);
}

TEST(CORRECT, file_4){
	Intersection("../sets/input/good_4.txt");
	ifstream fin;
	fin.open("../sets/result/RESULT(good_4).txt");
	string input;
	getline(fin, input);
	fin.close();
	ASSERT_EQ("Result={C}",input);
}

TEST(CORRECT, file_5){
	Intersection("../sets/input/good_5.txt");
	ifstream fin;
	fin.open("../sets/result/RESULT(good_5).txt");
	string input;
	getline(fin, input);
	fin.close();
	ASSERT_EQ("Result={MEGA,a,c}",input);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}