#include "CommandManager.h"

namespace shoryu::core
{
	CommandManager::CommandManager()
		:stack_()
	{ }

	void CommandManager::invoke(std::unique_ptr<IShoryuCommand> command)
	{
		command->execute();
		stack_.push(std::move(command));
	}

	void CommandManager::undoLast()
	{
		if (stack_.empty())
			return;

		auto command = std::move(stack_.top());
		stack_.pop();

		command->undo();
	}
}
