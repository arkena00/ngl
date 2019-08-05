#ifndef COMPILER_INCLUDE_NGL_LOG_HPP_NGL
#define COMPILER_INCLUDE_NGL_LOG_HPP_NGL

#include <spdlog/spdlog.h>

#define ngl_trace(Message, ...) spdlog::trace(Message, __VA_ARGS__)

#endif // COMPILER_INCLUDE_NGL_LOG_HPP_NGL
