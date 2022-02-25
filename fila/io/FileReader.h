#pragma once
#include <string>

namespace fl {

class FileReader
{
public:
    FileReader(const std::string& filePath);
    std::string Read();
protected:
    std::string _filePath;
};

}
