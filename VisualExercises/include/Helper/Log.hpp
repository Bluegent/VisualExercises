#pragma once

#include <string.h>
#include <stdarg.h>
#include <string>
#include <memory>

#define ALLOW_DEBUG 1
#define ALLOW_INFO 1
#define ALLOW_WARNING 1
#define ALLOW_ERROR 1

namespace ve
{
    void log(const char* format, ...);
}

#define FORMAT "\t[%s() in %s(line %d)]\n"

#ifdef _MSC_VER

#define LOG_MACRO(format,...) ve::log(format FORMAT,__VA_ARGS__,__func__,strrchr(__FILE__,'\\')+1,__LINE__)

#ifdef ALLOW_DEBUG
    #define LOG_DEBUG(format,...) LOG_MACRO("[DBG] " format,__VA_ARGS__)
#else
    #define LOG_DEBUG(format,...)
#endif

#ifdef ALLOW_INFO
    #define LOG_INFO(format,...) LOG_MACRO("[INF] " format,__VA_ARGS__)
#else
    #define LOG_INFO(format,...)
#endif

#ifdef ALLOW_WARNING
    #define LOG_WARNING(format,...) LOG_MACRO("[WRN] " format,__VA_ARGS__)
#else
    #define LOG_WARNING(format,...)
#endif

#ifdef ALLOW_ERROR
    #define LOG_ERROR(format,...) LOG_MACRO("[ERR] " format,__VA_ARGS__)
#else
    #define LOG_ERROR(format,...)
#endif


#define LOG_ERROR(format,...) LOG_MACRO("[ERR] " format,__VA_ARGS__)

#elif defined(__GNUC__)

#define LOG_MACRO(format,...) ve::log(format FORMAT,##__VA_ARGS__,__PRETTY_FUNCTION__,strrchr(__FILE__,'/')+1,__LINE__)

#ifdef ALLOW_DEBUG
#define LOG_DEBUG(format,...) LOG_MACRO("[DBG] " format,##__VA_ARGS__)
#else
#define LOG_DEBUG(format,...)
#endif

#ifdef ALLOW_INFO
#define LOG_INFO(format,...) LOG_MACRO("[INF] " format,##__VA_ARGS__)
#else
#define LOG_INFO(format,...)
#endif

#ifdef ALLOW_WARNING
#define LOG_WARNING(format,...) LOG_MACRO("[WRN] " format,##__VA_ARGS__)
#else
#define LOG_WARNING(format,...)
#endif

#ifdef ALLOW_ERROR
#define LOG_ERROR(format,...) LOG_MACRO("[ERR] " format,##__VA_ARGS__)
#else
#define LOG_ERROR(format,...)
#endif
#endif