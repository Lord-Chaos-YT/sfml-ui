/**
 * Compile with:
 * g++ -o test0.exe test0.cpp -Isfml/include -Lsfml/lib "-Wl,--start-group" -lfreetype -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-main -lgdi32 -lopengl32 -lwinmm "-Wl,--end-group"
 */

#define SFML_STATIC


#ifndef MAIN_HPP
#define MAIN_HPP


#include <SFML/Graphics.hpp>
#include "UI/scrollwindow.hpp"
#include "UI/constants.hpp"
#include "UI/concrete.hpp"
#include "UI/elements.hpp"
#include "UI/methods.hpp"
#include "UI/textbox.hpp"
#include "UI/button.hpp"
#include "UI/scroll.hpp"
#include "UI/scene.hpp"
#include "UI/pop.hpp"
#include <functional>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <regex>

using namespace std;

int init(int argCount, char* args[],
function<void(sf::RenderWindow& window, sf::Font& font, sf::Cursor& normalCursor, sf::Cursor& textBoxCursor, sf::Clock& clock, UI::Focus* focus, UI::Hold* hold, UI::Hover* hover, UI::Scene* currentScene)> initFnc
) {
    // Only show console if the argument "console" is used
    if (argCount > 1 && (string)args[1] == "console");
    else ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

    // Main window & font declarations
    sf::RenderWindow window(sf::VideoMode(UI::winW, UI::winH), "Game Test", sf::Style::Default);
    sf::Font font;
    if (!font.loadFromFile("./fonts/cour.ttf")) throw "Couldn't find font";

    // Cursor alternatives declarations
    sf::Cursor normalCursor, textBoxCursor;
    normalCursor.loadFromSystem(sf::Cursor::Arrow);
    textBoxCursor.loadFromSystem(sf::Cursor::Text);

    // Runtime data
    sf::Clock clock;
    UI::Focus* focus = nullptr;
    UI::Hold* hold = nullptr;
    UI::Hover* hover = nullptr;
    UI::Scene* currentScene = nullptr;

    initFnc(window, font, normalCursor, textBoxCursor, clock, focus, hold, hover, currentScene);

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            /**
             * Event loop, handles user actions and motions.
             */
            sf::Vector2i tempMousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = {(float)tempMousePos.x, (float)tempMousePos.y};
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (focus != nullptr) {
                    if (!focus->isMouseOver(mousePos)) {
                        focus->endFocus();
                        focus = nullptr;
                    } else {
                        focus->startFocus(clock.getElapsedTime());
                        focus->click();
                    }
                }

                for (auto val : currentScene->focusable) if (val.second->isMouseOver(mousePos)) {
                    focus = val.second;
                    break;
                }
                for (auto val : currentScene->holdable) if (val.second->isMouseOver(mousePos)) {
                    hold = val.second;
                    break;
                }
                for (auto val : currentScene->hoverable) if (val.second->isMouseOver(mousePos)) {
                    val.second->click();
                }

                if (hold != nullptr) hold->startHold(mousePos), hold->click();
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (hold != nullptr) {
                    hold->unClick();
                    hold->endHold();
                    hold = nullptr;
                }
                if (hover != nullptr) {
                    hover->unClick();
                    if (hover->isMouseOver(mousePos)) hover->hover();
                }
                if (focus != nullptr) focus->unClick();
            } else if (event.type == sf::Event::MouseMoved) {
                for (auto val : currentScene->hoverable) {
                    if (val.second->isMouseOver(mousePos) && hover != val.second) {
                        if (hover != nullptr) hover->unHover();
                        hover = val.second;
                        break;
                    }
                }
                if (hold != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left)) hold->updateHold(mousePos);
                if (hover != nullptr) {
                    if (hover->isMouseOver(mousePos)) hover->hover();
                    else {
                        hover->unHover();
                        hover = nullptr;
                    }
                }
            } else if (event.type == sf::Event::KeyReleased) {
                if (focus != nullptr) focus->registerKeystroke(
                    event.key.code,
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)
                );
            } else if (event.type == sf::Event::Resized) {
                window.setSize({event.size.width, event.size.height});
            }
        }
        sf::Time time = clock.getElapsedTime();
        if (focus != nullptr) focus->focusTick(time);

        /**
         * Draw the current scene.
         */
        window.clear();
        if (currentScene != nullptr) window.draw(*currentScene);
        window.display();
    }
    FreeConsole();
    return 0;
}

#endif