#include "pch.h"
#include "../edit/FSOStack.h"
#include <vector>

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

TEST(FSOStack, Full)
{
	edit::FSOStack<int> s(4);

	for (size_t i = 0; i < s.capacity(); i++) {
		s.push(i);
	}

	EXPECT_EQ(s.size(), 4);
	EXPECT_TRUE(s.full());
}

TEST(FSOStack, EmptyAFullStack)
{
	edit::FSOStack<int> s(4);

	for (size_t i = 0; i < s.capacity(); i++) {
		s.push(i);
	}

	for (size_t i = 0; i < s.capacity(); i++) {
		s.pop();
	}

	EXPECT_TRUE(s.empty());
}

static std::vector<int> collect(edit::FSOStack<int> &s)
{
	std::vector<int> v;

	while (!s.empty()) {
		v.push_back(s.top());

		s.pop();
	}

	return v;
}

TEST(FSOStack, Overwrite)
{
	edit::FSOStack<int>		s(3);

	// Fill the stack exactly (i.e. without causing any overwrite).
	for (size_t i = 0; i < s.capacity(); i++) {
		s.push(i);
	}

	// Push 3 to overwrite the 0 at the bottom.
	s.push(3);

	auto got = collect(s);
	std::vector<int> expected{ {3,2,1} };
	EXPECT_EQ(got, expected);
}