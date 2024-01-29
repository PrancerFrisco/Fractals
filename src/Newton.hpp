#pragma once
#include <SFML\Graphics.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include "Palettes.hpp"
#include "Global.hpp"
#include <iostream>
#include "ComplexNums.hpp"
#include <sstream>
#include <iomanip>


struct newtonFormula {
    std::function<int(double, double, int)> func;
    std::string name;
};
struct newtonFormulaJulia {
    std::function<int(double, double, double, double, int)> func;
    std::function<int(double, double, int)> newtonFunc;
    std::string name;
};





int newtonIterationCheck(double real, double imag, int maxIterations) {
    double tolerance = 0.01;
    double Z0 = real;
    double Z1 = imag;

    for (int i = 0; i < maxIterations; i++) {
        //top = { Z0 * (Z0 * Z0 - 3 * Z1 * Z1) - 1, Z1 * (3 * Z0 * Z0 - Z1 * Z1) };
        //bottom = { 3 * (Z0 * Z0 - Z1 * Z1), 6 * Z0 * Z1 };
        //Complex top = c_cubed(Z) - Complex(1);
        //Complex bottom = Complex(3) * c_squared(Complex(Z0, Z1));
        double bottom0 = 3 * (Z0 * Z0 - Z1 * Z1);
        double bottom1 = 6 * Z0 * Z1;
        double top0 = Z0 * (Z0 * Z0 - 3 * Z1 * Z1) - 1;
        double top1 = Z1 * (3 * Z0 * Z0 - Z1 * Z1);
        double bottomProdConj = (bottom0 * bottom0 + bottom1 * bottom1);
        double result0 = (top0 * bottom0 + top1*bottom1) / bottomProdConj;
        double result1 = (-top0 * bottom1 + top1 * bottom0) / bottomProdConj;

        
        Z0 -= result0;
        Z1 -= result1;

        
        for (int i = 0; i < 3; i++) {
            double a = sin(6.2831853071795864769252867 * i / 3.0) - Z1;
            double b = cos(6.2831853071795864769252867 * i / 3.0) - Z0;
            double distance = sqrt(a * a + b * b);
            if (distance < tolerance) {
                return i;
            }
        }
    }
     //pythagorean theorem will go over each root and the one with the lowest distance to Z will be returned
    double minDistance = 100;
    int minDistanceNum = 0;
    for (int i = 0; i < 3; i++) {
        double a = sin(6.2831853071795864769252867 * i / 3.0) - Z1;
        double b = cos(6.2831853071795864769252867 * i / 3.0) - Z0;
        double distance = sqrt(a * a + b * b);
        if (distance < minDistance) {
            minDistance = distance;
            minDistanceNum = i;
        }
    }
    return minDistanceNum;
}







