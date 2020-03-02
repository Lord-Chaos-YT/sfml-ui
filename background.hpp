#define SFML_STATIC

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "constants.hpp"
#include "concrete.hpp"
#include <iostream>
#include "pop.hpp"

//using namespace std;

namespace UI {
    class Background : public sf::Drawable {
    private:
        sf::RectangleShape base;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(base, states);
        }
    public:
        Background();
        virtual void setOutlineThickness(float thickness);
        virtual void setOutlineColor(const sf::Color& color);
        virtual void setFillColor(const sf::Color& color);
        virtual void setPosition(const sf::Vector2f& pos);
        virtual void setPosition(float x, float y);
        virtual void setSize(const sf::Vector2f& size);
        virtual void setShadowColor(const sf::Color& color) {base.setFillColor(color);}
        
        virtual const sf::Vector2f& getSize();
        virtual sf::Vector2f getPosition();
        virtual sf::Color getOutlineColor();
        virtual sf::Color getFillColor();
        virtual float getOutlineThickness();
    };

    Background::Background() {}

    void Background::setOutlineThickness(float thickness) {base.setOutlineThickness(thickness);}
    void Background::setOutlineColor(const sf::Color& color) {base.setOutlineColor(color);}
    void Background::setFillColor(const sf::Color& color) {base.setFillColor(color);}
    void Background::setPosition(const sf::Vector2f& pos) {base.setPosition(pos);}
    void Background::setPosition(float x, float y) {base.setPosition(x, y);}
    void Background::setSize(const sf::Vector2f& size) {base.setSize(size);}
    const sf::Vector2f& Background::getSize() {return base.getSize();}
    sf::Vector2f Background::getPosition() {return base.getPosition();}
    sf::Color Background::getOutlineColor() {return base.getOutlineColor();}
    sf::Color Background::getFillColor() {return base.getFillColor();}
    float Background::getOutlineThickness() {return base.getOutlineThickness();}

    class PopBackground : public Background {
    private:
        sf::RectangleShape base;
        Pop shadow;
        float padding;
        sf::Color baseColor, shadowColor, highlightColor;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(base, states);
            target.draw(shadow, states);
        }
        void recomputePos();
        void recomputeSizes();
    public:
        PopBackground(
            const sf::Vector2f& pos = {0, 0},
            const sf::Vector2f& size = {0, 0},
            const sf::Color& frontColor = lGrey,
            const sf::Color& highlightColor = sWhite,
            const sf::Color& shadowColor = dGrey,
            float pad = 1
        );
        void setColor(const sf::Color& frontColor, const sf::Color& highlightColor, const sf::Color& baseColor = dGrey);
        void setPadding(float pad);
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2f& size);
        void setOutlineThickness(float thickness);
        void setOutlineColor(const sf::Color& color);
        void setFillColor(const sf::Color& color, bool temp = false);
        void setShadowColor(const sf::Color& color);
        void setHighlightColor(const sf::Color& color);
        void invert(bool temp = false);
        void revert();
        const sf::Vector2f& getSize();
        sf::Vector2f getPosition();
        sf::Color getOutlineColor();
        sf::Color getFillColor();
        sf::Color getShadowColor();
        sf::Color getHighlightColor();
        float getOutlineThickness();
    };

    PopBackground::PopBackground(
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const sf::Color& frontColor,
        const sf::Color& hlColor,
        const sf::Color& sColor,
        float pad
    ) {
        padding = pad;
        this->setColor(frontColor, hlColor, sColor);
        base.setPosition(pos);
        base.setSize(size);
        this->recomputeSizes();
    }

    void PopBackground::recomputePos() {
        sf::Vector2f pos = base.getPosition();
        shadow.setPosition(pos);
    }

    void PopBackground::recomputeSizes() {
        shadow.setSize(base.getSize());
        this->recomputePos();
    }

    void PopBackground::setColor(const sf::Color& frontColor, const sf::Color& hlColor, const sf::Color& sColor) {
        shadow.setColors({highlightColor = hlColor, shadowColor = sColor});
        base.setFillColor(frontColor);
    }

    void PopBackground::setPadding(float pad) {
        shadow.setPadding(padding = pad);
    }

    void PopBackground::setPosition(const sf::Vector2f& pos) {
        base.setPosition(pos);
        this->recomputePos();
    }

    void PopBackground::setPosition(float x, float y) {
        base.setPosition(x, y);
        this->recomputePos();
    }

    void PopBackground::setSize(const sf::Vector2f& size) {
        base.setSize(size);
        this->recomputeSizes();
    }

    void PopBackground::setOutlineThickness(float thickness) {base.setOutlineThickness(thickness);}
    void PopBackground::setOutlineColor(const sf::Color& color) {base.setOutlineColor(color);}

    void PopBackground::setFillColor(const sf::Color& color, bool temp) {
        if (temp) base.setFillColor(color);
        else base.setFillColor(baseColor = color);
    }

    void PopBackground::setShadowColor(const sf::Color& color) {
        shadow.setShadow(shadowColor = color);
    }

    void PopBackground::setHighlightColor(const sf::Color& color) {
        shadow.setHighlight(highlightColor = color);
    }

    void PopBackground::invert(bool temp) {
        shadow.setHighlight(shadowColor);
        shadow.setShadow(highlightColor);
        if (!temp) {
            sf::Color t = highlightColor;
            highlightColor = shadowColor;
            shadowColor = t;
        }
    }

    void PopBackground::revert() {
        this->setFillColor(baseColor);
        this->setShadowColor(shadowColor);
        this->setHighlightColor(highlightColor);
    }

    const sf::Vector2f& PopBackground::getSize() {return base.getSize();}
    sf::Vector2f PopBackground::getPosition() {return base.getPosition();}
    sf::Color PopBackground::getOutlineColor() {return base.getOutlineColor();}
    sf::Color PopBackground::getFillColor() {return base.getFillColor();}
    sf::Color PopBackground::getShadowColor() {return shadowColor;}
    sf::Color PopBackground::getHighlightColor() {return highlightColor;}
    float PopBackground::getOutlineThickness() {return base.getOutlineThickness();}
};

#endif