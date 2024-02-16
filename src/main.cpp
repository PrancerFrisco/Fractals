#include <iostream>
#include <SFML\Graphics.hpp>
#include "Mandelbrot.hpp"
#include "MandelbrotGMP.hpp"
#include "Newton.hpp"
#include "Julia.hpp"











int main() {


    std::cout << "refer to How-To-Use.txt for controls\n\n\n";

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

    std::cout << "\n1 - Mandelbrot Set\n2 - Julia Sets\n3 - Mandelbrot Set (unlimited precision, but extemely slow)\n4 - Newton Fractal\n5 - Newton Fractal (Julia)\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        gameLoop(threads, width, height, fullscreen);
        break;
    case 2:
        gameLoopJulia(threads, width, height, fullscreen);
        break;
    case 3:
        gameLoopGMP(threads);
        break;
    case 4:
        gameLoopNewton(threads, width, height, fullscreen);
        break;
    case 5:
        gameLoopNewtonJulia(threads, width, height, fullscreen);
        break;
    default:
        break;
    }
    return 0;
}
