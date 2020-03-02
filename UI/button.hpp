#define SFML_STATIC

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "constants.hpp"
#include "concrete.hpp"
#include "methods.hpp"
#include <functional>
#include <iostream>
#include <cstdlib>
#include <string>

//using namespace std;

namespace UI{
    template<class BackgroundType = PopBackground> class Button : public Hover {
    private:
        BackgroundType background;
        sf::Text text;
        sf::Color bgOutlineColor;
        sf::Color bgFillColor;
        sf::Color textColor;
        sf::Vector2f padding;
        float defWidth, defHeight;
        std::function<void(Button* button)> onHover, onUnHover, onClick, onUnClick;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
            target.draw(text, states);
        }

        void recomputePos();
        void recomputeSizes();
    public:
        Button(
            const std::string& text = "",
            const sf::Font& font = sf::Font{},
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Vector2f& pad = {16.f, 4.f},
            float defW = -1.f,
            float defH = -1.f,
            unsigned int textSize = 16,
            const sf::Color& textColor = sBlack,
            const sf::Color& fill = lGrey,
            const sf::Color& outline = sBlack,
            float outlineThickness = 1.f
        );

        void drawText(sf::RenderTarget& target);
        void drawBackground(sf::RenderTarget& target);

        void setBackground(BackgroundType& bg);
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setString(const std::string& str);
        void setCharacterSize(int size);
        void setFont(const sf::Font& font);
        void setOutlineColor(const sf::Color& color, bool temp = false);
        void setFillColor(const sf::Color& color, bool temp = false);
        void setTextColor(const sf::Color& color, bool temp = false);
        void setSize(const sf::Vector2f& size);
        void setHoverAction(std::function<void(Button* button)> fnc);
        void setUnHoverAction(std::function<void(Button* button)> fnc);
        void setClickAction(std::function<void(Button* button)> fnc);
        void setUnClickAction(std::function<void(Button* button)> fnc);

        std::string getString();
        sf::Vector2f getSize();
        sf::Vector2f getPosition();
        sf::Color getOutlineColor();
        sf::Color getFillColor();
        sf::Color getTextColor();
        float getOutlineThickness();
        BackgroundType& getBackground();

        void hover();
        void unHover();
        void click();
        void unClick();
        void revert();
        void defaultClickEffect(bool temp = true);

