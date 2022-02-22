#pragma once
#include <vector>

namespace fl {

class System;
class ISysPrepare;
class ISysUpdate;
class ISysRenderer;
class ISysCleanup;

class Framework
{
public:
    Framework();
    virtual ~Framework();
    
public:
    void OnPrepare();
    void OnUpdate();
    void OnRender();
    void OnCleanUp();
    
public:
    void RegisterSystem(System* sys);
    
protected:
    std::vector<ISysPrepare*>       _prepareSysList;
    std::vector<ISysUpdate*>        _updateSysList;
    std::vector<ISysRenderer*>      _renderSysList;
    std::vector<ISysCleanup*>       _cleanupSysList;
};

}
