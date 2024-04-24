#include "GUIhelper.hpp"

void GUIhelp(const char* message)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(message);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}