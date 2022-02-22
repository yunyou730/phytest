#pragma once

namespace fl {

class Application
{
public:
    Application();
    virtual ~Application();
    
    virtual void OnPrepare();
    virtual void OnCleanup();
    
    virtual void OnUpdate();
    virtual void OnRenderer();
    
    void SetDeltaTime();
    float GetDeltaTime();
};

}

