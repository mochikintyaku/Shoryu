#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)
#include "IShoryuCommand.h"
#include "ShoryuCoreExport.h"
#include <memory>
#include <stack>

namespace shoryu::core
{
	class SHORYU_API CommandManager
	{
	public:
		typedef std::stack<std::unique_ptr<IShoryuCommand>> CommandStack;

		CommandManager();
		~CommandManager() = default;
		void invoke(std::unique_ptr<IShoryuCommand> command);
		void undoLast();

	private:
		CommandManager(const CommandManager&) = delete;
		CommandManager& operator=(const CommandManager&) = delete;

		CommandStack stack_;
	};
}
#pragma warning(pop)