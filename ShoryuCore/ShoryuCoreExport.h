#pragma once

namespace shoryu
{
	// DLLエクスポート定義
	#ifdef SHORYUCORE_EXPORTS
	#define SHORYU_API __declspec(dllexport)
	#else
	#define SHORYU_API __declspec(dllimport)
	#endif
}