int newton4thIterationCheck(double real, double imag, int maxIterations) {
    double tolerance = 0.01;
    //Complex Z = { real, imag };
    double Z0 = real;
    double Z1 = imag;

    for (int i = 0; i < maxIterations; i++) {
        //Complex top = { -1 + (Z0 * Z0 - Z1 * Z1) * (Z0 * Z0 - Z1 * Z1) - (2 * Z0 * Z1) * (2 * Z0 * Z1), 4 * Z0 * Z1 * (Z0 * Z0 - Z1 * Z1) };
        //Complex bottom = { 3 * Z0 * (Z0 * Z0 - 3 * Z1 * Z1), 3 * Z1 * (3 * Z0 * Z0 - Z1 * Z1) };

        double top0 = -1 + (Z0 * Z0 - Z1 * Z1) * (Z0 * Z0 - Z1 * Z1) - (2 * Z0 * Z1) * (2 * Z0 * Z1);
        double top1 = 4 * Z0 * Z1 * (Z0 * Z0 - Z1 * Z1);
        double bottom0 = 3 * Z0 * (Z0 * Z0 - 3 * Z1 * Z1);
        double bottom1 = 3 * Z1 * (3 * Z0 * Z0 - Z1 * Z1);

        double bottomProdConj = (bottom0 * bottom0 + bottom1 * bottom1);
        double result0 = (top0 * bottom0 + top1 * bottom1) / bottomProdConj;
        double result1 = (-top0 * bottom1 + top1 * bottom0) / bottomProdConj;
        //Complex top = c_squared(c_squared(Z)) - Complex(1);
        //Complex bottom = Complex(3) * c_cubed(Z);

        //Z -= Complex(weightNewton) * top / bottom;
        Z0 -= result0;
        Z1 -= result1;


        for (int i = 0; i < 4; i++) {
            double a = sin(6.2831853071795864769252867 * i / 4.0) - Z1;
            double b = cos(6.2831853071795864769252867 * i / 4.0) - Z0;
            double distance = sqrt(a * a + b * b);
            if (distance < tolerance) {
                return i;
            }
        }
    }
    double minDistance = 100;
    int minDistanceNum = 0;
    for (int i = 0; i < 4; i++) {
        // abs value of distance
        double a = sin(6.2831853071795864769252867 * i / 4.0) - Z1;
        double b = cos(6.2831853071795864769252867 * i / 4.0) - Z0;
        double distance = sqrt(a * a + b * b);
        if (distance < minDistance) {
            minDistance = distance;
            minDistanceNum = i;
        }
    }
    return minDistanceNum;
}
int newtonIterationCheckJulia(double real, double imag, double realC, double imagC, int maxIterations) {
    double tolerance = 0.01;
    double Z0 = real;
    double Z1 = imag;
    for (int i = 0; i < maxIterations; i++) {
        double bottom0 = 3 * (Z0 * Z0 - Z1 * Z1);
        double bottom1 = 6 * Z0 * Z1;
        double top0 = Z0 * (Z0 * Z0 - 3 * Z1 * Z1) - 1;
        double top1 = Z1 * (3 * Z0 * Z0 - Z1 * Z1);
        double bottomProdConj = (bottom0 * bottom0 + bottom1 * bottom1);
        double result0 = (top0 * bottom0 + top1 * bottom1) / bottomProdConj;
        double result1 = (-top0 * bottom1 + top1 * bottom0) / bottomProdConj;

        result0 = result0 * realC - result1 * imagC;
        result1 = result0 * imagC + result1 * realC;

        Z0 -= result0;
        Z1 -= result1;

        for (int i = 0; i < 3; i++) {
            double a = sin(6.2831853071795864769252867 * i / 3.0) - Z1;
            double b = cos(6.2831853071795864769252867 * i / 3.0) - Z0;
            double distance = sqrt(a * a + b * b);
            if (distance < tolerance) {
                return i;
            }
        }
    }
    double minDistance = 100;
    int minDistanceNum = 0;
    for (int i = 0; i < 3; i++) {
        double a = sin(6.2831853071795864769252867 * i / 3.0) - Z1;
        double b = cos(6.2831853071795864769252867 * i / 3.0) - Z0;
        double distance = sqrt(a * a + b * b);
        if (distance < minDistance) {
            minDistance = distance;
            minDistanceNum = i;
        }
    }
    return minDistanceNum;
}
int newton4thIterationCheckJulia(double realZ, double imagZ, double realC, double imagC, int maxIterations) {
    double tolerance = 0.01;
    //Complex Z = { real, imag };
    double Z0 = realZ;
    double Z1 = imagZ;

    for (int i = 0; i < maxIterations; i++) {
        //Complex top = { -1 + (Z0 * Z0 - Z1 * Z1) * (Z0 * Z0 - Z1 * Z1) - (2 * Z0 * Z1) * (2 * Z0 * Z1), 4 * Z0 * Z1 * (Z0 * Z0 - Z1 * Z1) };
        //Complex bottom = { 3 * Z0 * (Z0 * Z0 - 3 * Z1 * Z1), 3 * Z1 * (3 * Z0 * Z0 - Z1 * Z1) };

        double top0 = -1 + (Z0 * Z0 - Z1 * Z1) * (Z0 * Z0 - Z1 * Z1) - (2 * Z0 * Z1) * (2 * Z0 * Z1);
        double top1 = 4 * Z0 * Z1 * (Z0 * Z0 - Z1 * Z1);
        double bottom0 = 3 * Z0 * (Z0 * Z0 - 3 * Z1 * Z1);
        double bottom1 = 3 * Z1 * (3 * Z0 * Z0 - Z1 * Z1);

        double bottomProdConj = (bottom0 * bottom0 + bottom1 * bottom1);
        double result0 = (top0 * bottom0 + top1 * bottom1) / bottomProdConj;
        double result1 = (-top0 * bottom1 + top1 * bottom0) / bottomProdConj;
        //Complex top = c_squared(c_squared(Z)) - Complex(1);
        //Complex bottom = Complex(3) * c_cubed(Z);

        //Z -= Complex(weightNewton) * top / bottom;


        




        // result *= weight
        result0 = result0 * realC - result1 * imagC;
        result1 = result0 * imagC + result1 * realC;




        Z0 -= result0;
        Z1 -= result1;


        for (int i = 0; i < 4; i++) {
            double a = sin(6.2831853071795864769252867 * i / 4.0) - Z1;
            double b = cos(6.2831853071795864769252867 * i / 4.0) - Z0;
            double distance = sqrt(a * a + b * b);
            if (distance < tolerance) {
                return i;
            }
        }
    }
    double minDistance = 100;
    int minDistanceNum = 0;
    for (int i = 0; i < 4; i++) {
        // abs value of distance
        double a = sin(6.2831853071795864769252867 * i / 4.0) - Z1;
        double b = cos(6.2831853071795864769252867 * i / 4.0) - Z0;
        double distance = sqrt(a * a + b * b);
        if (distance < minDistance) {
            minDistance = distance;
            minDistanceNum = i;
        }
    }
    return minDistanceNum;
}




