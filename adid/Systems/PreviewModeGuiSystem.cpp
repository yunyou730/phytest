#include "PreviewModeGuiSystem.h"
#include "imgui.h"
#include "Framework.h"
#include "WorldComp.h"

static const std::string strFree = "free";
static const std::string strPlaying = "playing";

namespace ad
{

PreviewModeGuiSystem::PreviewModeGuiSystem(fl::Framework* framework)
    :fl::System(framework)
{
    _previewMode = GetFramework()->GetWorldComponent<WCPreviewMode>();
}

void PreviewModeGuiSystem::OnGUI()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    
    {
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (work_pos.x + work_size.x * 0.5);
        window_pos.y = (work_pos.y + PAD);
        window_pos_pivot.x = 0.5f;
        window_pos_pivot.y = 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Preview Mode", &_bOpen, window_flags))
    {
        const std::string* title = nullptr;
        if(_previewMode->_previewMode == EPreviewMode::Free)
        {
            title = &strFree;
        }
        if(_previewMode->_previewMode == EPreviewMode::Playing)
        {
            title = &strPlaying;
        }
        if(ImGui::Button(title->c_str()))
        {
            _previewMode->SwitchPreviewMode();
        }
//        ImGui::Separator();
    }
    ImGui::End();
}



}
