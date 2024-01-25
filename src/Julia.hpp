#pragma once
#include <SFML\Graphics.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include "Palettes.hpp"
#include "Mandelbrot.hpp"
#include "Global.hpp"





int juliaIterationCheck(double realZ, double imagZ, double realC, double imagC, int maxIterations) {
    const double C0 = realC;
    const double C1 = imagC;
    double Z0 = realZ;
    double Z1 = imagZ;
    double re2;
    double im2;

    int iterations = 0;
    do {
        re2 = Z0 * Z0;
        im2 = Z1 * Z1;
        Z1 = 2 * Z0 * Z1 + C1;
        Z0 = re2 - im2 + C0;
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    return iterations;
}




std::vector<sf::Uint8> generateJuliaChunk(int maxIterations, unsigned long long int zoom, double realC, double imagC, double xOffset, double yOffset, int minY, int maxY, int height, int minX, int maxX, int width, std::function<sf::Color(int, int)> paletteFunction) {
    int iterations;
    std::vector<sf::Uint8> pixels;
    pixels.resize((maxX - minX) * (maxY - minY) * 4);
    int index = 0;
    for (int y = maxY - 1; y >= minY; y--) {
        for (int x = minX; x < maxX; x++) {
            iterations = juliaIterationCheck((x + xOffset) / zoom, (y + yOffset) / zoom, realC, imagC, maxIterations);
            sf::Color colour = paletteFunction(iterations, maxIterations);

            sf::Uint8* pixelPtr = &pixels[index];
            pixelPtr[0] = colour.r;
            pixelPtr[1] = colour.g;
            pixelPtr[2] = colour.b;
            pixelPtr[3] = 255;

            index += 4;
        }
    }
    return pixels;
}

sf::Image loadJulia(unsigned short threadNum, int maxIterations, unsigned long long int zoom, double realC, double imagC, double xCoord, double yCoord, int width, int height, std::function<sf::Color(int, int)> paletteFunction) {
    int minX = -width / 2;
    int maxX = -minX;
    int minY = -height / 2;
    int maxY = -minY;
    int newMinY = minY;
    int newMaxY = maxY;
    double xOffset = xCoord * zoom;
    double yOffset = yCoord * zoom;

    int chunkSize = height / threadNum;
    std::vector<std::vector<sf::Uint8>> arrays;
    arrays.resize(threadNum);

    std::vector<std::thread> threads;
    for (int i = 0; i < threadNum; i++) {
        threads.emplace_back([&, i]() {
            int startRow = minY + i * (maxY - minY) / threadNum;
            int endRow = minY + (i + 1) * (maxY - minY) / threadNum;

            std::vector<sf::Uint8> tempArray = generateJuliaChunk(maxIterations, zoom, realC, imagC, xOffset, yOffset, startRow, endRow, height, minX, maxX, width, paletteFunction);

            std::lock_guard<std::mutex> guard(mutex);
            arrays[threadNum - i - 1] = std::move(tempArray);
            });
    }
    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
    std::vector<sf::Uint8> pixels;
    for (const auto& arr : arrays) {
        pixels.insert(pixels.end(), arr.begin(), arr.end());
    }
    // ERROR TERM
    if (chunkSize * threadNum != height) {
        std::vector<sf::Uint8> tempArray = generateJuliaChunk(maxIterations, zoom, realC, imagC, xOffset, yOffset, minY + chunkSize * threadNum, maxY, height, minX, maxX, width, paletteFunction);
        pixels.insert(pixels.end(), tempArray.begin(), tempArray.end());
    }
    sf::Image image;
    image.create(width, height, pixels.data());
    return image;
}










void gameLoopJulia(unsigned short threads, int width, int height, bool fullscreen) {
    if (width % 2 == 1) width++;
    if (height % 2 == 1) height++;

    int maxIterations = 100;
    unsigned long long int zoom = 450;
    double xCoord = 0;
    double yCoord = 0;


    double realC = 0;
    double imagC = 1;


    int paletteNum = 0;




    sf::Texture texture;
    texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
    sf::Sprite sprite(texture);

    int winWidth = width;
    int winHeight = height;
    sf::RenderWindow window;
    if (fullscreen)
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Julia Set", sf::Style::Fullscreen);
    else {
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Julia Set");
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
                    mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);
                    xCoord = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
                    yCoord = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
                    texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
                    sprite.setTexture(texture);
                }
            } if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        } if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            realC = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
            imagC = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom += zoom / 3;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && zoom > 4) {
            zoom -= zoom / 3;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations += maxIterations / 5;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && maxIterations > 5) {
            maxIterations -= maxIterations / 5;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paletteLength *= 2;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paletteLength >= 2) {
            paletteLength /= 2;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            paletteNum++;
            if (paletteNum == palettes.size()) {
                paletteNum = 0;
            }
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            if (paletteNum == 0) {
                paletteNum = palettes.size() - 1;
            }
            else {
                paletteNum--;
            }
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            texture.copyToImage().saveToFile("julia.png");
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            zoom += zoom / 15;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display the window
        window.display();
    }
}