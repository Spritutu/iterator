#include<gtest/gtest.h>

int foo(){
	return 0;
}

TEST(TestName, TestIndex){
	ASSERT_EQ(0, foo());
}

