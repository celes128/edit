#include "pch.h"
#include "../edit/FSOStack.h"

TEST(FSOStack, Ctor)
{
	edit::FSOStack<int> s(4);

	EXPECT_EQ(s.capacity(), 4);
}