#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace fl {

FileReader::FileReader(const std::string& filePath)
    :_filePath(filePath)
{
}

std::string FileReader::Read()
{
    std::string content;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

//    FILE* f = fopen("/storage/emulated/0/res/test.fs","r");
//    if(f == nullptr)
//    {
//        printf("11\n");
//    } else
//    {
//        printf("222\n");
//    }
//    fclose(f);
    
    try
    {
        file.open(_filePath);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        content = ss.str();
    }
    catch(std::ifstream::failure& e)
    {
        std::cout << "Open file " << _filePath << "failed" << std::endl;
    }
    return content;
}

}
