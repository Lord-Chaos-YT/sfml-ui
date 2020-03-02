#define SFML_STATIC

#ifndef TEST_HPP
#define TEST_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <cstdlib>
#include <string>

//using namespace std;

namespace UI {
    sf::Vector2f center(const sf::Vector2f& size, const sf::Vector2f& pos = {0.f, 0.f}) {
        return {pos.x - (size.x / 2.f), pos.y - (size.y / 2.f)};
    }

    bool isWithinBounds(const sf::Vector2f& pos, const sf::FloatRect& bounds) {
        return bounds.contains(pos);
        //return (pos.x > bounds.left && pos.x < bounds.left + bounds.width && pos.y > bounds.top && pos.y < bounds.top + bounds.height);
    }

    sf::Vector2f centerStrInBounds(const sf::Vector2f& textSize, const sf::Vector2f& bgSize, const sf::Vector2f& pos = {0, 0}) {
        return center(textSize, {pos.x + (bgSize.x / 2.f), (pos.y + (bgSize.y / 2.f)) - (textSize.y / 8.f)});
    }
};

#endif