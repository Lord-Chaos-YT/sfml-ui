#define SFML_STATIC

#ifndef FOCUSABLE_HPP
#define FOCUSABLE_HPP

#include <SFML/Graphics.hpp>
#include "concrete_h.hpp"
#include "scene_h.hpp"
#include <functional>

//using namespace std;

namespace UI {
    void Concrete::addScene(Scene* scene) {(scene->drawable).push_back(this);}

    void Hover::addScene(Scene* scene) {
        (scene->drawable).push_back(this);
        (scene->hoverable).push_back(this);
    }

    bool Hover::isMouseOver(const sf::Vector2f& mousePos) {
        sf::Vector2f pos = this->getPosition(), size = this->getSize();
        return (sf::FloatRect{pos.x, pos.y, size.x, size.y}).contains(mousePos);
    }

    void Focus::addScene(Scene* scene) {
        (scene->drawable).push_back(this);
        (scene->hoverable).push_back(this);
        (scene->focusable).push_back(this);
    }

    void Hold::addScene(Scene* scene) {
        (scene->drawable).push_back(this);
        (scene->hoverable).push_back(this);
        (scene->holdable).push_back(this);
    }
};

#endif