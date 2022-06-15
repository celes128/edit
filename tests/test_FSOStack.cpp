#include "pch.h"
#include "../edit/FSOStack.h"

TEST(FSOStack, Ctor)
{
	edit::FSOStack<int> s(4);

	EXPECT_EQ(s.capacity(), 4);
	EXPECT_EQ(s.size(), 0);
	EXPECT_TRUE(s.empty());
	EXPECT_FALSE(s.full());
}

TEST(FSOStack, PushOneItemAndTop)
{
	edit::FSOStack<int> s(4);

	s.push(9);

	EXPECT_EQ(s.size(), 1);
	EXPECT_EQ(s.top(), 9);
}