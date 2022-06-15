#pragma once

#include "ICommand.h"

namespace edit {

	class CommandHistory {
	public:
		CommandHistory(int capacity)
			: m_capacity(capacity)
		{}

		auto capacity() const { return m_capacity; }

	private:
		int		m_capacity;
	};
}