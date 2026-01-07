#pragma once
#include <iostream>

//Always on info logs
#define LOG_INFO(msg) std::cout<< "[INFO]" <<msg<<std::endl;

#ifndef DEBUG_BUILD
    #define LOG_DEBUG(msg) std::cout<<"[DEBUG]"<<msg<<std::endl;
#else
    #define LOG_DEBUG(msg)
#endif