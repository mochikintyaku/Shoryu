#pragma once
#include "ShoryuCoreExport.h"

namespace shoryu
{
	class SHORYU_API IShoryuCommand
	{
	public:
		virtual ~IShoryuCommand() = default;
		virtual void execute() = 0;
		virtual void undo() = 0;
	};
}