#define SFML_STATIC

#ifndef FOCUSABLE_HPP
#define FOCUSABLE_HPP

#include <SFML/Graphics.hpp>
#include "concrete_h.hpp"
#include "scene_h.hpp"
#include <functional>

//using namespace std;

namespace UI {
    void Concrete::addScene(const std::string& name, Scene* scene) {(scene->drawable).insert({name, this});}

    void Hover::addScene(const std::string& name, Scene* scene) {
        (scene->drawable).insert({name, this});
        (scene->hoverable).insert({name, this});
    }

    bool Hover::isMouseOver(const sf::Vector2f& mousePos) {
        sf::Vector2f pos = this->getPosition(), size = this->getSize();
        return (sf::FloatRect{pos.x, pos.y, size.x, size.y}).contains(mousePos);
    }

    void Focus::addScene(const std::string& name, Scene* scene) {
        (scene->drawable).insert({name, this});
        (scene->hoverable).insert({name, this});
        (scene->focusable).insert({name, this});
    }

    void Hold::addScene(const std::string& name, Scene* scene) {
        (scene->drawable).insert({name, this});
        (scene->hoverable).insert({name, this});
        (scene->holdable).insert({name, this});
    }
};

#endif