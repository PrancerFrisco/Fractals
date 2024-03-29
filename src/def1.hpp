#pragma once
#include <SFML\Graphics.hpp>

std::vector<sf::Color> def1C = {

    {4, 4, 73},

    {3, 4, 77},
    {3, 5, 82},

    {2, 5, 86},

    {1, 6, 91},
    {1, 6, 95},

    {0, 7, 100},

    {2, 13, 106},
    {4, 19, 113},

    {6, 25, 119},

    {8, 31, 125},
    {10, 38, 132},

    {12, 44, 138},

    {14, 50, 144},
    {16, 57, 151},

    {18, 63, 157},

    {20, 69, 164},
    {20, 69, 164},

    {24, 82, 177},

    {29, 89, 182},
    {35, 96, 188},

    {40, 103, 193},

    {46, 110, 198},
    {51, 118, 204},

    {57, 125, 209},

    {70, 134, 212},
    {82, 144, 216},

    {95, 153, 219},

    {108, 162, 222},
    {121, 172, 226},

    {134, 181, 229},

    {147, 190, 232},
    {159, 199, 235},

    {172, 208, 238},

    {185, 217, 241},
    {198, 227, 245},

    {211, 236, 248},

    {216, 235, 238},
    {221, 235, 229},

    {226, 234, 219},

    {231, 234, 210},
    {236, 233, 200},

    {241, 233, 191},

    {205, 228, 175},
    {168, 222, 159},

    {132, 217, 143},

    {96, 212, 127},
    {60, 206, 111},

    {24, 201, 95},

    {62, 196, 79},
    {101, 190, 63},

    {139, 185, 47},

    {178, 180, 31},
    {216, 175, 16},

    {255, 170, 0},

    {246, 163, 0},
    {238, 156, 0},

    {229, 149, 0},

    {221, 142, 0},
    {212, 135, 0},

    {204, 128, 0},

    {195,121,0},
    {187,114,0},

    {178, 107, 0},

    {170, 100, 0},
    {161, 94, 0},

    {153, 87, 0},

    {145, 81, 0},
    {137, 75, 1},

    {129, 69, 1},

    {121, 63, 2},
    {114, 58, 2},

    {106, 52, 3},

    {108,54,3},
    {110,56,2},

    {112, 58, 2},

    {66, 30, 15},

    {59, 26, 17},
    {52, 22, 18},

    {45, 18, 20},

    {38, 14, 22},
    {32, 11, 24},

    {25, 7, 26},

    {22, 6, 29},
    {20, 5, 33},

    {17, 4, 36},

    {14, 3, 40},
    {12, 2, 43},

    {9, 1, 47},

    {8, 1, 51},
    {7, 2, 56},

    {6, 2, 60},

    {5, 3, 64},
    {5, 3, 69},
};

sf::Color def1(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        return def1C[(iterations / paletteLength) % def1C.size()];
    }
    return sf::Color::Black;
}
