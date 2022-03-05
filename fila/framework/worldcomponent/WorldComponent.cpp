#include "WorldComponent.h"

namespace fl {

WCKeyboardInput::WCKeyboardInput()
{
    for(int i = 0;i < (int)EInputKey::Max;i++)
    {
        _keyStateMap.insert(std::make_pair((EInputKey)i, EKeyState::RELEASE));
    }
}

void WCKeyboardInput::SetState(EInputKey key,EKeyState state)
{
    auto it = _keyStateMap.find(key);
    assert(it != _keyStateMap.end());
    it->second = state;
}

EKeyState WCKeyboardInput::GetState(EInputKey key) const
{
    EKeyState result = EKeyState::RELEASE;
    auto it = _keyStateMap.find(key);
    if(it != _keyStateMap.end())
    {
        result = it->second;
    }
    return result;
}

}
