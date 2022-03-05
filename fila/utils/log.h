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
    
    inline static void Info(const char* tag,const char* msg)
    {
        printf("[%s] %s\n",tag,msg);
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
        char info[256] = {0};
        sprintf(info,"---\n%.3f,%.3f,%.3f,%.3f\n%.3f,%.3f,%.3f,%.3f\n%.3f,%.3f,%.3f,%.3f\n%.3f,%.3f,%.3f,%.3f\n",
                mat[0][0],mat[0][1],mat[0][2],mat[0][3],
                mat[1][0],mat[1][1],mat[1][2],mat[1][3],
                mat[2][0],mat[2][1],mat[2][2],mat[2][3],
                mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
        /*
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
         */
        Info(info);
    }
};

}
