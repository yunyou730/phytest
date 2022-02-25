#pragma once
#include <cstdio>
#include <glm/glm.hpp>

namespace fl {

class Log
{
public:
    inline static void Info(const char* msg){
        printf("[info] %s\n",msg);
    }
    
    
    inline static void Info(const glm::vec3& v)
    {
        char info[128] = {0};
        sprintf(info,"%.3f,%.3f,%.3f",v.x,v.y,v.z);
        Info(info);
    }
};

}
