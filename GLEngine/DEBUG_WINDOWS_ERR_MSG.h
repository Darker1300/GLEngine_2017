#pragma once

#if defined(_WIN32) && defined(_DEBUG)
#include <Windows.h>
#endif
#include <string>

namespace DEBUG {
	inline static void ERROR_MSG(char* _msg)
	{
#if defined(_WIN32) && defined(_DEBUG)
		MessageBox(NULL, _msg, "ERROR", MB_ICONERROR);
#endif
	}

	inline static void ERROR_MSG(std::string _msg)
	{
#if defined(_WIN32) && defined(_DEBUG)
		MessageBox(NULL, _msg.c_str(), "ERROR", MB_ICONERROR);
#endif
	}
}
