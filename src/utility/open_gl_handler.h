#pragma once

#include <gl/glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define DEBUG_OPEN_GL

#ifdef DEBUG_OPEN_GL
#define GL_CALL(x) gl_clear_error(); x; ASSERT(gl_log_call(#x, __FILE__, __LINE__))
#else 
#define GL_CALL(x) x
#endif

void gl_clear_error();
bool gl_log_call(const char* function, const char* file, int line);