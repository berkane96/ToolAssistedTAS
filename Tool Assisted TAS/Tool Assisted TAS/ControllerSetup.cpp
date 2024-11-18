#include "ControllerSetup.h"


bool promptForButton(const std::string& buttonName, int& buttonIndex, unsigned int joystickID) {
    std::cout << "Press the " << buttonName << " button on your controller..." << std::endl;
    bool buttonPressed = false;

    while (true) {
        sf::Joystick::update();  // Refresh joystick state
        for (unsigned int i = 0; i < sf::Joystick::getButtonCount(joystickID); ++i) {
            if (sf::Joystick::isButtonPressed(joystickID, i)) {
                if (!buttonPressed) {  // Check if this is the first time the button is pressed
                    buttonIndex = i;
                    buttonPressed = true;
                    std::cout << buttonName << " mapped to button index " << i << std::endl;
                }
            }
        }
        if (buttonPressed) {
            bool allReleased = true;
            for (unsigned int i = 0; i < sf::Joystick::getButtonCount(joystickID); ++i) {
                if (sf::Joystick::isButtonPressed(joystickID, i)) {
                    allReleased = false;
                    break;
                }
            }
            if (allReleased) {
                sf::sleep(sf::milliseconds(200));  // Short delay to debounce
                break;
            }
        }
        sf::sleep(sf::milliseconds(50));
    }
    return true;
}

// Function to map the controller and D-pad
ControllerMapping configureController(unsigned int joystickID) {
    ControllerMapping mapping;
    promptForButton("A", mapping.aButton, joystickID);
    promptForButton("B", mapping.bButton, joystickID);
    promptForButton("X", mapping.xButton, joystickID);
    promptForButton("Y", mapping.yButton, joystickID);
    promptForButton("L Shoulder", mapping.lShoulder, joystickID);
    promptForButton("R Shoulder", mapping.rShoulder, joystickID);
    promptForButton("Start", mapping.startButton, joystickID);
    promptForButton("Select", mapping.selectButton, joystickID);

    // Set D-pad axes
    mapping.dpadXAxis = sf::Joystick::X;  // Typically Axis 0 for horizontal D-pad
    mapping.dpadYAxis = sf::Joystick::Y;  // Typically Axis 1 for vertical D-pad
    mapping.dpadThreshold = 50.0f;        // Adjust sensitivity as needed

    std::cout << "Controller mapping complete!" << std::endl;
    return mapping;
}

void RenderOverlay(sf::RenderWindow& overlayWindow, unsigned int joystickID, const ControllerMapping& mapping) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font!" << std::endl;
        return;
    }

    while (overlayWindow.isOpen()) {
        sf::Event event;
        while (overlayWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                overlayWindow.close();
            }
        }

        overlayWindow.clear(sf::Color(50, 50, 50));

        // Check each button using the mapped indices
        bool isAPressed = sf::Joystick::isButtonPressed(joystickID, mapping.aButton);
        bool isBPressed = sf::Joystick::isButtonPressed(joystickID, mapping.bButton);
        bool isXPressed = sf::Joystick::isButtonPressed(joystickID, mapping.xButton);
        bool isYPressed = sf::Joystick::isButtonPressed(joystickID, mapping.yButton);
        bool isLPressed = sf::Joystick::isButtonPressed(joystickID, mapping.lShoulder);
        bool isRPressed = sf::Joystick::isButtonPressed(joystickID, mapping.rShoulder);
        bool isStartPressed = sf::Joystick::isButtonPressed(joystickID, mapping.startButton);
        bool isSelectPressed = sf::Joystick::isButtonPressed(joystickID, mapping.selectButton);

        // D-pad checks using mapped axes
        float dpadX = sf::Joystick::getAxisPosition(joystickID, mapping.dpadXAxis);
        float dpadY = sf::Joystick::getAxisPosition(joystickID, mapping.dpadYAxis);
        bool isDpadLeft = (dpadX < -mapping.dpadThreshold);
        bool isDpadRight = (dpadX > mapping.dpadThreshold);
        bool isDpadUp = (dpadY < -mapping.dpadThreshold);
        bool isDpadDown = (dpadY > mapping.dpadThreshold);

        sf::Text buttonTexts[12];
        std::string labels[] = {
            "A Button: " + std::string(isAPressed ? "Pressed" : "Released"),
            "B Button: " + std::string(isBPressed ? "Pressed" : "Released"),
            "X Button: " + std::string(isXPressed ? "Pressed" : "Released"),
            "Y Button: " + std::string(isYPressed ? "Pressed" : "Released"),
            "L Shoulder: " + std::string(isLPressed ? "Pressed" : "Released"),
            "R Shoulder: " + std::string(isRPressed ? "Pressed" : "Released"),
            "Start: " + std::string(isStartPressed ? "Pressed" : "Released"),
            "Select: " + std::string(isSelectPressed ? "Pressed" : "Released"),
            "D-Pad Left: " + std::string(isDpadLeft ? "Pressed" : "Released"),
            "D-Pad Right: " + std::string(isDpadRight ? "Pressed" : "Released"),
            "D-Pad Up: " + std::string(isDpadUp ? "Pressed" : "Released"),
            "D-Pad Down: " + std::string(isDpadDown ? "Pressed" : "Released")
        };

        for (int i = 0; i < 12; i++) {
            buttonTexts[i].setFont(font);
            buttonTexts[i].setString(labels[i]);
            buttonTexts[i].setCharacterSize(20);
            buttonTexts[i].setFillColor(sf::Color::White);
            buttonTexts[i].setPosition(20, 20 + i * 40);
            overlayWindow.draw(buttonTexts[i]);
        }

        overlayWindow.display();
        sf::sleep(sf::milliseconds(16));
    }
}

void controllerCheck() {
    // Poll for joystick connection status in a loop
    bool joystickConnected = false;

    while (!joystickConnected) {
        for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
            if (sf::Joystick::isConnected(i)) {
                std::cout << "Controller " << i << " is connected." << std::endl;
                joystickConnected = true;
                break;
            }
        }

        if (!joystickConnected) {
            std::cout << "No controller detected. Please connect a controller..." << std::endl;
        }

        sf::sleep(sf::seconds(1)); // Wait for 1 second before checking again
        sf::Joystick::update(); // Update joystick status
    }

    std::cout << "Starting the button mapping..." << std::endl;

}
