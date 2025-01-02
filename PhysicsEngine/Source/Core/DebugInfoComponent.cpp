#include "DebugInfoComponent.h"

void DebugInfoComponent::AddInfo(const std::string& info)
{
	DebugInfo.emplace_back(info);
}

std::string DebugInfoComponent::GetDebugInfo() const
{
    std::ostringstream ss;
    for (const auto& info : DebugInfo) 
    {
        ss << info << "\n";
    }
    return ss.str();
}

void DebugInfoComponent::Clear()
{
    DebugInfo.clear();
}
