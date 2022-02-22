#pragma once

namespace fl {

class System
{
public:
    System();
    virtual ~System();
};

class ISysPrepare
{
public:
    virtual void Prepare() = 0;
};

class ISysUpdate
{
public:
    virtual void Update() = 0;
};

class ISysRenderer
{
public:
    virtual void Renderer() = 0;
};

class ISysCleanup
{
public:
    virtual void CleanUp() = 0;
};

}
