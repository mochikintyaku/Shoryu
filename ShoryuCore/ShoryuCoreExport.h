#pragma once

namespace shoryu
{
	// DLL�G�N�X�|�[�g��`
	#ifdef SHORYUCORE_EXPORTS
	#define SHORYU_API __declspec(dllexport)
	#else
	#define SHORYU_API __declspec(dllimport)
	#endif
}