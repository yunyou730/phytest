#include "CameraCtrlSystem.h"

#include "fila.h"


namespace ad {

CameraCtrlSystem::CameraCtrlSystem(fl::Framework* framework)
    :System(framework)
{
    _keyboardInput = _framework->GetWorldComponent<fl::WCKeyboardInput>(CLASS_NAME(WCKeyboardInput));
}

void CameraCtrlSystem::Update()
{
    /*
    printf("------------\n");
    for(int i = 0;i < (int)fl::EInputKey::Max;i++)
    {
        fl::EInputKey key = fl::EInputKey(i);
        fl::EKeyState state = _keyboardInput->GetState(key);
        
        printf("%d\t%d\n",key,state);
    }
    printf("------------\n");
     */
}

}
