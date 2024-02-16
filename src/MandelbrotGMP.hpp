#pragma once
#include <iostream>
#include "global.hpp"
#include <functional>
#include <vector>
#include <SFML\Graphics.hpp>
#include <gmpxx.h>



int mandelbrotIterationCheckGMP(mpf_t& real, mpf_t& imag, int maxIterations) {
    mpf_t C0, Z0, C1, Z1, re2, im2;
    mpf_init(C0);
    mpf_init(Z0);
    mpf_init(C1);
    mpf_init(Z1);
    mpf_init(re2);
    mpf_init(im2);


    mpf_set(C0, real);
    mpf_set(Z0, real);
    mpf_set(C1, imag);
    mpf_set(Z1, imag);

    int iterations = 0;
    do {
        mpf_mul(re2, Z0, Z0);
        mpf_mul(im2, Z1, Z1);


        // Z1 = 2 * Z0 * Z1 + C1;
        mpf_mul(Z1, Z0, Z1);
        mpf_mul_ui(Z1, Z1, 2);
        mpf_add(Z1, Z1, C1);

        // Z0 = re2 - im2 + C0;
        mpf_sub(Z0, re2, im2);
        mpf_add(Z0, Z0, C0);

        mpf_add(re2, re2, im2);
        iterations++;
    } while (iterations < maxIterations && (mpf_cmp_ui(re2, 4) <= 0));
    mpf_clear(C0);
    mpf_clear(Z0);
    mpf_clear(C1);
    mpf_clear(Z1);
    mpf_clear(re2);
    mpf_clear(im2);
    return iterations;
}



std::vector<sf::Uint8> generateMandelbrotChunkGMP(int maxIterations, mpf_t& zoom, mpf_t& xOffset, mpf_t& yOffset, int minY, int maxY, int height, int minX, int maxX, int width, std::function<sf::Color(int, int)> paletteFunction) {
    int iterations;
    std::vector<sf::Uint8> pixels;
    pixels.resize((maxX - minX) * (maxY - minY) * 4);
    mpf_t real, imag, tempXY;
    mpf_init(real);
    mpf_init(imag);
    mpf_init(tempXY);
    int index = 0;
    for (int y = maxY - 1; y >= minY; y--) {
        for (int x = minX; x < maxX; x++) {
            mpf_set_si(tempXY, x);
            mpf_add(real, xOffset, tempXY);
            mpf_div(real, real, zoom);

            mpf_set_si(tempXY, y);
            mpf_add(imag, yOffset, tempXY);
            mpf_div(imag, imag, zoom);


            iterations = mandelbrotIterationCheckGMP(real, imag, maxIterations);

            sf::Color colour = paletteFunction(iterations, maxIterations);

            sf::Uint8* pixelPtr = &pixels[index];
            pixelPtr[0] = colour.r;
            pixelPtr[1] = colour.g;
            pixelPtr[2] = colour.b;
            pixelPtr[3] = 255;

            index += 4;
        }
    }
    mpf_clear(real);
    mpf_clear(imag);
    mpf_clear(tempXY);
    return pixels;
}

