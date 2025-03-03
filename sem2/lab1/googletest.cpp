#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "spisok.h"
using namespace std;

TEST(push,test1)
{
    List a;
    a.push_b(2);
    ASSERT_EQ(a[0]->value,2);
}
TEST(push,test2)
{
  List a;
  a.push_b(4);
  ASSERT_EQ(a[0]->value,4);
}
TEST(remove_first,test1)
{
  List a;
  a.push_b(2);
  a.push_b(4);
  a.Remove_first();
  ASSERT_EQ(a[0]->value,4);
}
TEST(remove_first,test2)
{
  List a;
  a.push_b(4);
  a.push_b(6);
  a.Remove_first();
  ASSERT_EQ(a[0]->value,6);
}
TEST(remove_last,test1)
{
  List a;
  a.push_b(2);
  a.push_b(6);
  a.Remove_last();
  ASSERT_EQ(a.find(6),0);
}
TEST(remove_last,test2)
{
  List a;
  a.push_b(20);
  a.push_b(40);
  a.Remove_last();
  ASSERT_EQ(a.find(40),0);
}
TEST(remove,test1)
{
  List a;
  a.push_b(40);
  a.push_b(60);
  a.push_b(44);
  a.Remove(60);
  ASSERT_EQ(a.find(60),0);
}
TEST(remove,test2)
{
  List a;
  a.push_b(40);
  a.push_b(60);
  a.push_b(44);
  a.push_b(144);
  a.Remove(144);
  ASSERT_EQ(a.find(144),0);
}
TEST(is_empty,test1)
{
  List a;
  ASSERT_EQ(a.is_empty(),1);
}
TEST(is_empty,test2)
{
  List a;
  a.push_b(2);
  ASSERT_EQ(a.is_empty(),0);
}
TEST(sort,test1)
{
  List a;
  a.push_b(22);
  a.push_b(44);
  a.push_b(1);
  a.push_b(-1);
  a.push_b(-10);
  a.Sort();
  for(int i=1;i<a.Get_size();i++)
  {
    ASSERT_LE(a[i-1]->value,a[i]->value);
  }
}
TEST(sort,test2)
{
  List a;
  a.push_b(2);
  a.push_b(2);
  a.push_b(2);
  a.push_b(1);
  a.push_b(1);
  a.Sort();
  for(int i=1;i<a.Get_size();i++)
  {
    ASSERT_LE(a[i-1]->value,a[i]->value);
  }
}
TEST(find,test1)
{
  List a;
  a.push_b(2);
  a.push_b(3);
  ASSERT_EQ(a.find(2),1);
}
TEST(find,test2)
{
  List a;
  a.push_b(2);
  a.push_b(3);
  ASSERT_EQ(a.find(-1),0);
}
TEST(get_size,test1)
{
  List a;
  a.push_b(2);
  a.push_b(1);
  ASSERT_EQ(a.Get_size(),2);
}
TEST(get_size,test2)
{
  List a;
  ASSERT_EQ(a.Get_size(),0);
}
TEST(intersection,test1)
{
  List a;
  List b;
  List result;

  a.push_b(2);
  a.push_b(2);
  a.push_b(1);
  a.push_b(3);

  b.push_b(1);
  b.push_b(1);
  b.find(2);

  result=a.intersection_list(b.first);

  for(int i=0;i<result.Get_size();i++)
  {
    ASSERT_EQ(a.find(result[i]->value),1);
    ASSERT_EQ(b.find(result[i]->value),1);
  }

}
TEST(intersection,test2)
{
  List a;
  List b;
  List result;

  a.push_b(1);
  a.push_b(2);
  a.push_b(3);

  b.push_b(3);
  b.push_b(3);
  b.push_b(6);

  result=a.intersection_list(b.first);

  for(int i=0;i<result.Get_size();i++)
  {
    ASSERT_EQ(a.find(result[i]->value),1);
    ASSERT_EQ(b.find(result[i]->value),1);
  }

}
TEST(merge,test1)
{
  List a;
  List b;
  List result;

  a.push_b(1);
  a.push_b(2);
  a.push_b(3);

  b.push_b(3);
  b.push_b(3);
  b.push_b(6);

  result=a.union_list(b.first);

  for(int i=0;i<a.Get_size();i++)
  {
    ASSERT_EQ(result.find(a[i]->value),1);
  }

  for(int i=0;i<b.Get_size();i++)
  {
    ASSERT_EQ(result.find(b[i]->value),1);
  }
}
TEST(merge,test2)
{
  List a;
  List b;
  List result;

  a.push_b(1);
  a.push_b(0);
  a.push_b(6);

  b.push_b(6);
  b.push_b(1);
  b.push_b(100);

  result=a.union_list(b.first);

  for(int i=0;i<a.Get_size();i++)
  {
    ASSERT_EQ(result.find(a[i]->value),1);
  }

  for(int i=0;i<b.Get_size();i++)
  {
    ASSERT_EQ(result.find(b[i]->value),1);
  }
}
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
