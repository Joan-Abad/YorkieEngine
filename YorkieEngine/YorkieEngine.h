#pragma once

#ifdef YENGINE_EXPORT
#define YENGINE __declspec(dllexport)
#else
#define YENGINE __declspec(dllimport)
#endif