#include "pch.h"
#include "CommandHistory.h"

namespace edit {

	static void pop_delete_all(FSOStack<ICommand *> &s)
	{
		while (!s.empty()) {
			delete s.top();
			s.pop();
		}
	}

	CommandHistory::CommandHistory(size_t capacity)
		: m_capacity(capacity)
		, m_execStack(capacity)
		, m_undoStack(capacity)
	{}

	CommandHistory::~CommandHistory()
	{
		pop_delete_all(m_execStack);
		pop_delete_all(m_undoStack);
	}

	CommandOuput CommandHistory::execute(ICommand *cmd, IDocument *doc)
	{
		assert(cmd != nullptr);
		assert(doc != nullptr);

		m_execStack.push(cmd);

		pop_delete_all(m_undoStack);

		auto output = cmd->execute(doc);

		return output;
	}

	CommandOuput CommandHistory::undo(IN IDocument *doc, OUT OPTIONAL bool *performed)
	{
		CommandOuput output;

		if (performed) {
			*performed = false;// Assume we did not Undo
		}

		if (!m_execStack.empty()) {
			auto *cmd = m_execStack.top();
			m_execStack.pop();

			output = cmd->undo(doc);

			if (performed) {
				*performed = true;
			}

			m_undoStack.push(cmd);
		}

		return output;
	}

	CommandOuput CommandHistory::redo(IN IDocument *doc, OUT OPTIONAL bool *performed)
	{
		CommandOuput output;

		if (performed) {
			*performed = false;// Assume we did not Redo
		}

		if (!m_undoStack.empty()) {
			auto *cmd = m_undoStack.top();
			m_undoStack.pop();

			output = cmd->execute(doc);

			if (performed) {
				*performed = true;
			}

			m_execStack.push(cmd);
		}

		return output;
	}
}