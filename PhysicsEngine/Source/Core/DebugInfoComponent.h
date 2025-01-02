#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "Core/DebugInfoComponent.h"

class DebugInfoComponent
{

public:

    void AddInfo(const std::string& Info);

    template <typename T>
    void AddInfo(const std::string& name, const T& value)
    {
        std::ostringstream ss;
        ss << name << ": " << value;
        DebugInfo.emplace_back(ss.str());
    }

    std::string GetDebugInfo() const;

    void Clear();

private:

    std::vector<std::string> DebugInfo;

};