std::vector<newtonFormula> formulasNewton = { {newtonIterationCheck, "newton 3rd power fractal"}, {newton4thIterationCheck, "newton 4th power fractal"} };
std::vector<newtonFormulaJulia> formulasNewtonJulia = { {newtonIterationCheckJulia, newtonIterationCheck, "newton 3rd power Julia set"}, {newton4thIterationCheckJulia, newton4thIterationCheck, "newton 4th power Julia set"} };












std::vector<sf::Uint8> generateNewtonChunk(int maxIterations, unsigned long long int zoom, double xCoord, double yCoord, int minY, int maxY, int minX, int maxX, const std::function<int(double, double, int)>& rootFunction) {
    int root;
    std::vector<sf::Uint8> pixels;
    pixels.resize((maxX - minX) * (maxY - minY) * 4);
    double zoomInverse = 1.0 / zoom; // multiplication by the inverse should be faster than division
    int index = 0;
    std::vector<sf::Color> colours = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}, {255, 0, 255} };
    for (int y = maxY - 1; y >= minY; y--) {
        for (int x = minX; x < maxX; x++) {
            root = rootFunction(xCoord + x * zoomInverse, yCoord + y * zoomInverse, maxIterations);
            //sf::Color colour = paletteFunction(iterations, maxIterations);
            sf::Color colour = colours[root];
            

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








sf::Image loadNewton(unsigned short threadNum, int maxIterations, unsigned long long int zoom, double xCoord, double yCoord, int width, int height, const std::function<int(double, double, int)>& rootFunction) {
    int minX = -width / 2;
    int maxX = -minX;
    int minY = -height / 2;
    int maxY = -minY;
    int newMinY = minY;
    int newMaxY = maxY;

    int chunkSize = height / threadNum;
    std::vector<std::vector<sf::Uint8>> arrays;
    arrays.resize(threadNum);

    std::vector<std::thread> threads;
    for (int i = 0; i < threadNum; i++) {
        threads.emplace_back([&, i]() {
            int startRow = minY + i * (maxY - minY) / threadNum;
            int endRow = minY + (i + 1) * (maxY - minY) / threadNum;

            std::vector<sf::Uint8> tempArray = generateNewtonChunk(maxIterations, zoom, xCoord, yCoord, startRow, endRow, minX, maxX, rootFunction);

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
        std::vector<sf::Uint8> tempArray = generateNewtonChunk(maxIterations, zoom, xCoord, yCoord, minY + chunkSize * threadNum, maxY, minX, maxX, rootFunction);
        pixels.insert(pixels.end(), tempArray.begin(), tempArray.end());
    }
    sf::Image image;
    image.create(width, height, pixels.data());
    return image;
}

std::vector<sf::Uint8> generateNewtonChunkJulia(int maxIterations, unsigned long long int zoom, double xCoord, double yCoord, double realC, double imagC, int minY, int maxY, int minX, int maxX, const std::function<int(double, double, double, double, int)>& rootFunction) {
    int root;
    std::vector<sf::Uint8> pixels;
    pixels.resize((maxX - minX) * (maxY - minY) * 4);
    double zoomInverse = 1.0 / zoom; // multiplication by the inverse should be faster than division
    int index = 0;
    std::vector<sf::Color> colours = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}, {255, 0, 255} };
    for (int y = maxY - 1; y >= minY; y--) {
        for (int x = minX; x < maxX; x++) {
            root = rootFunction(xCoord + x * zoomInverse, yCoord + y * zoomInverse, realC, imagC, maxIterations);
            //sf::Color colour = paletteFunction(iterations, maxIterations);
            sf::Color colour = colours[root];


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

sf::Image loadNewtonJulia(unsigned short threadNum, int maxIterations, unsigned long long int zoom, double realC, double imagC, double xCoord, double yCoord, int width, int height, const std::function<int(double, double, double, double, int)>& rootFunction) {
    int minX = -width / 2;
    int maxX = -minX;
    int minY = -height / 2;
    int maxY = -minY;
    int newMinY = minY;
    int newMaxY = maxY;

    int chunkSize = height / threadNum;
    std::vector<std::vector<sf::Uint8>> arrays;
    arrays.resize(threadNum);

    std::vector<std::thread> threads;
    for (int i = 0; i < threadNum; i++) {
        threads.emplace_back([&, i]() {
            int startRow = minY + i * (maxY - minY) / threadNum;
            int endRow = minY + (i + 1) * (maxY - minY) / threadNum;

            std::vector<sf::Uint8> tempArray = generateNewtonChunkJulia(maxIterations, zoom, xCoord, yCoord, realC, imagC, startRow, endRow, minX, maxX, rootFunction);

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
        std::vector<sf::Uint8> tempArray = generateNewtonChunkJulia(maxIterations, zoom, xCoord, yCoord, realC, imagC, minY + chunkSize * threadNum, maxY, minX, maxX, rootFunction);
        pixels.insert(pixels.end(), tempArray.begin(), tempArray.end());
    }
    sf::Image image;
    image.create(width, height, pixels.data());
    return image;
}











void manualAdjustNewton(unsigned long long int& zoom, double& xCoord, double& yCoord, int& maxIterations) {
    std::cout << std::fixed << std::setprecision(15) << "\n\n\n(" << xCoord << ", " << yCoord << ")\n";
    std::cout << "zoom: " << zoom << '\n';
    std::cout << "iterations: " << maxIterations << '\n';

    std::string userInput;
    std::cout << "\n";
    std::getline(std::cin, userInput);

    std::cout << "enter a new value of x: ";
    std::getline(std::cin, userInput);
    std::istringstream issX(userInput);
    if (issX >> xCoord) std::cout << "x coord: " << xCoord << '\n';
    else std::cout << "unsuccessful conversion to double\n";

    std::cout << "enter a new value of y: ";
    std::getline(std::cin, userInput);
    std::istringstream issY(userInput);
    if (issY >> yCoord) std::cout << "y coord: " << yCoord << '\n';
    else std::cout << "unsuccessful conversion to double\n";

    std::cout << "enter a new value for zoom: ";
    std::getline(std::cin, userInput);
    std::istringstream issZoom(userInput);
    if (issZoom >> zoom) std::cout << "zoom: " << zoom << '\n';
    else std::cout << "unsuccessful conversion to integer\n";

    std::cout << "enter a new value for iterations: ";
    std::getline(std::cin, userInput);
    std::istringstream issIters(userInput);
    if (issIters >> maxIterations) std::cout << "iterations: " << maxIterations << '\n';
}





void gameLoopNewton(unsigned short threads, int width, int height, bool fullscreen) {
    if (width % 2 == 1) width++;
    if (height % 2 == 1) height++;



    int maxIterations = 10;
    unsigned long long int zoom = 450;
    double xCoord = 0;
    double yCoord = 0;
    int paletteNum = 4;
    int formulaNum = 0;



    sf::Texture texture;
    texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
    sf::Sprite sprite(texture);

    int winWidth = width;
    int winHeight = height;
    int scaleFactor = 1;
    sf::RenderWindow window;
    if (fullscreen)
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Newton Fractal", sf::Style::Fullscreen);
    else {
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Newton Fractal");
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
                mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);

                xCoord = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
                yCoord = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
                texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
                sprite.setTexture(texture);
            }  if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom += zoom / 15;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom *= 2;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 15;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 2;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations += maxIterations / 5;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations *= 2;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            maxIterations -= maxIterations / 5;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            maxIterations -= maxIterations / 2;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paletteLength *= 2;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paletteLength -= paletteLength / 2;
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            paletteNum++;
            if (paletteNum == palettes.size()) {
                paletteNum = 0;
            }
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            if (paletteNum == 0) {
                paletteNum = palettes.size() - 1;
            }
            else {
                paletteNum--;
            }
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            formulaNum++;
            if (formulaNum == formulasNewton.size()) {
                formulaNum = 0;
            }
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
            std::cout << formulasNewton[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (formulaNum == 0) {
                formulaNum = formulasNewton.size() - 1;
            }
            else {
                formulaNum--;
            }
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
            std::cout << formulasNewton[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            manualAdjustNewton(zoom, xCoord, yCoord, maxIterations);
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewton[formulaNum].func));
            sprite.setTexture(texture);
        }

        sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));


        // Clear the window
        window.clear();
        sprite.setScale(scaleFactor, scaleFactor);

        // Draw the sprite
        window.draw(sprite);

        // Display the window
        window.display();
    }
}


void manualAdjustNewtonJulia(unsigned long long int& zoom, double& xCoord, double& yCoord, double& realC, double& imagC, int& maxIterations) {
    std::cout << std::fixed << std::setprecision(15) << "\n\n\n(Z: " << xCoord << ", " << yCoord << ")\n";
    std::cout << std::fixed << std::setprecision(15) << "\n\n\n(C: " << realC << ", " << imagC << ")\n";
    std::cout << "zoom: " << zoom << '\n';
    std::cout << "iterations: " << maxIterations << '\n';

    std::string userInput;
    std::cout << "\n";
    std::getline(std::cin, userInput);

    std::cout << "FOR Z:\nenter a new value of x: ";
    std::getline(std::cin, userInput);
    std::istringstream issX(userInput);
    if (issX >> xCoord) std::cout << "x coord: " << xCoord << '\n';
    else std::cout << "unsuccessful conversion to double\n";

    std::cout << "enter a new value of y: ";
    std::getline(std::cin, userInput);
    std::istringstream issY(userInput);
    if (issY >> yCoord) std::cout << "y coord: " << yCoord << '\n';
    else std::cout << "unsuccessful conversion to double\n";

    std::cout << "FOR C:\nenter a new value of x: ";
    std::getline(std::cin, userInput);
    std::istringstream issCX(userInput);
    if (issCX >> realC) std::cout << "x coord: " << realC << '\n';
    else std::cout << "unsuccessful conversion to double\n";

    std::cout << "enter a new value of y: ";
    std::getline(std::cin, userInput);
    std::istringstream issCY(userInput);
    if (issCY >> imagC) std::cout << "y coord: " << imagC << '\n';
    else std::cout << "unsuccessful conversion to double\n";


    std::cout << "enter a new value for zoom: ";
    std::getline(std::cin, userInput);
    std::istringstream issZoom(userInput);
    if (issZoom >> zoom) std::cout << "zoom: " << zoom << '\n';
    else std::cout << "unsuccessful conversion to integer\n";

    std::cout << "enter a new value for iterations: ";
    std::getline(std::cin, userInput);
    std::istringstream issIters(userInput);
    if (issIters >> maxIterations) std::cout << "iterations: " << maxIterations << '\n';
}

void gameLoopNewtonJulia(unsigned short threads, int width, int height, bool fullscreen) {
    if (width % 2 == 1) width++;
    if (height % 2 == 1) height++;

    int maxIterations = 10;
    unsigned long long int zoom = 450;
    double xCoord = 0;
    double yCoord = 0;


    double realC = 0;
    double imagC = 1;


    int paletteNum = 0;
    int formulaNum = 0;




    sf::Texture texture;
    texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
    sf::Sprite sprite(texture);

    int winWidth = width;
    int winHeight = height;
    sf::RenderWindow window;
    if (fullscreen)
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Newton Julia Set", sf::Style::Fullscreen);
    else {
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Newton Julia Set");
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
                    texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
                    sprite.setTexture(texture);
                }
            } if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
            mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);
            realC = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
            imagC = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            texture.copyToImage().saveToFile("julia.png");
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom += zoom / 15;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom *= 2;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 15;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 2;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations += maxIterations / 15;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations += maxIterations / 5;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            maxIterations -= maxIterations / 15;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && maxIterations > 5) {
            maxIterations -= maxIterations / 5;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paletteLength *= 2;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paletteLength -= paletteLength / 2;
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            paletteNum++;
            if (paletteNum == palettes.size()) {
                paletteNum = 0;
            }
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            if (paletteNum == 0) {
                paletteNum = palettes.size() - 1;
            }
            else {
                paletteNum--;
            }
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            manualAdjustNewtonJulia(zoom, xCoord, yCoord, realC, imagC, maxIterations);
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            texture.loadFromImage(loadNewton(threads, maxIterations, zoom, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].newtonFunc));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            formulaNum++;
            if (formulaNum == formulasNewtonJulia.size()) {
                formulaNum = 0;
            }
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::cout << formulasNewtonJulia[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (formulaNum == 0) {
                formulaNum = formulasNewtonJulia.size() - 1;
            }
            else {
                formulaNum--;
            }
            texture.loadFromImage(loadNewtonJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, formulasNewtonJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::cout << formulasNewtonJulia[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }




        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display the window
        window.display();
    }
}