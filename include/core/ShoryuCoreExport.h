#pragma once

namespace shoryu::core
{
	// Export macro:
	// - Build/consume DLL: define SHORYU_CORE_EXPORTS in the DLL project, consumers get dllimport.
	// - Build/consume static lib: define SHORYUCORE_STATIC so SHORYU_API becomes empty.
	#ifdef SHORYU_CORE_TEST
		#define SHORYU_API
	#else
		#ifdef SHORYU_CORE_EXPORTS
			#define SHORYU_API __declspec(dllexport)
		#else
			#define SHORYU_API __declspec(dllimport)
		#endif
	#endif
}