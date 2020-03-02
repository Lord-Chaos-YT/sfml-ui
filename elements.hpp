#define SFML_STATIC

#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include <SFML/Graphics.hpp>
#include "concrete.hpp"
#include "methods.hpp"
#include <iostream>
#include <string>

//using namespace std;

namespace UI {
    class Element : public Concrete {
    private:
        sf::RectangleShape background;
        sf::Text text;
        sf::Vector2f size;

        void recomputePos();
        void recomputeSizes();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
            target.draw(text, states);
        }
    public:
        Element(
            sf::Font& font,
            std::string str = "",
            unsigned int charSize = 16,
            const sf::Vector2f& initSize = {-1.f, -1.f},
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Color& textColor = sBlack,
            const sf::Color& bgColor = sWhite
        );

        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2f& size);
        void setString(std::string str);
        void setFillColor(const sf::Color& color);
        void setTextColor(const sf::Color& color);
        void setCharacterSize(float size);

        sf::Vector2f getPosition();
        sf::Vector2f getSize();

        void drawText(sf::RenderTarget& target) {
            target.draw(text);
            //cout << (string)text.getString() << '\n' << text.getCharacterSize() << '\n' << (text.getFillColor() == sBlack) << '\n';
        }
    };

    Element::Element(
        sf::Font& font,
        std::string str,
        unsigned int charSize,
        const sf::Vector2f& initSize,
        const sf::Vector2f& pos,
        const sf::Color& textColor,
        const sf::Color& bgColor
    ) {
        size = initSize;

        text.setFont(font);
        text.setString(str);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);

        background.setPosition(pos);
        background.setSize(size);
        background.setFillColor(bgColor);

        this->recomputeSizes();
    }

    void Element::recomputePos() {
        sf::Vector2f pos = background.getPosition();
        text.setPosition(centerStrInBounds(
            {text.getLocalBounds().width, (float)text.getCharacterSize()},
            background.getSize(), pos
        ));
    }

    void Element::recomputeSizes() {
        sf::Vector2f textSize = {text.getLocalBounds().width, (float)text.getCharacterSize()},
            sizes = {0.f, 0.f};
        if (size.x == -1.f) sizes.x = textSize.x + 16.f;
        else sizes.x = size.x;
        if (size.y == -1.f) sizes.y = textSize.y + 8.f;
        else sizes.y = size.y;
        background.setSize(sizes);
        this->recomputePos();
    }

    void Element::setPosition(const sf::Vector2f& pos) {
        background.setPosition(pos);
        this->recomputePos();
    }

    void Element::setPosition(float x, float y) {
        background.setPosition(x, y);
        this->recomputePos();
    }

    void Element::setSize(const sf::Vector2f& size) {
        background.setSize(size);
        this->recomputeSizes();
    }

    void Element::setString(std::string str) {
        text.setString(str);
        this->recomputeSizes();
    }

    void Element::setFillColor(const sf::Color& color) {background.setFillColor(color);}
    void Element::setTextColor(const sf::Color& color) {text.setFillColor(color);}

    void Element::setCharacterSize(float size) {
        text.setCharacterSize(size);
        this->recomputeSizes();
    }

    sf::Vector2f Element::getPosition() {return background.getPosition();}
    sf::Vector2f Element::getSize() {return background.getSize();}
};

#endif