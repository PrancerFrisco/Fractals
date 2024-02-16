#pragma once
#include <mutex>

std::mutex mutex;
int normaliseINT(float n, float start1, float stop1, float start2, float stop2) {
    return round(((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2);
}
struct numPair {
    double num1;
    double num2;
};



void drawPoints(unsigned long long int zoom, double xCoord, double yCoord, int width, int height, std::vector<numPair>& pointsVec, sf::RenderWindow& window) {
    for (int i = 1; i < pointsVec.size(); ++i)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(zoom * pointsVec[i - 1].num1 - (xCoord * zoom) + width / 2, zoom * pointsVec[i - 1].num2 + (yCoord * zoom) + height / 2)),
            sf::Vertex(sf::Vector2f(zoom * pointsVec[i].num1 - (xCoord * zoom) + width / 2, zoom * pointsVec[i].num2 + (yCoord * zoom) + height / 2))
        };
        window.draw(line, 2, sf::Lines);
    }
}




int paletteLength = 1;
