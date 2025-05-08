//
// Created by dev on 5/6/25.
//

#ifndef PLATFORM_EXPORT_H
#define PLATFORM_EXPORT_H
#if defined(_WIN32)
    #ifdef LIB_EXPORTS
        #define LIB_API __declspec(dllimport)
    #else
        #define LIB_API __declspec(dllimport)
    #endif
#else
    #ifdef LIB_EXPORTS
        #define LIB_API __attribute__ ((visibility("default")))
    #else
        #define LIB_API
    #endif
#endif


#endif //PLATFORM_EXPORT_H
