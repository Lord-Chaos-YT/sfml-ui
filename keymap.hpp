#define SFML_STATIC

#ifndef KEYMAPS_HPP
#define KEYMAPS_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

//using namespace std;

namespace UI {
    class Key {
    public:
        char lower, upper;
        Key(char l, char u) {lower = l, upper = u;}
    };

    const std::unordered_map<sf::Keyboard::Key, Key> sfKeyToChar = {
        {sf::Keyboard::A, {'a', 'A'}},
        {sf::Keyboard::B, {'b', 'B'}},
        {sf::Keyboard::C, {'c', 'C'}},
        {sf::Keyboard::D, {'d', 'D'}},
        {sf::Keyboard::E, {'e', 'E'}},
        {sf::Keyboard::F, {'f', 'F'}},
        {sf::Keyboard::G, {'g', 'G'}},
        {sf::Keyboard::H, {'h', 'H'}},
        {sf::Keyboard::I, {'i', 'I'}},
        {sf::Keyboard::J, {'j', 'J'}},
        {sf::Keyboard::K, {'k', 'K'}},
        {sf::Keyboard::L, {'l', 'L'}},
        {sf::Keyboard::M, {'m', 'M'}},
        {sf::Keyboard::N, {'n', 'N'}},
        {sf::Keyboard::O, {'o', 'O'}},
        {sf::Keyboard::P, {'p', 'P'}},
        {sf::Keyboard::Q, {'q', 'Q'}},
        {sf::Keyboard::R, {'r', 'R'}},
        {sf::Keyboard::S, {'s', 'S'}},
        {sf::Keyboard::T, {'t', 'T'}},
        {sf::Keyboard::U, {'u', 'U'}},
        {sf::Keyboard::V, {'v', 'V'}},
        {sf::Keyboard::W, {'w', 'W'}},
        {sf::Keyboard::X, {'x', 'X'}},
        {sf::Keyboard::Y, {'y', 'Y'}},
        {sf::Keyboard::Z, {'z', 'Z'}},
        {sf::Keyboard::Num0, {'0', ')'}},
        {sf::Keyboard::Num1, {'1', '!'}},
        {sf::Keyboard::Num2, {'2', '@'}},
        {sf::Keyboard::Num3, {'3', '#'}},
        {sf::Keyboard::Num4, {'4', '$'}},
        {sf::Keyboard::Num5, {'5', '%'}},
        {sf::Keyboard::Num6, {'6', '^'}},
        {sf::Keyboard::Num7, {'7', '&'}},
        {sf::Keyboard::Num8, {'8', '*'}},
        {sf::Keyboard::Num9, {'9', '('}},
        {sf::Keyboard::Tilde, {'`', '~'}},
        {sf::Keyboard::Dash, {'-', '_'}},
        {sf::Keyboard::Equal, {'=', '+'}},
        {sf::Keyboard::LBracket, {'[', '{'}},
        {sf::Keyboard::RBracket, {']', '}'}},
        {sf::Keyboard::Backslash, {'\\', '|'}},
        {sf::Keyboard::Semicolon, {';', ':'}},
        {sf::Keyboard::Quote, {'\'', '"'}},
        {sf::Keyboard::Comma, {',', '<'}},
        {sf::Keyboard::Period, {'.', '>'}},
        {sf::Keyboard::Slash, {'/', '?'}},
        {sf::Keyboard::Space, {' ', ' '}}
    };
};

#endif