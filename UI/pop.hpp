#define SFML_STATIC

#ifndef SHADOW_HPP
#define SHADOW_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"

//using namespace std;

namespace UI {
    class Pop : public sf::Drawable {
    private:
        sf::RectangleShape top, bottom, left, right;
        float padTop, padBottom, padLeft, padRight;
        int drawOrder = 0;

        void recomputePos();
        void recomputeSizes();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            if (drawOrder == 0) {
                target.draw(top, states);
                target.draw(right, states);
                target.draw(bottom, states);
                target.draw(left, states);
            } else if (drawOrder == 1) {
                target.draw(top, states);
                target.draw(left, states);
                target.draw(bottom, states);
                target.draw(right, states);
            } else if (drawOrder == 2) {
                target.draw(bottom, states);
                target.draw(left, states);
                target.draw(top, states);
                target.draw(right, states);
            } else if (drawOrder == 3) {
                target.draw(bottom, states);
                target.draw(right, states);
                target.draw(top, states);
                target.draw(left, states);
            }
        }
    public:
        Pop(
            const sf::Vector2f& pos,
            const sf::Vector2f& size,
            float topPad = 1.f,
            float bottomPad = 1.f,
            float leftPad = 1.f,
            float rightPad = 1.f,
            const sf::Color& colorTop = sWhite,
            const sf::Color& colorBottom = dGrey,
            const sf::Color& colorLeft = sWhite,
            const sf::Color& colorRight = dGrey
        );
        Pop(
            const sf::Vector2f& pos,
            const sf::Vector2f& size = {0.f, 0.f},
            float padX = 1.f,
            float padY = 1.f,
            const std::pair<sf::Color, sf::Color>& shadowColors = {sWhite, dGrey}
        );
        Pop(
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Vector2f& size = {0.f, 0.f},
            float pad = 1.f,
            const std::pair<sf::Color, sf::Color>& shadowColors = {sWhite, dGrey}
        );

        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2f& size);
        void setPadding(float topPad, float bottomPad, float leftPad, float rightPad);
        void setPadding(float pad);
        void setColors(
            const sf::Color& colorTop,
            const sf::Color& colorBottom,
            const sf::Color& colorLeft,
            const sf::Color& colorRight
        );
        void setColors(const std::pair<sf::Color, sf::Color>& shadowColors);
        void setHighlight(const sf::Color& color);
        void setShadow(const sf::Color& color);
        void setDrawOrder(int order);

        sf::Vector2f getSize();
    };

    Pop::Pop(
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        float topPad,
        float bottomPad,
        float leftPad,
        float rightPad,
        const sf::Color& colorTop,
        const sf::Color& colorBottom,
        const sf::Color& colorLeft,
        const sf::Color& colorRight
    ) {
        this->setPadding(padTop, padBottom, padLeft, padRight);
        this->setPosition(pos);
        this->setSize(size);
        this->setColors(colorTop, colorBottom, colorLeft, colorRight);
    }

    Pop::Pop(
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        float padX,
        float padY,
        const std::pair<sf::Color, sf::Color>& shadowColors
    ) {
        this->setPadding(padY, padY, padX, padX);
        this->setPosition(pos);
        this->setSize(size);
        this->setColors(shadowColors);
    }

    Pop::Pop(
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        float pad,
        const std::pair<sf::Color, sf::Color>& shadowColors
    ) {
        this->setPadding(pad);
        this->setPosition(pos);
        this->setSize(size);
        this->setColors(shadowColors);
    }

    void Pop::recomputePos() {
        sf::Vector2f pos = top.getPosition();
        left.setPosition(pos);
        right.setPosition({pos.x + (top.getSize().x - padRight), pos.y});
        bottom.setPosition({pos.x, pos.y + (left.getSize().y - padBottom)});
    }

    void Pop::recomputeSizes() {
        right.setSize({padRight, left.getSize().y});
        bottom.setSize({top.getSize().x, padBottom});
        this->recomputePos();
    }

    void Pop::setPosition(const sf::Vector2f& pos) {
        top.setPosition(pos);
        this->recomputePos();
    }

    void Pop::setPosition(float x, float y) {
        top.setPosition(x, y);
        this->recomputePos();
    }

    void Pop::setSize(const sf::Vector2f& size) {
        top.setSize({size.x, padTop});
        left.setSize({padLeft, size.y});
        this->recomputeSizes();
    }

    void Pop::setPadding(float topPad, float bottomPad, float leftPad, float rightPad) {
        padTop = topPad, padBottom = bottomPad, padLeft = leftPad, padRight = rightPad;
        this->recomputeSizes();
    }

    void Pop::setPadding(float pad) {
        padTop = pad, padBottom = pad, padLeft = pad, padRight = pad;
        this->recomputeSizes();
    }

    void Pop::setColors(
        const sf::Color& colorTop,
        const sf::Color& colorBottom,
        const sf::Color& colorLeft,
        const sf::Color& colorRight
    ) {
        top.setFillColor(colorTop);
        bottom.setFillColor(colorBottom);
        left.setFillColor(colorLeft);
        right.setFillColor(colorRight);
    }

    void Pop::setColors(const std::pair<sf::Color, sf::Color>& shadowColors) {
        top.setFillColor(shadowColors.first);
        bottom.setFillColor(shadowColors.second);
        left.setFillColor(shadowColors.first);
        right.setFillColor(shadowColors.second);
    }

    void Pop::setHighlight(const sf::Color& color) {
        if (drawOrder == 0) {
            top.setFillColor(color);
            left.setFillColor(color);
        } else if (drawOrder == 1) {
            right.setFillColor(color);
            top.setFillColor(color);
        } else if (drawOrder == 2) {
            bottom.setFillColor(color);
            right.setFillColor(color);
        } else if (drawOrder == 3) {
            left.setFillColor(color);
            bottom.setFillColor(color);
        }
    }

    void Pop::setShadow(const sf::Color& color) {
        if (drawOrder == 0) {
            bottom.setFillColor(color);
            right.setFillColor(color);
        } else if (drawOrder == 1) {
            left.setFillColor(color);
            bottom.setFillColor(color);
        } else if (drawOrder == 2) {
            top.setFillColor(color);
            left.setFillColor(color);
        } else if (drawOrder == 3) {
            right.setFillColor(color);
            top.setFillColor(color);
        }
    }

    //void Pop::setShadow(const sf::Color& color) {}

    /**
     * 0 = top left to bottom right
     * 1 = top right to bottom left
     * 2 = bottom right to top left
     * 3 = bottom left to top right
     */
    void Pop::setDrawOrder(int order) {
        if (order >= 0 && order <= 3) drawOrder = order;
        else throw "Given order is out of range! Must be a number on [0, 3].";
    }

    sf::Vector2f Pop::getSize() {return {top.getSize().x, left.getSize().y};}
};

#endif