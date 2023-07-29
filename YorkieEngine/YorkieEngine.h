#pragma once

#ifdef YENGINE_EXPORT
#define Yorkie __declspec(dllexport)
#else
#define Yorkie __declspec(dllimport)
#endif