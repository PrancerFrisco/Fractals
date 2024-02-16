#pragma once
#include <SFML\Graphics.hpp>
#include "Global.hpp"

const struct lab {
    float l;
    float a;
    float b;
};

const struct lchS {
    float l;
    float c;
    float h;
};
const struct xyz {
    float x;
    float y;
    float z;
};

lab lch2lab(lchS LCH) {
    const float ab = sin(LCH.h * 0.01745329251f) * LCH.c;
    return { LCH.l, ab, ab };
}

xyz lab2xyz(lab LAB) {

    float y = (LAB.l + 16) / 116.0f;
    float x = LAB.a / 500.0f + y;
    float z = y - LAB.b / 200.0f;

    if (y * y * y > 0.008856f) {
        y = y * y * y;
    }
    else {
        y = (y - 0.137931034f) / 7.787f;
    }

    if (x*x*x > 0.008856f) {
        x = x * x * x;
    }
    else {
        x = (x - 0.137931034f) / 7.787f;
    }

    if (z*z*z > 0.008856f) {
        z = z * z * z;
    }
    else {
        z = (z - 0.137931034f) / 7.787f;
    }

    x = 95.047f * x;
    y = 100.000f * y;
    z = 108.883f * z;

    return { x, y, z };
}

sf::Color xyz2rgb(xyz XYZ) {
    const float x = XYZ.x / 100.0f; // X from 0 to 95.047
    const float y = XYZ.y / 100.0f; // Y from 0 to 100.000
    const float z = XYZ.z / 100.0f; // Z from 0 to 108.883

    float r = x * 3.2406f + y * -1.5372f + z * -0.4986f;
    float g = x * -0.9689f + y * 1.8758f + z * 0.0415f;
    float b = x * 0.0557f + y * -0.2040f + z * 1.0570f;

    if (r > 0.0031308f) {
        r = 1.055f * powf(r, 0.41666667f) - 0.055f;
    }
    else {
        r = 12.92f * r;
    }

    if (g > 0.0031308f) {
        g = 1.055f * powf(g, 0.41666667f) - 0.055f;
    }
    else {
        g = 12.92f * g;
    }

    if (b > 0.0031308f) {
        b = 1.055f * powf(b, 0.41666667f) - 0.055f;
    }
    else {
        b = 12.92f * b;
    }

    r *= 255;
    g *= 255;
    b *= 255;

    return { (sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b };
}


sf::Color lch2rgb(lchS LCH) {
    return xyz2rgb(lab2xyz(lch2lab(LCH)));
}






sf::Color lch(int iterations, int maxIterations) {
    if (iterations < maxIterations) {
        float s = iterations / (float)maxIterations;
        const float v = 1.0 - powf(cos(3.1415926f * s), 2.0f);
        lchS colour = { 75 - (75 * v), 28 + (75 - (75 * v)), fmodf(powf(360 * s, 1.5f), 360) };
        return lch2rgb(colour);
    }
    return sf::Color::Black;
}
