#ifndef COMPILER_INCLUDE_NGL_LOG_HPP_NGL
#define COMPILER_INCLUDE_NGL_LOG_HPP_NGL

#include <spdlog/spdlog.h>

#define ngl_trace(...) spdlog::trace(__VA_ARGS__)
#define ngl_info(...) spdlog::info(__VA_ARGS__)
#define ngl_warning(...) spdlog::warning(__VA_ARGS__)
#define ngl_error(...) spdlog::error(__VA_ARGS__)

#endif // COMPILER_INCLUDE_NGL_LOG_HPP_NGL
