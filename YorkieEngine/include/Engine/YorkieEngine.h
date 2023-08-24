#pragma once

#ifdef YENGINE_EXPORT
#define YorkieAPI __declspec(dllexport)
#else
#define YorkieAPI __declspec(dllimport)
#endif