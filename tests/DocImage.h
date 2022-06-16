#pragma once
#include "pch.h"
#include "../edit/CommandHistory.h"
#include <cstdint>
#include <vector>

using Color = uint32_t;

namespace color {
	const Color white = 0xFFFFFFFF;
	const Color blue = 0x0000FFFF;
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

class DocImage : public edit::IDocument {
public:
	DocImage(Size size = { 0,0 }, Color color = color::blue)
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