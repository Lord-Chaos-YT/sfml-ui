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
        sf::Text text;
        sf::Vector2f sizeDefault;

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
            bool pop = false,
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

        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;

        void drawText(sf::RenderTarget& target) {
            target.draw(text);
            //cout << (string)text.getString() << '\n' << text.getCharacterSize() << '\n' << (text.getFillColor() == sBlack) << '\n';
        }
    };

    template<class BackgroundType> Element<BackgroundType>::Element(
        sf::Font& font,
        std::string str,
        bool pop,
        unsigned int charSize,
        const sf::Vector2f& initSize,
        const sf::Vector2f& pos,
        const sf::Color& textColor,
        const sf::Color& bgColor
    ) : sizeDefault{initSize}, text{str, font, charSize} {
        if (!std::is_base_of<sf::RectangleShape, BackgroundType>::value) throw "Invalid type specifier. Type must inherit from class sf::RectangleShape!";
        text.setFillColor(textColor);

        background.setPosition(pos);
        background.setSize(sizeDefault);
        background.setFillColor(bgColor);

        this->recomputeSizes();
    }

    template<class BackgroundType> void Element<BackgroundType>::recomputePos() {
        sf::Vector2f pos = background.getPosition();
        text.setPosition(centerStrInBounds(
            {text.getLocalBounds().width, (float)text.getCharacterSize()},
            background.getSize(), pos
        ));
    }

    template<class BackgroundType> void Element<BackgroundType>::recomputeSizes() {
        sf::Vector2f textSize = {text.getLocalBounds().width, (float)text.getCharacterSize()},
            sizes = {0.f, 0.f};
        if (sizeDefault.x == -1.f) sizes.x = textSize.x + 16.f;
        else sizes.x = sizeDefault.x;
        if (sizeDefault.y == -1.f) sizes.y = textSize.y + 8.f;
        else sizes.y = sizeDefault.y;
        background.setSize(sizes);
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
        background.setSize(size);
        this->recomputeSizes();
    }

    template<class BackgroundType> void Element<BackgroundType>::setString(std::string str) {
        text.setString(str);
        this->recomputeSizes();
    }

    template<class BackgroundType> void Element<BackgroundType>::setFillColor(const sf::Color& color) {background.setFillColor(color);}
    template<class BackgroundType> void Element<BackgroundType>::setTextColor(const sf::Color& color) {text.setFillColor(color);}

    template<class BackgroundType> void Element<BackgroundType>::setCharacterSize(float size) {
        text.setCharacterSize(size);
        this->recomputeSizes();
    }

    template<class BackgroundType> sf::Vector2f Element<BackgroundType>::getPosition() const {return background.getPosition();}
    template<class BackgroundType> sf::Vector2f Element<BackgroundType>::getSize() const {return background.getSize();}
};

#endif