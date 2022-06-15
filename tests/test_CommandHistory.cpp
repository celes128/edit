#include "pch.h"
#include "../edit/CommandHistory.h"
#include <cstdint>
#include <vector>

using Color = uint32_t;

namespace color {
	const Color black	= 0x000000FF;
	const Color white	= 0xFFFFFFFF;
	const Color red		= 0xFF0000FF;
	const Color green	= 0x00FF00FF;
	const Color blue	= 0x0000FFFF;
}

struct Pixel {
	Color	color;
};

inline bool operator==(const Pixel &lhs, const Pixel &rhs)
{
	return lhs.color == rhs.color;
}
inline bool operator!=(const Pixel &lhs, const Pixel &rhs)
{
	return !(lhs == rhs);
}

struct Size {
	union {
		struct { int x, y; };
		struct { int w, h; };
	};
};

using Point = Size;

class Rect {
public:
	Rect(Point pos, Size size)
		: m_pos(pos)
		, m_size(size)
	{}

	auto Left() const { return m_pos.x; }
	auto Right() const { return m_pos.x + m_size.w; }
	auto Top() const { return m_pos.y; }
	auto Bottom() const { return m_pos.y + m_size.h; }

	auto Width() const { return m_size.w; }
	auto Height() const { return m_size.h; }
	Size GetSize() const { return { Width(), Height() }; }

private:
	Point	m_pos;
	Size	m_size;
};

class ImageDocument : public edit::IDocument {
public:
	ImageDocument(Size size = { 0,0 }, Color color = color::blue)
		: m_size(size)
		, m_pixels(NumPixels(), Pixel{ color })
	{}

	//		ACCESSORS
	//
	const auto &GetPixel(Point p) const
	{
		return m_pixels[pxi(p)];
	}
	
	const auto Width() const { return m_size.w; }
	const auto Height() const { return m_size.h; }
	const size_t NumPixels() const { return Width() * Height(); }


	//		MANIPULATORS
	//
	void SetPixel(Point p, Pixel pixel)
	{
		m_pixels[pxi(p)] = pixel;
	}

private:
	// pxi returns the pixel index in the vector given its coordinates in the image.
	size_t pxi(Point p) const
	{
		return p.y * m_size.w + p.x;
	}

private:
	Size				m_size;
	std::vector<Pixel>	m_pixels;
};

class CmdSetPixel : public edit::ICommand {
public:
	CmdSetPixel(Point p, Pixel pixel)
		: m_p(p)
		, m_newPixel(pixel)
	{}

	~CmdSetPixel() override = default;

private:
	edit::CommandOuput execute(edit::IDocument *doc) override
	{
		auto *image = dynamic_cast<ImageDocument *>(doc);

		m_originalPixel = image->GetPixel(m_p);
		
		image->SetPixel(m_p, m_newPixel);

		return {};
	}

	edit::CommandOuput undo(edit::IDocument *doc) override
	{
		auto *image = dynamic_cast<ImageDocument *>(doc);

		image->SetPixel(m_p, m_originalPixel);

		return {};
	}

private:
	// Position of the pixel in the image.
	Point	m_p;

	Pixel	m_newPixel;
	Pixel	m_originalPixel;
};

TEST(CommandHistory, Ctor)
{
	edit::CommandHistory h(4);

	EXPECT_EQ(h.capacity(), 4);
}

TEST(CommandHistory, Execute)
{
	ImageDocument	image(Size{ 8, 8 }, color::white); 

	edit::CommandHistory h(4);

	h.execute(new CmdSetPixel(Point{ 0,0 }, Pixel{ color::blue }), &image);

	auto got = image.GetPixel(Point{ 0,0 });
	auto expected = Pixel{ color::blue };
	EXPECT_EQ(got, expected);
}

TEST(CommandHistory, Undo)
{
	ImageDocument	image(Size{ 8, 8 }, color::white);

	edit::CommandHistory h(4);

	h.execute(new CmdSetPixel(Point{ 0,0 }, Pixel{ color::blue }), &image);
	h.undo(&image);

	auto got = image.GetPixel(Point{ 0,0 });
	auto expected = Pixel{ color::white };
	EXPECT_EQ(got, expected);
}

TEST(CommandHistory, Redo)
{
	ImageDocument	image(Size{ 8, 8 }, color::white);

	edit::CommandHistory h(4);

	h.execute(new CmdSetPixel(Point{ 0,0 }, Pixel{ color::blue }), &image);
	h.undo(&image);
	h.redo(&image);

	auto got = image.GetPixel(Point{ 0,0 });
	auto expected = Pixel{ color::blue };
	EXPECT_EQ(got, expected);
}