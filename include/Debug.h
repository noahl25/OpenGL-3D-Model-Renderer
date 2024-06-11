#pragma once

#include <iostream>

#ifndef DEBUG
    #define DEBUG
#endif

#define ASSERT(condition) if (!(condition)) __debugbreak();

#ifdef DEBUG
    #define DEBUG_LOG(x) std::cout << (x) << "\n";
    #define glCall(func) dbg::glClearError();\
                      func;\
                      ASSERT(dbg::glLogCall(#func, __FILE__, __LINE__));
#else
    #define glCall(func) func
    #define DEBUG_LOG(x)
#endif

namespace dbg {

    inline void glClearError() {
        while (glGetError() != GL_NO_ERROR);
    }

    inline bool glLogCall(const char* function, const char* file, int line) {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] " << "[Function: " << function << "] [File: " << file << "] [Line: " << line << "] " << error << std::endl;
            return false;
        }
        return true;
    }

};