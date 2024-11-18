#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ControllerSetup.h"

// Constants for overlay window dimensions
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 500;



int main() {
    // ID of the first controller connected
    unsigned int joystickID = 0;

    controllerCheck();

    std::cout << "Configuring controller. Please press the specified buttons when prompted." << std::endl;
    ControllerMapping mapping = configureController(joystickID);  // Configure controller mappings for joystick ID 0

    sf::RenderWindow overlayWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Controller Overlay");
    RenderOverlay(overlayWindow, joystickID, mapping);  // Render the overlay using the mapped buttons

    return 0;
}
