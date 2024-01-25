#pragma once
#include <SFML\Graphics.hpp>
#include "Palettes.hpp"

std::vector<sf::Color> five_layersC = { {49, 167, 167},
    { 173, 227, 227 },
    { 0, 0, 0 },
    { 204, 63, 63 },
    { 255, 255, 255 } };

sf::Color five_layers(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        return five_layersC[(iterations / paletteLength) % five_layersC.size()];
    }
    return sf::Color::Black;
}