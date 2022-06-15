#include "pch.h"
#include "../edit/CommandHistory.h"

TEST(CommandHistory, Ctor)
{
	edit::CommandHistory h(16);

	EXPECT_EQ(h.capacity(), 16);
}