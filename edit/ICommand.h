#pragma once

#include <vector>
#include <string>

namespace edit {

	class Document;

	class ICommand {
	public:
		friend class CommandHistory;

		ICommand() {}
		virtual ~ICommand() = default;

	private:
		virtual std::vector<std::string> execute(Document *doc) = 0;
		virtual std::vector<std::string> undo(Document *doc) = 0;
	};
}