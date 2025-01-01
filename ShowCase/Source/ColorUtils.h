#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class ColorUtils {
public:
    static sf::Color GetRandomPresetColor() {
        static const std::vector<sf::Color> PresetColors = 
        {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Cyan,
            sf::Color::Magenta
        };

        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dist(0, PresetColors.size() - 1);

        return PresetColors[dist(gen)];
    }
};