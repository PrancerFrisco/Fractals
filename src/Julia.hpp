#pragma once
#include <SFML\Graphics.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include "Palettes.hpp"
#include "Mandelbrot.hpp"
#include "ComplexNums.hpp"
#include "Global.hpp"


struct juliaFormula {
    std::function<int(double, double, double, double, int)> func;
    std::function<int(double, double, int)> mandelFunc;
    std::function<void(double, double, double, double, int, std::vector<numPair>&)> orbitFunc;
    std::string name;
};


void blankOrbitJuliaFunc(double real, double imag, double realC, double imagC, int maxIterations, std::vector<numPair>& pointsVec) {}

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
void juliaOrbit(double realZ, double imagZ, double realC, double imagC, int maxIterations, std::vector<numPair>& pointsVec) {
    pointsVec.clear();
    pointsVec.resize(maxIterations);
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
        pointsVec[iterations] = { Z0, Z1 };
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    pointsVec.resize(iterations);
}

int burningShipJuliaIterationCheck(double realZ, double imagZ, double realC, double imagC, int maxIterations) {
    const double C0 = realC;
    const double C1 = imagC;
    double Z0 = realZ;
    double Z1 = imagZ;
    double re2;
    double im2;

    int iterations = 0;
    do {
        Z0 = abs(Z0);
        Z1 = -abs(Z1);
        re2 = Z0 * Z0;
        im2 = Z1 * Z1;
        Z1 = 2 * Z0 * Z1 + C1;
        Z0 = re2 - im2 + C0;
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    return iterations;
}
void burningShipJuliaOrbit(double realZ, double imagZ, double realC, double imagC, int maxIterations, std::vector<numPair>& pointsVec) {
    pointsVec.clear();
    pointsVec.resize(maxIterations);
    const double C0 = realC;
    const double C1 = imagC;
    double Z0 = realZ;
    double Z1 = imagZ;
    double re2;
    double im2;

    int iterations = 0;
    do {
        Z0 = abs(Z0);
        Z1 = -abs(Z1);
        re2 = Z0 * Z0;
        im2 = Z1 * Z1;
        Z1 = 2 * Z0 * Z1 + C1;
        Z0 = re2 - im2 + C0;
        pointsVec[iterations] = { Z0, Z1 };
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    pointsVec.resize(iterations);
}
int julia3rdIterationCheck(double realZ, double imagZ, double realC, double imagC, int maxIterations) {
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
        double origZ0 = Z0;
        Z0 = Z0 * (re2 - im2) - 2 * Z0 * im2 + C0;
        Z1 = origZ0 * (2 * origZ0 * Z1) + Z1 * (re2 - im2) + C1;

        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    return iterations;
}
void julia3rdOrbit(double realZ, double imagZ, double realC, double imagC, int maxIterations, std::vector<numPair>& pointsVec) {
    pointsVec.clear();
    pointsVec.resize(maxIterations);
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
        double origZ0 = Z0;
        Z0 = Z0 * (re2 - im2) - 2 * Z0 * im2 + C0;
        Z1 = origZ0 * (2 * origZ0 * Z1) + Z1 * (re2 - im2) + C1;
        pointsVec[iterations] = { Z0, Z1 };
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    pointsVec.resize(iterations);
}








std::vector<juliaFormula> formulasJulia = { {juliaIterationCheck, mandelbrotIterationCheck, juliaOrbit, "julia sets"}, {burningShipJuliaIterationCheck, burningShipIterationCheck, burningShipJuliaOrbit, "burning ship"}, {julia3rdIterationCheck, mandelbrot3rdIterationCheck, julia3rdOrbit, "julia third power"} };





std::vector<sf::Uint8> generateJuliaChunk(int maxIterations, unsigned long long int zoom, double realC, double imagC, double xCoord, double yCoord, int minY, int maxY, int minX, int maxX, std::function<sf::Color(int, int)> paletteFunction, const std::function<int(double, double, double, double, int)>& iterationFunction) {
    int iterations;
    std::vector<sf::Uint8> pixels;
    pixels.resize((maxX - minX) * (maxY - minY) * 4);
    double zoomInverse = 1.0 / zoom;
    int index = 0;
    for (int y = maxY - 1; y >= minY; y--) {
        for (int x = minX; x < maxX; x++) {
            iterations = iterationFunction(xCoord + x * zoomInverse, yCoord + y * zoomInverse, realC, imagC, maxIterations);
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

sf::Image loadJulia(unsigned short threadNum, int maxIterations, unsigned long long int zoom, double realC, double imagC, double xCoord, double yCoord, int width, int height, std::function<sf::Color(int, int)> paletteFunction, const std::function<int(double, double, double, double, int)>& iterationFunction) {
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

            std::vector<sf::Uint8> tempArray = generateJuliaChunk(maxIterations, zoom, realC, imagC, xCoord, yCoord, startRow, endRow, minX, maxX, paletteFunction, iterationFunction);

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
        std::vector<sf::Uint8> tempArray = generateJuliaChunk(maxIterations, zoom, realC, imagC, xCoord, yCoord, minY + chunkSize * threadNum, maxY, minX, maxX, paletteFunction, iterationFunction);
        pixels.insert(pixels.end(), tempArray.begin(), tempArray.end());
    }
    sf::Image image;
    image.create(width, height, pixels.data());
    return image;
}

//create animation in 4k and upload to youtube

void animationJulia(unsigned short threads, int width, int height, bool fullscreen) {
    double a = 0;
    if (width % 2 == 1) width++;
    if (height % 2 == 1) height++;



    int maxIterations = 300;
    unsigned long long int zoom = std::min(width, height) / 4;
    double xCoord = 0;
    double yCoord = 0;
    int paletteNum = 1;
    int frameNum = 0;
    sf::Texture texture;
    sf::Sprite sprite(texture);
    int winWidth = width;
    int winHeight = height;
    int scaleFactor = 1;
    sf::RenderWindow window;
    if (fullscreen)
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Julia Set", sf::Style::Fullscreen);
    else {
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Julia Set");
    }
    while (window.isOpen() && a < 3.1415*2) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        }

        texture.loadFromImage(loadJulia(threads, maxIterations, zoom, 0.7885 * c_exp_imag(a).real, 0.7885 * c_exp_imag(a).imag, xCoord, yCoord, width, height, palettes[paletteNum], juliaIterationCheck));
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));


        // Clear the window
        window.clear();
        sprite.setScale(scaleFactor, scaleFactor);

        // Draw the sprite
        window.draw(sprite);

        // Display the window
        window.display();
        std::string fileName = std::to_string(frameNum) + ".png";
        // make fileNum length 10 chars
        fileName = "animation/" + std::string(10 - fileName.length(), '0') + fileName;
        //std::cout << fileName << '\n';
        texture.copyToImage().saveToFile(fileName);
        a += 0.0009765625;
        frameNum++;
    }
}






