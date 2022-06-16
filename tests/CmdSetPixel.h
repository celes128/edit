#pragma once
#include "pch.h"
#include "../edit/CommandHistory.h"
#include "DocImage.h"

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
		auto *image = dynamic_cast<DocImage *>(doc);

		m_originalPixel = image->GetPixel(m_p);
		
		image->SetPixel(m_p, m_newPixel);

		return {};
	}

	edit::CommandOuput undo(edit::IDocument *doc) override
	{
		auto *image = dynamic_cast<DocImage *>(doc);

		image->SetPixel(m_p, m_originalPixel);

		return {};
	}

private:
	// Position of the pixel in the image.
	Point	m_p;

	Pixel	m_newPixel;
	Pixel	m_originalPixel;
};