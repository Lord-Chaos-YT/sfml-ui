#define SFML_STATIC

#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include "concrete_h.hpp"
#include "scene_h.hpp"
#include <functional>
#include <iostream>
#include <cstdlib>

//using namespace std;

namespace UI {
    Scene::Scene(
        std::map<std::string, Focus*> focusVect,
        std::map<std::string, Hold*> holdVect,
        std::map<std::string, Hover*> hoverVect,
        std::map<std::string, sf::Drawable*> drawVect
    ) {
        focusable = focusVect;
        holdable = holdVect;
        hoverable = hoverVect;
        drawable = drawVect;
    }

    void Scene::setSwitchToAction(std::function<void(Scene* scene)> fnc) {onSceneSwitchTo = fnc;}
    void Scene::setSwitchAwayAction(std::function<void(Scene* scene)> fnc) {onSceneSwitchAway = fnc;}
    void Scene::setTickAction(std::function<void(Scene* scene)> fnc) {onTick = fnc;}

    void Scene::switchTo() {if ((bool)onSceneSwitchTo) onSceneSwitchTo(this);}
    void Scene::switchAway() {if ((bool)onSceneSwitchAway) onSceneSwitchAway(this);}
    void Scene::tick() {if ((bool)onTick) onTick(this);}

    Concrete* Scene::addElem(const std::string& name, Concrete* elem) {
        elem->addScene(name, this);
        return elem;
    }

    sf::Drawable* Scene::addElem(const std::string& name, sf::Drawable* elem) {
        this->drawable.insert({name, elem});
        return elem;
    }
};

#endif