#pragma once
#include <cstdio>

namespace fl {

class Log
{
public:
    inline static void Info(const char* msg){
        printf("[info] %s\n",msg);
    }
};

}
