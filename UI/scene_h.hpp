#define SFML_STATIC

#ifndef SCENE_H_HPP
#define SCENE_H_HPP

#include <SFML/Graphics.hpp>
#include "forward_decls.hpp"
#include <map>
#include <functional>
#include <iostream>
#include <string>

//using namespace std;

namespace UI {
    class Scene : public sf::Drawable {
    public:
        std::function<void(Scene* scene)> onSceneSwitchTo, onSceneSwitchAway, onTick;
        std::vector<Focus*> focusable;
        std::vector<Hold*> holdable;
        std::vector<Hover*> hoverable;
        std::vector<sf::Drawable*> drawable;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            for (auto val : drawable) target.draw(*val, states);
        }
    public:
        Scene(
            std::vector<Focus*> focusVect = {},
            std::vector<Hold*> holdVect = {},
            std::vector<Hover*> hoverVect = {},
            std::vector<sf::Drawable*> drawVect = {}
        );

        void setSwitchToAction(std::function<void(Scene* scene)> fnc);
        void setSwitchAwayAction(std::function<void(Scene* scene)> fnc);
        void setTickAction(std::function<void(Scene* scene)> fnc);

        void switchTo();
        void switchAway();
        void tick();

        Concrete* addElem(const std::string& name, Concrete* elem);
        sf::Drawable* addElem(const std::string& name, sf::Drawable* elem);
    };
};

#endif