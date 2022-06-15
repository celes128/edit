#pragma once

#include "framework.h"
#include "ICommand.h"
#include "FSOStack.h"

namespace edit {

	class IDocument;

	class CommandHistory {
	public:
		CommandHistory(size_t capacity);
		~CommandHistory();

		auto capacity() const { return m_capacity; }

		CommandOuput execute(ICommand *cmd, IDocument *doc);
		CommandOuput undo(IN IDocument *doc, OUT OPTIONAL bool *performed = nullptr);
		CommandOuput redo(IN IDocument *doc, OUT OPTIONAL bool *performed = nullptr);

	private:
		size_t	m_capacity;

		// Commands that have been executed or redone.
		FSOStack<ICommand *>		m_execStack;

		// Commands that have been undone.
		FSOStack<ICommand *>		m_undoStack;
	};
}