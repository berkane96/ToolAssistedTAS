#ifndef CONTROLLERSETUP_H
#define CONTROLLERSETUP_H\

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>

// Struct to hold the mapping for each button
struct ControllerMapping {
    int aButton;
    int bButton;
    int xButton;
    int yButton;
    int lShoulder;
    int rShoulder;
    int startButton;
    int selectButton;

    // D-pad axes
    sf::Joystick::Axis dpadXAxis;
    sf::Joystick::Axis dpadYAxis;
    float dpadThreshold;  // Threshold for detecting D-pad direction
};


bool promptForButton(const std::string& buttonName, int& buttonIndex, unsigned int joystickID);

// Function to map the controller and D-pad
ControllerMapping configureController(unsigned int joystickID);

void RenderOverlay(sf::RenderWindow& overlayWindow, unsigned int joystickID, const ControllerMapping& mapping);

void controllerCheck();


#endif