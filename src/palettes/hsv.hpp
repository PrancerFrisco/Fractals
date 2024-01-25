#pragma once
#include <SFML\Graphics.hpp>
#include "Global.hpp"
#include "Palettes.hpp"


class HSV {
public:
    float H, S, V;

    HSV(float h, float s, float v) {
        this->H = h;
        this->S = s / 100.0f;
        this->V = v / 100.0f;
    }

    const sf::Color toRGB() {
        float R, G, B, C, X, m;
        float Hp = this->H / 60.0f;
        C = this->V * this->S;
        X = C * (1 - abs(fmodf(Hp, 2) - 1));
        m = this->V - C;
        if (Hp < 1) {
            R = C; G = X; B = 0;
        }
        else if (Hp < 2) {
            R = X; G = C; B = 0;
        }
        else if (Hp < 3) {
            R = 0; G = C; B = X;
        }
        else if (Hp < 4) {
            R = 0; G = X; B = C;
        }
        else if (Hp < 5) {
            R = X; G = 0; B = C;
        }
        else {
            R = C; G = 0; B = X;
        }
        return { (sf::Uint8)((R+m) * 255), (sf::Uint8)((G + m) * 255), (sf::Uint8)((B + m) * 255) };
    }
};










sf::Color hsv(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        HSV colour(fmodf(powf(360 * iterations / maxIterations / paletteLength, 1.5f), 360), 100, 700 * iterations / (float)maxIterations);
        return colour.toRGB();
    }
    return sf::Color::Black;
}