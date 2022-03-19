#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"


namespace fl
{
class CameraComponent;
}

namespace ad {

class CameraCtrlSystem : public fl::System,public fl::ISysUpdate
{
public:
    CameraCtrlSystem(fl::Framework* framework);
    
    virtual void Update() override;
    
protected:
    void DumpKeyboardState();
    void HandleCameraMove(float deltaTime,fl::Entity* camEntity);
    void HandleCameraRotate(float deltaTime,fl::Entity* camEntity);
    
    glm::vec3 GetHorizontalMoveDirection(fl::CameraComponent* camComp);
    
protected:
    fl::WCKeyboardInput* _keyboardInput = nullptr;
    float   _moveSpeedFactor = 3.0f;
};

}

