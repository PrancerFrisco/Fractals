#pragma once
#include <SFML\Graphics.hpp>
#include "Palettes.hpp"

std::vector<sf::Color> def2C = {
                        {25, 7, 26},
                        {17, 4, 36},
                        {9, 1, 47},
                        {6, 2, 60},
                        {4, 4, 73},
                        {2, 5, 86},
                        {0, 7, 100},
                        {6, 25, 119},
                        {12, 44, 138},
                        {18, 63, 157},
                        {24, 82, 177},
                        {40, 103, 193},
                        {57, 125, 209},
                        {95, 153, 219},
                        {134, 181, 229},
                        {172, 208, 238},
                        {211, 236, 248},
                        {226, 234, 219},
                        {241, 233, 191},
                        {132, 217, 143},
                        {24, 201, 95},
                        {139, 185, 47},
                        {255, 170, 0},
                        {229, 149, 0},
                        {204, 128, 0},
                        {178, 107, 0},
                        {153, 87, 0},
                        {129, 69, 1},
                        {106, 52, 3},
                        {112, 58, 2},
                        {66, 30, 15},
                        {45, 18, 20} };

sf::Color def2(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        return def2C[(iterations / paletteLength) % def2C.size()];
    }
    return sf::Color::Black;
}