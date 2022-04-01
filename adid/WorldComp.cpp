#include "WorldComp.h"

namespace ad
{

void WCPreviewMode::SwitchPreviewMode()
{
    switch(_previewMode)
    {
        case EPreviewMode::Free:
            _previewMode = EPreviewMode::Playing;
            break;
        case EPreviewMode::Playing:
            _previewMode = EPreviewMode::Free;
            break;
        default:
            break;
    }

}

}