        bool isMouseOver(const sf::Vector2f& mousePos);
    };

    template<class BackgroundType> Button<BackgroundType>::Button(
        const std::string& str,
        const sf::Font& font,
        const sf::Vector2f& pos,
        const sf::Vector2f& pad,
        float defW,
        float defH,
        unsigned int textSize,
        const sf::Color& txtColor,
        const sf::Color& fill,
        const sf::Color& outline,
        float outlineThickness
    ) {
        if (!std::is_base_of<Background, BackgroundType>::value) throw "Invalid type specifier. Type must inherit from class Background!";

        defWidth = defW, defHeight = defH, padding = pad;

        text.setString(str);
        text.setFont(font);
        text.setCharacterSize(textSize);
        this->setTextColor(txtColor);

        this->setFillColor(fill);
        this->setOutlineColor(outline);
        background.setOutlineThickness(outlineThickness);
        
        this->setPosition(pos);
        this->recomputeSizes();
    }

    template<class BackgroundType> void Button<BackgroundType>::recomputePos() {
        text.setPosition(centerStrInBounds(
            {text.getLocalBounds().width, (float)text.getCharacterSize()},
            background.getSize(), background.getPosition()
        ));
    }

    template<class BackgroundType> void Button<BackgroundType>::recomputeSizes() {
        sf::FloatRect textBounds = text.getLocalBounds();
        float width, height;
        if (defWidth == -1) width = (padding.x * 2.f) + textBounds.width;
        else width = defWidth;
        if (defHeight == -1) height = (padding.y * 2.f) + textBounds.height;
        else height = defHeight;
        background.setSize({width, height});
        this->recomputePos();
    }

    template<class BackgroundType> void Button<BackgroundType>::drawText(sf::RenderTarget& target) {target.draw(text);}
    template<class BackgroundType> void Button<BackgroundType>::drawBackground(sf::RenderTarget& target) {target.draw(background);}

    template<class BackgroundType> void Button<BackgroundType>::setBackground(BackgroundType& bg) {background = bg;}

    template<class BackgroundType> void Button<BackgroundType>::setPosition(const sf::Vector2f& pos) {
        background.setPosition(pos);
        this->recomputePos();
    }

    template<class BackgroundType> void Button<BackgroundType>::setPosition(float x, float y) {
        background.setPosition({x, y});
        this->recomputePos();
    }

    template<class BackgroundType> void Button<BackgroundType>::setString(const std::string& str) {text.setString(str);}

    template<class BackgroundType> void Button<BackgroundType>::setCharacterSize(int size) {
        text.setCharacterSize(size);
        this->recomputeSizes();
    }

    template<class BackgroundType> void Button<BackgroundType>::setFont(const sf::Font& font) {text.setFont(font);}

    template<class BackgroundType> void Button<BackgroundType>::setOutlineColor(const sf::Color& color, bool temp) {
        background.setOutlineColor(color);
        if (!temp) bgOutlineColor = color;
    }

    template<class BackgroundType> void Button<BackgroundType>::setFillColor(const sf::Color& color, bool temp) {
        background.setFillColor(color);
        if (!temp) bgFillColor = color;
    }

    template<class BackgroundType> void Button<BackgroundType>::setTextColor(const sf::Color& color, bool temp) {
        text.setFillColor(color);
        if (!temp) textColor = color;
    }

    template<class BackgroundType> void Button<BackgroundType>::setSize(const sf::Vector2f& size) {
        background.setSize(size);
    }

    template<class BackgroundType> void Button<BackgroundType>::setHoverAction(std::function<void(Button* button)> fnc) {onHover = fnc;}
    template<class BackgroundType> void Button<BackgroundType>::setUnHoverAction(std::function<void(Button* button)> fnc) {onUnHover = fnc;}
    template<class BackgroundType> void Button<BackgroundType>::setClickAction(std::function<void(Button* button)> fnc) {onClick = fnc;}
    template<class BackgroundType> void Button<BackgroundType>::setUnClickAction(std::function<void(Button* button)> fnc) {onUnClick = fnc;}



    template<class BackgroundType> std::string Button<BackgroundType>::getString() {return text.getString();}
    template<class BackgroundType> sf::Vector2f Button<BackgroundType>::getSize() {return background.getSize();}
    template<class BackgroundType> sf::Vector2f Button<BackgroundType>::getPosition() {return background.getPosition();}
    template<class BackgroundType> sf::Color Button<BackgroundType>::getOutlineColor() {return background.getOutlineColor();}
    template<class BackgroundType> sf::Color Button<BackgroundType>::getFillColor() {return background.getFillColor();}
    template<class BackgroundType> sf::Color Button<BackgroundType>::getTextColor() {return text.getFillColor();}
    template<class BackgroundType> float Button<BackgroundType>::getOutlineThickness() {return background.getOutlineThickness();}
    template<class BackgroundType> BackgroundType& Button<BackgroundType>::getBackground() {return background;}

    template<class BackgroundType> void Button<BackgroundType>::hover() {if ((bool)onHover) onHover(this);}
    template<class BackgroundType> void Button<BackgroundType>::unHover() {if ((bool)onUnHover) onUnHover(this);}
    template<class BackgroundType> void Button<BackgroundType>::click() {if ((bool)onClick) onClick(this);}
    template<class BackgroundType> void Button<BackgroundType>::unClick() {if ((bool)onUnClick) onUnClick(this);}

    template<class BackgroundType> void Button<BackgroundType>::revert() {
        background.setOutlineColor(bgOutlineColor);
        background.setFillColor(bgFillColor);
        text.setFillColor(textColor);
        background.revert();
    }

    template<class BackgroundType> void Button<BackgroundType>::defaultClickEffect(bool temp) {background.invert(temp);}

    template<class BackgroundType> bool Button<BackgroundType>::isMouseOver(const sf::Vector2f& mousePos) {
        sf::Vector2f buttonPos = this->getPosition(), size = this->getSize();
        return (sf::FloatRect{buttonPos.x, buttonPos.y, size.x, size.y}).contains(mousePos);
    }
};

#endif