sf::Image loadMandelbrotGMP(unsigned short threadNum, int maxIterations, mpf_t& zoom, mpf_t& xCoord, mpf_t& yCoord, int width, int height, std::function<sf::Color(int, int)> paletteFunction) {
    int iterations;
    int minX = -width / 2;
    int maxX = -minX;
    int minY = -height / 2;
    int maxY = -minY;

    mpf_t xOffset, yOffset, real, imag;
    mpf_init(xOffset);
    mpf_init(yOffset);
    mpf_init(real);
    mpf_init(imag);
    mpf_mul(xOffset, xCoord, zoom);
    mpf_mul(yOffset, yCoord, zoom);


    int chunkSize = height / threadNum;
    std::vector<std::vector<sf::Uint8>> arrays;
    arrays.resize(threadNum);

    std::vector<std::thread> threads;
    for (int i = 0; i < threadNum; i++) {
        threads.emplace_back([&, i]() {
            int startRow = minY + i * (maxY - minY) / threadNum;
            int endRow = minY + (i + 1) * (maxY - minY) / threadNum;

            std::vector<sf::Uint8> tempArray = generateMandelbrotChunkGMP(maxIterations, zoom, xOffset, yOffset, startRow, endRow, height, minX, maxX, width, paletteFunction);

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
        std::vector<sf::Uint8> tempArray = generateMandelbrotChunkGMP(maxIterations, zoom, xOffset, yOffset, minY + chunkSize * threadNum, maxY, height, minX, maxX, width, paletteFunction);
        pixels.insert(pixels.end(), tempArray.begin(), tempArray.end());
    }
    sf::Image image;
    image.create(width, height, pixels.data());
    return image;
    mpf_clear(xOffset);
    mpf_clear(yOffset);
    mpf_clear(real);
    mpf_clear(imag);

    return image;
}



void manualAdjustMandelGMP(mpz_t& zoom, mpz_t& xCoord, mpz_t& yCoord, int& maxIterations) {
    gmp_printf("coordinates : %.*Ff, %.*Ff \n\n\n\n", 500, xCoord, 500, yCoord);
    gmp_printf("zoom: %Ff\n", zoom);
    std::cout << "iterations: " << maxIterations << '\n';
    printf("iterations: %d\n", maxIterations);

    std::string userInput;
    std::cout << "\n";
    std::getline(std::cin, userInput);

    std::cout << "enter a new value of x: ";
    std::getline(std::cin, userInput);
    mpz_set_str(xCoord, userInput.c_str(), 10);
    gmp_printf("x coord: %.*Ff\n", 500, xCoord);

    std::cout << "enter a new value of y: ";
    std::getline(std::cin, userInput);
    mpz_set_str(yCoord, userInput.c_str(), 10);
    gmp_printf("y coord: %.*Ff\n", 500, yCoord);


    std::cout << "enter a new value for zoom: ";
    std::getline(std::cin, userInput);
    mpz_set_str(zoom, userInput.c_str(), 10);
    gmp_printf("zoom: %.*Ff\n", zoom);

    std::cout << "enter a new value for iterations: ";
    std::getline(std::cin, userInput);
    std::istringstream issIters(userInput);
    if (issIters >> maxIterations) printf("iterations: %d\n", maxIterations);
}









void gameLoopGMP(const unsigned short& threads) {
    int prec;
    std::cout << "enter precision (in bits) for the calculations: ";
    std::cin >> prec;
    mpf_set_default_prec(prec);
    bool answer;
    std::cout << "use default resolution (1/0): ";
    std::cin >> answer;
    int width = 100;
    int height = 100;
    if (!answer) {
        std::cout << "enter width: ";
        std::cin >> width;
        std::cout << "enter height: ";
        std::cin >> height;
    }


    paletteLength = 10;

    int maxIterations = 50000;
    int paletteNum = 0;
    mpf_t zoom, xCoord, yCoord;
    mpf_init(zoom);
    mpf_init(xCoord);
    mpf_init(yCoord);
    mpf_set_str(zoom, "1000", 10);
    /*mpf_set_str(zoom, "1000", 10);
    mpf_set_str(xCoord, "-0.04185809511832129648121425363767380159259", 10);
    mpf_set_str(yCoord, "0.9833883421416195186612488600506905099094", 10);*/
    //mpf_set_str(zoom, "7555121520734093065255179271209531843903208054538697400108902813868330342441959932304295717190508354569072644421815841350040207348462280000077844971520000000000000000000000000000", 10);
    mpf_set_str(xCoord, "-0.17263992420071190839818276390118149888924116243793517214666468601289684626808058290986780909925050862848288936555930266238194627196573720398609693598174510151011765125761313709202862235250293208", 10);
    mpf_set_str(yCoord, "1.0503649263079115536875706751697729765122260848906042038823035989160783016088259124444158505604537988825409508523765645807473164922165294879885406987440228255090273741752602965889639630296075951", 10);
    //maxIterations = 80000;


    mpf_t temp;



    sf::Texture texture;
    texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
    sf::Sprite sprite(texture);

    int winWidth = 1000;
    int winHeight = 1000;
    float scaleX = winWidth / width;
    float scaleY = winHeight / height;
    float scaleFactor = std::min(scaleX, scaleY);
    int normalisedMouseX, normalisedMouseY;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "SFML Mandelbrot Set GMP");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                gmp_printf("zoom: %Ff\n", zoom);
                mousePos.x = normaliseINT(mousePos.x, 0, winWidth, 0, width);
                mousePos.y = normaliseINT(mousePos.y, 0, winHeight, 0, height);
                mpf_init(temp);
                mpf_set_si(temp, (mousePos.x - width / 2));
                mpf_div(temp, temp, zoom);
                mpf_add(xCoord, xCoord, temp);


                mpf_set_si(temp, ((height - 1 - mousePos.y) - height / 2));
                mpf_div(temp, temp, zoom);
                mpf_add(yCoord, yCoord, temp);
                
                texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
                sprite.setTexture(texture);



                gmp_printf("coordinates : %.*Ff, %.*Ff \n\n\n\n", 500, xCoord, 500, yCoord);
                mpf_clear(temp);

            }
            if (event.type == sf::Event::Resized) {
                winWidth = window.getSize().x;
                winHeight = window.getSize().y;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            mpf_init(temp);
            mpf_div_ui(temp, zoom, 15);
            mpf_add(zoom, zoom, temp);
            mpf_clear(temp);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            mpf_mul_ui(zoom, zoom, 2);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            mpf_mul_ui(zoom, zoom, 6);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            mpf_init(temp);
            mpf_div_ui(temp, zoom, 15);
            mpf_sub(zoom, zoom, temp);
            mpf_clear(temp);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            mpf_div_ui(zoom, zoom, 2);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            maxIterations += maxIterations / 6;
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            maxIterations *= 2;
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && maxIterations >= 10) {
            maxIterations -= maxIterations / 6;
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && maxIterations >= 2) {
            maxIterations /= 2;
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paletteLength *= 2;
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paletteLength >= 2) {
            paletteLength /= 2;
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            paletteNum++;
            if (paletteNum == palettes.size()) {
                paletteNum = 0;
            }
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            if (paletteNum == 0) {
                paletteNum = palettes.size() - 1;
            }
            else {
                paletteNum--;
            }
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
            width += width / 5;
            height += height / 5;
            if (width > winWidth) width = winWidth;
            if (height > winHeight) height = winHeight;
            if (width % 2 == 1) width++;
            if (height % 2 == 1) height++;
            scaleX = (float)winWidth / (float)width;
            scaleY = (float)winHeight / (float)height;
            scaleFactor = std::min(scaleX, scaleY);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));

            std::cout << width << ' ' << height << ' ' << winWidth << ' ' << winHeight << '\n';
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && width > 5) {
            width -= width / 5;
            height -= height / 5;
            if (width % 2 == 1) width++;
            if (height % 2 == 1) height++;
            scaleX = (float)winWidth / (float)width;
            scaleY = (float)winHeight / (float)height;
            scaleFactor = std::min(scaleX, scaleY);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
        }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            texture.copyToImage().saveToFile("mandelbrotGMP.png");
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            prec += 100;
            mpf_set_default_prec(prec);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && prec > 100) {
            prec -= 100;
            mpf_set_default_prec(prec);
            texture.loadFromImage(loadMandelbrotGMP(threads, maxIterations, zoom, xCoord, yCoord, width, height, palettes[paletteNum]));
            sprite.setTexture(texture);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }



        window.clear();
        sprite.setScale(scaleFactor, scaleFactor);

        window.draw(sprite);

        window.display();
    }
}