void manualAdjustJulia(unsigned long long int& zoom, double& xCoord, double& yCoord, double& realC, double& imagC, int& maxIterations) {
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

void gameLoopJulia(unsigned short threads, int width, int height, bool fullscreen) {
    if (width % 2 == 1) width++;
    if (height % 2 == 1) height++;

    int maxIterations = 50;
    int maxIterationsLine = 50;
    unsigned long long int zoom = 450;
    double xCoord = 0;
    double yCoord = 0;
    double xCoordLine = 0;
    double yCoordLine = 0;

    double realC = 0;
    double imagC = 1;


    int paletteNum = 0;
    int formulaNum = 0;




    sf::Texture texture;
    texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
    sf::Sprite sprite(texture);

    int winWidth = width;
    int winHeight = height;
    sf::RenderWindow window;
    std::vector<numPair> pointsVec;
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
            if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
                mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);

                xCoord = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
                yCoord = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
                texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
                sprite.setTexture(texture);
                pointsVec.clear();
            } if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
            mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);

            xCoordLine = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
            yCoordLine = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;

            //mandelbrotOrbit(xCoord, -yCoord, maxIterations, pointsVec);
            formulasJulia[formulaNum].orbitFunc(xCoordLine, yCoordLine, realC, imagC, maxIterationsLine, pointsVec);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
            mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);
            realC = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
            imagC = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
            pointsVec.clear();
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            texture.copyToImage().saveToFile("julia.png");
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom += zoom / 15;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom *= 2;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 15;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 2;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations += maxIterations / 15;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations +=  maxIterations / 5;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            maxIterations -= maxIterations / 15;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && maxIterations > 5) {
            maxIterations -= maxIterations / 5;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paletteLength *= 2;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paletteLength -= paletteLength / 2;
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            paletteNum++;
            if (paletteNum == palettes.size()) {
                paletteNum = 0;
            }
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            if (paletteNum == 0) {
                paletteNum = palettes.size() - 1;
            }
            else {
                paletteNum--;
            }
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            manualAdjustJulia(zoom, xCoord, yCoord, realC, imagC, maxIterations);
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].mandelFunc));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            formulaNum++;
            if (formulaNum == formulasJulia.size()) {
                formulaNum = 0;
            }
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::cout << formulasJulia[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (formulaNum == 0) {
                formulaNum = formulasJulia.size() - 1;
            }
            else {
                formulaNum--;
            }
            texture.loadFromImage(loadJulia(threads, maxIterations, zoom, realC, imagC, xCoord, yCoord, width, height, palettes[paletteNum], formulasJulia[formulaNum].func));
            sprite.setTexture(texture);
            std::cout << formulasJulia[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            maxIterationsLine++;
            formulasJulia[formulaNum].orbitFunc(xCoordLine, yCoordLine, realC, imagC, maxIterationsLine, pointsVec);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && maxIterationsLine > 1) {
            maxIterationsLine--;
            formulasJulia[formulaNum].orbitFunc(xCoordLine, yCoordLine, realC, imagC, maxIterationsLine, pointsVec);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        
        

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        drawPoints(zoom, xCoord, yCoord, width, height, pointsVec, window);

        // Display the window
        window.display();
    }
}
