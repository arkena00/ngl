#ifndef COMPILER_INCLUDE_NGL_LOG_HPP_NGL
#define COMPILER_INCLUDE_NGL_LOG_HPP_NGL

#include <spdlog/spdlog.h>

#define ngl_trace(Message, ...) spdlog::trace(Message, __VA_ARGS__)
#define ngl_info(Message, ...) spdlog::info(Message, __VA_ARGS__)
#define ngl_warning(Message, ...) spdlog::warning(Message, __VA_ARGS__)
#define ngl_error(Message, ...) spdlog::error(Message, __VA_ARGS__)

#endif // COMPILER_INCLUDE_NGL_LOG_HPP_NGL
