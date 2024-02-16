#pragma once
#include <SFML\Graphics.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include "Palettes.hpp"
#include "Global.hpp"
#include "ComplexNums.hpp"
#include <sstream>
#include <iomanip>



struct mandelFormula {
    std::function<int(double, double, int)> func;
    std::function<void(double, double, int, std::vector<numPair>&)> orbitFunc;
    std::string name;
};


void blankOrbitMandelFunc(double real, double imag, int maxIterations, std::vector<numPair>& pointsVec) {}

int mandelbrotIterationCheck(double real, double imag, int maxIterations) {
    const double C0 = real;
    const double C1 = imag;
    double Z0 = real;
    double Z1 = imag;
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
void mandelbrotOrbit(double real, double imag, int maxIterations, std::vector<numPair>& pointsVec) {
    pointsVec.clear();
    pointsVec.resize(maxIterations);
    const double C0 = real;
    const double C1 = imag;
    double Z0 = real;
    double Z1 = imag;
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

int mandelbrot3rdIterationCheck(double real, double imag, int maxIterations) {
    const double C0 = real;
    const double C1 = imag;
    double Z0 = real;
    double Z1 = imag;
    double re2, im2;



    int iterations = 0;
    do {
        re2 = Z0 * Z0;
        im2 = Z1 * Z1;
        const double origZ0 = Z0;
        Z0 = Z0 * (re2 - im2) - 2 * Z0 * im2 + C0;
        Z1 = origZ0 * (2 * origZ0 * Z1) + Z1 * (re2 - im2) + C1;

        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    return iterations;
}
void mandelbrot3rdOrbit(double real, double imag, int maxIterations, std::vector<numPair>& pointsVec) {
    pointsVec.clear();
    pointsVec.resize(maxIterations);
    const double C0 = real;
    const double C1 = imag;
    double Z0 = real;
    double Z1 = imag;
    double re2, im2;



    int iterations = 0;
    do {
        re2 = Z0 * Z0;
        im2 = Z1 * Z1;
        const double origZ0 = Z0;
        Z0 = Z0 * (re2 - im2) - 2 * Z0 * im2 + C0;
        Z1 = origZ0 * (2 * origZ0 * Z1) + Z1 * (re2 - im2) + C1;
        pointsVec[iterations] = { Z0, Z1 };
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    pointsVec.resize(iterations);
}
int mandelbrotSinIterationCheck(double real, double imag, int maxIterations) {
    const double C0 = real;
    const double C1 = imag;
    double Z0 = real;
    double Z1 = imag;
    Complex Z = c_sin(Complex(C0, C1));
    Z0 = Z.real;
    Z1 = Z.imag;
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
int burningShipIterationCheck(double real, double imag, int maxIterations) {
    const double C0 = real;
    const double C1 = imag;
    double Z0 = real;
    double Z1 = imag;
    double re2;
    double im2;

    int iterations = 1;
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
void burningShipOrbit(double real, double imag, int maxIterations, std::vector<numPair>& pointsVec) {
    pointsVec.clear();
    pointsVec.resize(maxIterations);
    const double C0 = real;
    const double C1 = -imag;
    double Z0 = real;
    double Z1 = -imag;
    double re2;
    double im2;

    int iterations = 1;
    do {
        Z0 = abs(Z0);
        Z1 = -abs(Z1);
        re2 = Z0 * Z0;
        im2 = Z1 * Z1;
        Z1 = 2 * Z0 * Z1 + C1;
        Z0 = re2 - im2 + C0;
        pointsVec[iterations] = { Z0, -Z1 };
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    pointsVec.resize(iterations);
}
int tricornIterationCheck(double real, double imag, int maxIterations) {
    const double C0 = real;
    const double C1 = imag;
    double Z0 = real;
    double Z1 = imag;
    double re2;
    double im2;

    int iterations = 0;
    do {
        re2 = Z0 * Z0;
        Z1 = -Z1;
        im2 = Z1 * Z1;
        Z1 = 2 * Z0 * Z1 + C1;
        Z0 = re2 - im2 + C0;
        iterations++;
    } while (iterations < maxIterations && (re2 + im2 <= 4));
    return iterations;
}


int collatzIterationCheck(double real, double imag, int maxIterations) {
    const Complex PI = 3.141592653589793238462643383279;
    const Complex PI2 = 1.57079632679489661923132169163;
    const Complex PIINV = 0.318309886183790671537767527;
    Complex Z = { real, imag };

    int iterations = 0;
    do {
        Z = Z / Complex(2) * c_pow_real(c_cos(PI2 * Z), 2) + (Complex(3) * Z + Complex(1)) / Complex(2) * c_pow_real(c_sin(PI2 * Z), 2) + PIINV * (Complex(0.5) - c_cos(PI * Z)) * c_sin(PI * Z);
        iterations++;
    } while (iterations < maxIterations && (Z.real*Z.real + Z.imag*Z.imag <= 16));
    return iterations;
}
void collatzOrbit(double real, double imag, int maxIterations, std::vector<numPair>& pointsVec) {
    pointsVec.clear();
    pointsVec.resize(maxIterations);
    const Complex PI = 3.141592653589793238462643383279;
    const Complex PI2 = 1.57079632679489661923132169163;
    const Complex PIINV = 0.318309886183790671537767527;
    Complex Z = { real, imag };

    int iterations = 0;
    do {
        Z = Z / Complex(2) * c_pow_real(c_cos(PI2 * Z), 2) + (Complex(3) * Z + Complex(1)) / Complex(2) * c_pow_real(c_sin(PI2 * Z), 2) + PIINV * (Complex(0.5) - c_cos(PI * Z)) * c_sin(PI * Z);
        pointsVec[iterations] = { Z.real, Z.imag };
        iterations++;
    } while (iterations < maxIterations && (Z.real * Z.real + Z.imag * Z.imag <= 16));
    pointsVec.resize(iterations);
}








std::vector<mandelFormula> formulasMandel = { {mandelbrotIterationCheck, mandelbrotOrbit, "mandelbrot set"}, {burningShipIterationCheck, burningShipOrbit, "burning ship"}, {mandelbrotSinIterationCheck, blankOrbitMandelFunc, "mandelbrot set, but the starting value of z is sin(z)"},  {mandelbrot3rdIterationCheck, mandelbrot3rdOrbit, "mandelbrot third power"}, {tricornIterationCheck, blankOrbitMandelFunc, "tricorn/mandelbar set"} };














std::vector<sf::Uint8> generateMandelbrotChunk(int maxIterations, unsigned long long int zoom, double xCoord, double yCoord, int minY, int maxY, int minX, int maxX, const std::function<sf::Color(int, int)>& paletteFunction, const std::function<int(double, double, int)>& iterationFunction) {
    int iterations;
    std::vector<sf::Uint8> pixels;
    pixels.resize((maxX - minX) * (maxY - minY) * 4);
    double zoomInverse = 1.0 / zoom; // multiplication by the inverse should be faster than division
    int index = 0;
    for (int y = maxY - 1; y >= minY; y--) {
        for (int x = minX; x < maxX; x++) {
            iterations = iterationFunction(xCoord + x * zoomInverse, yCoord + y * zoomInverse, maxIterations);
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








sf::Image loadMandelbrot(unsigned short threadNum, int maxIterations, unsigned long long int zoom, double xCoord, double yCoord, int width, int height, std::function<sf::Color(int, int)> paletteFunction, const std::function<int(double, double, int)>& iterationFunction) {
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

            std::vector<sf::Uint8> tempArray = generateMandelbrotChunk(maxIterations, zoom, xCoord, yCoord, startRow, endRow, minX, maxX, paletteFunction, iterationFunction);

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
        std::vector<sf::Uint8> tempArray = generateMandelbrotChunk(maxIterations, zoom, xCoord, yCoord, minY + chunkSize * threadNum, maxY, minX, maxX, paletteFunction, iterationFunction);
        pixels.insert(pixels.end(), tempArray.begin(), tempArray.end());
    }
    sf::Image image;
    image.create(width, height, pixels.data());
    return image;
}








double powNum = -12;

int CustomAnimationCheck(double real, double imag, int maxIterations) {
    const Complex C = { real, imag };
    Complex Z = { real, imag };
    //Z = c_atan(C);
    Z = c_log(C);

    int iterations = 1;
    do {
        Z = c_pow_real(Z, powNum) + C;
        iterations++;
    } while (iterations < maxIterations && (Z.real * Z.real + Z.imag * Z.imag <= 4));
    return iterations;
}

 void animation(unsigned short threads, int width, int height, bool fullscreen) {
    if (width % 2 == 1) width++;
    if (height % 2 == 1) height++;

    /*(-0.749616216181571, 0.044035657218587)
zoom: 494780232499200
iterations: 8000*/

    /*unsigned long long int zoom = std::min(width, height) / 4;
    unsigned long long int limit = 32921504606846976;
    int count = 0;
    while (zoom < limit) {
        zoom += zoom / 8;
        count++;
    }
    printf("%d\n", count);
    return;*/



    int maxIterations = 250;
    unsigned long long int zoom = std::min(width, height) / 4;
    unsigned long long int limit = 32921504606846976;
    double xCoord = -0.749616216181571;
    double yCoord = 0.044035657218587;
    int paletteNum = 0;
    int formulaNum = 0;
    int frameNum = 0;
    sf::Texture texture;
    texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], CustomAnimationCheck));
    sf::Sprite sprite(texture);
    int winWidth = width;
    int winHeight = height;
    int scaleFactor = 1;
    sf::RenderWindow window;
    if (fullscreen)
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Mandelbrot Set", sf::Style::Fullscreen);
    else {
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Mandelbrot Set");
    }
    while (window.isOpen() && zoom < limit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        }
        
        texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
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
        std::cout << fileName << '\n';
        texture.copyToImage().saveToFile(fileName);
        zoom += zoom / 8;
        maxIterations *= 1 + 1 / 79.f;
        frameNum++;
    }
}






void manualAdjustMandel(unsigned long long int& zoom, double& xCoord, double& yCoord, int& maxIterations) {
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





void gameLoop(unsigned short threads, int width, int height, bool fullscreen) {
    if (width % 2 == 1) width++;
    if (height % 2 == 1) height++;



    int maxIterations = 500;
    int maxIterationsLine = 50;
    unsigned long long int zoom = 450;
    //double xCoord = -1.99977406013629035931268075596025004757;
    //double yCoord = -0.00000000329004032147943505349697867;
    double xCoord = 0;
    double yCoord = 0;
    double xCoordLine = 0;
    double yCoordLine = 0;
    int paletteNum = 0;
    int formulaNum = 0;



    sf::Texture texture;
    texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
    sf::Sprite sprite(texture);
    std::vector<numPair> pointsVec;

    int winWidth = width;
    int winHeight = height;
    int scaleFactor = 1;
    sf::RenderWindow window;
    if (fullscreen)
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Mandelbrot Set", sf::Style::Fullscreen);
    else {
        window.create(sf::VideoMode(winWidth, winHeight), "SFML Mandelbrot Set");
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
                mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);

                xCoord = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
                yCoord = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
                texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
                sprite.setTexture(texture);
                pointsVec.clear();
            }  if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
            mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);

            xCoordLine = (mousePos.x - width / 2 + xCoord * zoom) / zoom;
            yCoordLine = ((height - 1 - mousePos.y) - height / 2 + yCoord * zoom) / zoom;
            formulasMandel[formulaNum].orbitFunc(xCoordLine, -yCoordLine, maxIterationsLine, pointsVec);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom += zoom / 15;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            zoom *= 2;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 15;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            zoom -= zoom / 2;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations += maxIterations / 5;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations *= 2;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            maxIterations -= maxIterations / 5;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            maxIterations -= maxIterations / 2;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paletteLength *= 2;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paletteLength -= paletteLength / 2;
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            paletteNum++;
            if (paletteNum == palettes.size()) {
                paletteNum = 0;
            }
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            if (paletteNum == 0) {
                paletteNum = palettes.size() - 1;
            }
            else {
                paletteNum--;
            }
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            texture.copyToImage().saveToFile("mandelbrot.png");
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            formulaNum++;
            if (formulaNum == formulasMandel.size()) {
                formulaNum = 0;
            }
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
            pointsVec.clear();
            std::cout << formulasMandel[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (formulaNum == 0) {
                formulaNum = formulasMandel.size() - 1;
            }
            else {
                formulaNum--;
            }
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
            pointsVec.clear();
            std::cout << formulasMandel[formulaNum].name << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            maxIterationsLine++;
            formulasMandel[formulaNum].orbitFunc(xCoordLine, -yCoordLine, maxIterationsLine, pointsVec);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && maxIterationsLine > 1) {
            maxIterationsLine--;
            formulasMandel[formulaNum].orbitFunc(xCoordLine, -yCoordLine, maxIterationsLine, pointsVec);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            manualAdjustMandel(zoom, xCoord, yCoord, maxIterations);
            texture.loadFromImage(loadMandelbrot(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum], formulasMandel[formulaNum].func));
            sprite.setTexture(texture);
        }

        sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));


        // Clear the window
        window.clear();
        sprite.setScale(scaleFactor, scaleFactor);

        // Draw the sprite
        window.draw(sprite);

        drawPoints(zoom, xCoord, yCoord, width, height, pointsVec, window);

        // Display the window
        window.display();
    }
}
