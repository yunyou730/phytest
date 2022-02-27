#pragma once
#include <cstdio>
#include <glm/glm.hpp>
#include <sstream>

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
    
    inline static void Info(const glm::vec4& v)
    {
        char info[128] = {0};
        sprintf(info,"%.3f,%.3f,%.3f,%.3f",v.x,v.y,v.z,v.w);
        Info(info);
    }
    
    inline static void Info(const glm::mat4& mat)
    {
        std::stringstream ss;
        ss << "---------\n";
        for(int r = 0;r < 4;r++)
        {
            for(int c = 0;c < 4;c++)
            {
                ss << mat[r][c] << "\t";
            }
            ss << "\n";
        }
        Info(ss.str().c_str());
    }
};

}
