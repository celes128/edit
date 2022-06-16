#include "pch.h"
#include "../edit/CommandHistory.h"
#include "DocImage.h"
#include "CmdSetPixel.h"
#include <vector>

TEST(CommandHistory, Ctor)
{
	edit::CommandHistory h(4);

	EXPECT_EQ(h.capacity(), 4);
}

TEST(CommandHistory, Execute)
{
	DocImage	image(Size{ 8, 8 }, color::white); 

	edit::CommandHistory h(4);

	h.execute(
		new CmdSetPixel(Point{ 0,0 }, Pixel{ color::blue }),
		&image
	);

	auto got = image.GetPixel(Point{ 0,0 });
	auto expected = Pixel{ color::blue };
	EXPECT_EQ(got, expected);
}

TEST(CommandHistory, Undo)
{
	DocImage	image(Size{ 8, 8 }, color::white);

	edit::CommandHistory h(4);

	h.execute(
		new CmdSetPixel(Point{ 0,0 }, Pixel{ color::blue }),
		&image
	);
	h.undo(&image);

	auto got = image.GetPixel(Point{ 0,0 });
	auto expected = Pixel{ color::white };
	EXPECT_EQ(got, expected);
}

TEST(CommandHistory, Redo)
{
	DocImage	image(Size{ 8, 8 }, color::white);

	edit::CommandHistory h(4);

	h.execute(
		new CmdSetPixel(Point{ 0,0 }, Pixel{ color::blue }),
		&image
	);
	h.undo(&image);
	h.redo(&image);

	auto got = image.GetPixel(Point{ 0,0 });
	auto expected = Pixel{ color::blue };
	EXPECT_EQ(got, expected);
}