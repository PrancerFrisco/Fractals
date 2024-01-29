#pragma once
#include "Global.hpp"
#include <SFML\Graphics.hpp>
#include <vector>
#include "def1.hpp"
#include "def2.hpp"
#include "BCGWMRYKkbcgwnry.hpp"
#include "DEFAULT.hpp"
#include "e10000.hpp"
#include "five_layers.hpp"
#include "golden.hpp"
#include "hsv.hpp"
#include "PeacocK4.hpp"
#include "lch.hpp"


sf::Color paletteRed(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        return sf::Color((iterations % 256), (iterations / 256) % 256, ((iterations / 65536) % 256));
    }
    return sf::Color::Black;
}
sf::Color paletteWhite1(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        short shade = ((float)iterations / maxIterations) * 255;
        return sf::Color(shade, shade, shade);
    }
    return sf::Color::White;
}
sf::Color paletteWhite2(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        float Fiterations = iterations;
        short shade = floor((Fiterations / maxIterations) * 255);
        return sf::Color(shade, shade, shade);
    }
    return sf::Color::Black;
}
sf::Color paletteAbsolute(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        return sf::Color::White;
    }
    return sf::Color::Black;
}





std::vector<std::function<sf::Color(int, int)>> palettes = { def1, def2, paletteWhite1, DEFAULT, five_layers, BCGWMRYKkbcgwnry, PeacocK4, e10000, hsv, golden, lch };
