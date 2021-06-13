#define SFML_STATIC

#ifndef UI_ELEMENTS_HPP
#define UI_ELEMENTS_HPP

#include <SFML/Graphics.hpp>
#include "concrete.hpp"
#include "methods.hpp"
#include <iostream>
#include <string>

//using namespace std;

namespace UI {
    template<class BackgroundType = sf::RectangleShape> class Element : public Concrete {
    protected:
        BackgroundType background;
        sf::Vector2f sizeDefault;

        void recomputePos();
        void recomputeSizes();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
        }
    public:
        Element(
            const sf::Vector2f& initSize = {-1.f, -1.f},
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Color& bgColor = sWhite
        );

        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2f& size);
        void setFillColor(const sf::Color& color);

        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        sf::Color getFillColor() const;
    };

    template<class BackgroundType> Element<BackgroundType>::Element(
        const sf::Vector2f& initSize,
        const sf::Vector2f& pos,
        const sf::Color& bgColor
    ) : sizeDefault{initSize} {
        if (!std::is_base_of<sf::RectangleShape, BackgroundType>::value) throw "Invalid type specifier. Type must inherit from class sf::RectangleShape!";

        background.setPosition(pos);
        background.setSize(sizeDefault);
        background.setFillColor(bgColor);

        this->recomputeSizes();
    }

    template<class BackgroundType> void Element<BackgroundType>::recomputePos() {
    }

    template<class BackgroundType> void Element<BackgroundType>::recomputeSizes() {
        background.setSize(sizeDefault);
        this->recomputePos();
    }

    template<class BackgroundType> void Element<BackgroundType>::setPosition(const sf::Vector2f& pos) {
        background.setPosition(pos);
        this->recomputePos();
    }

    template<class BackgroundType> void Element<BackgroundType>::setPosition(float x, float y) {
        background.setPosition(x, y);
        this->recomputePos();
    }

    template<class BackgroundType> void Element<BackgroundType>::setSize(const sf::Vector2f& size) {
        sizeDefault = size;
        this->recomputeSizes();
    }

    template<class BackgroundType> void Element<BackgroundType>::setFillColor(const sf::Color& color) {background.setFillColor(color);}

    template<class BackgroundType> sf::Vector2f Element<BackgroundType>::getPosition() const {return background.getPosition();}
    template<class BackgroundType> sf::Vector2f Element<BackgroundType>::getSize() const {return background.getSize();}
    template<class BackgroundType> sf::Color Element<BackgroundType>::getFillColor() const {return background.getFillColor();}
};

#endif