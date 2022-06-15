#include "pch.h"
#include "../edit/CommandHistory.h"

TEST(CommandHistory, Ctor)
{
	edit::CommandHistory h(4);

	EXPECT_EQ(h.capacity(), 4);
}