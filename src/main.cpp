#include <iostream>
#include <SFML\Graphics.hpp>
#include "Mandelbrot.hpp"
#include "MandelbrotGMP.hpp"
#include "Julia.hpp"





std::string controls() {
    return " rightclick - change julia set\n leftclick - centre screen on mouse position (you can press any mouse button to do this for the mandelbrot set)\n i - zoom in\n o - zoom out\n s - save image (overwrites old image)\n up - increase iterations\n down - decrease iterations\n left - decrease palette length (only compatible with one palette)\n right - increase palette length (only compatible with one palette)\n plus/minus - change palette\n\nresizing the window will NOT change that amount of pixels rendered\n\n\n\n";
}





int main() {


    std::cout << controls();

    int threads;

    std::cout << "how many threads to use: ";
    std::cin >> threads;
    bool answer;
    std::cout << "use default resolution (1/0): ";
    std::cin >> answer;
    int width, height;
    bool fullscreen = false;
    if (answer) {
        width = sf::VideoMode::getDesktopMode().width;
        height = sf::VideoMode::getDesktopMode().height;
        fullscreen = true;
    }
    else {
        std::cout << "enter width: ";
        std::cin >> width;
        std::cout << "enter height: ";
        std::cin >> height;
    }
    gameLoop(threads, width, height, fullscreen);
    gameLoopJulia(threads, width, height, fullscreen);
    gameLoopGMP(threads);

    HSV thing(100, 50, 230);
    sf::Color t = thing.toRGB();
    std::cout << (int)t.r << ' ' << (int)t.g << ' ' << (int)t.b;


    return 0;
}