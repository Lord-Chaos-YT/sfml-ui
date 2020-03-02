#define SFML_STATIC

#ifndef SCROLL_HPP
#define SCROLL_HPP

#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "concrete.hpp"
#include "methods.hpp"
#include <functional>
#include <vector>

//using namespace std;

namespace UI {
    class Scroll : public Hold {
    private:
        sf::RectangleShape base;
        PopBackground bar;
        std::function<void(Scroll* scrollbar)> onHover, onUnHover, onClick, onUnClick;
        float scrollPosition = 0, virtualHeight = 0, mouseYOffset;
        std::pair<int, int> range;
        std::function<void(float percentilePos, float contentHeight)> onPositionUpdate;
        sf::Color mainColor;

        void recomputePos();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(base, states);
            target.draw(bar, states);
        }
    public:
        Scroll(
            const std::pair<int, int>& itemRange = {0, 8},
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Vector2f& size = {32.f, 512.f},
            const sf::Color& barColor = dGrey,
            const sf::Color& baseColor = grey,
            const std::pair<sf::Color, sf::Color>& barShadows = {lGrey, sBlack}
        );

        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2f& size);
        void setHoverAction(std::function<void(Scroll* scrollbar)> fnc);
        void setUnHoverAction(std::function<void(Scroll* scrollbar)> fnc);
        void setClickAction(std::function<void(Scroll* scrollbar)> fnc);
        void setUnClickAction(std::function<void(Scroll* scrollbar)> fnc);
        void setScrollPosition(float pos);
        void updateScrollPosition(float offset);
        void setScrollSize(const std::pair<int, int>& size);
        void setScrollVirtualHeight(float height);
        void setPositionUpdateAction(std::function<void(float percentilePos, float contentHeight)> fnc);
        void setFillColor(const sf::Color& color, bool temp = false);
        void setBaseColor(const sf::Color& color);
        void invert(bool temp = false);
        void revert();

        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        float getScrollPosition();

        void startHold(const sf::Vector2f& mousePos);
        void updateHold(const sf::Vector2f& mousePos);
        void endHold();

        void hover();
        void unHover();
        void click();
        void unClick();
    };

    Scroll::Scroll(
        const std::pair<int, int>& itemRange,
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const sf::Color& barColor,
        const sf::Color& baseColor,
        const std::pair<sf::Color, sf::Color>& barShadows
    ) {
        range = itemRange;
        base.setPosition(pos);
        base.setSize(size);
        base.setFillColor(baseColor);
        bar.setHighlightColor(barShadows.first);
        bar.setShadowColor(barShadows.second);
        this->setFillColor(barColor);
        this->recomputePos();
    }

    void Scroll::recomputePos() {
        sf::Vector2f pos = base.getPosition(), size = base.getSize();

        float barHeight, calcedHeight;
        {
            float clearHeight, factor;
            // display factor equals actual height divided by full height of elements
            // factor        =       bounds.height        /        virtualHeight
            factor = virtualHeight / size.y;
            if (factor < 1.f) factor = 1.f;
            //cout << factor << '\n';
            // height of scroll bar equals full height divided by display factor
            // bar.height        =        bounds.height      /       factor
            barHeight = size.y / factor;
            // usable height equals full height minus height of scroll bar
            // clearHeight    =    bounds.height       -        bar.height
            clearHeight = size.y - barHeight;
            // finally, calcedHeight:
            calcedHeight = (scrollPosition / (range.second - range.first)) * clearHeight;
        }
        bar.setSize({base.getSize().x, barHeight});
        if (calcedHeight < 0.f) calcedHeight = 0.f;
        else if (calcedHeight + barHeight > size.y) calcedHeight = size.y - barHeight;
        bar.setPosition({pos.x, pos.y + calcedHeight});
    }

    void Scroll::setPosition(const sf::Vector2f& pos) {
        base.setPosition(pos);
        this->recomputePos();
    }

    void Scroll::setPosition(float x, float y) {
        base.setPosition(x, y);
        this->recomputePos();
    }

    void Scroll::setSize(const sf::Vector2f& size) {
        base.setSize(size);
        this->recomputePos();
    }

    void Scroll::setHoverAction(std::function<void(Scroll* scrollbar)> fnc) {onHover = fnc;}
    void Scroll::setUnHoverAction(std::function<void(Scroll* scrollbar)> fnc) {onUnHover = fnc;}
    void Scroll::setClickAction(std::function<void(Scroll* scrollbar)> fnc) {onClick = fnc;}
    void Scroll::setUnClickAction(std::function<void(Scroll* scrollbar)> fnc) {onUnClick = fnc;}

    void Scroll::setScrollPosition(float pos) {
        scrollPosition = pos;
        this->recomputePos();
    }

    void Scroll::updateScrollPosition(float offset) {
        scrollPosition += offset;
        this->recomputePos();
    }

    void Scroll::setScrollSize(const std::pair<int, int>& size) {
        range = size;
        this->recomputePos();
    }

    void Scroll::setScrollVirtualHeight(float height) {
        virtualHeight = height;
        this->recomputePos();
    }

    void Scroll::setPositionUpdateAction(std::function<void(float percentilePos, float contentHeight)> fnc) {onPositionUpdate = fnc;}
    void Scroll::setFillColor(const sf::Color& color, bool temp) {bar.setFillColor(color, temp);}
    void Scroll::setBaseColor(const sf::Color& color) {base.setFillColor(color);}
    void Scroll::invert(bool temp) {bar.invert(temp);}
    void Scroll::revert() {bar.revert();}

    sf::Vector2f Scroll::getPosition() {return base.getPosition();}
    sf::Vector2f Scroll::getSize() {return base.getSize();}
    float Scroll::getScrollPosition() {return scrollPosition;}

    void Scroll::startHold(const sf::Vector2f& mousePos) {
        sf::Vector2f pos = bar.getPosition(), size = bar.getSize();
        //if (isWithinBounds(mousePos, {pos.x, pos.y, size.x, size.y})) 
        mouseYOffset = mousePos.y - pos.y;
    }

    void Scroll::updateHold(const sf::Vector2f& mousePos) {
        if (virtualHeight <= base.getSize().y) scrollPosition = 0.f;
        sf::Vector2f pos = base.getPosition(), size = base.getSize();
        float yPos = (mousePos.y - pos.y) - mouseYOffset,
            clearHeight = size.y - bar.getSize().y;
        if (yPos > clearHeight) yPos = clearHeight;
        if (yPos < 0.f) yPos = 0.f;
        this->setScrollPosition((yPos / clearHeight) * (range.second - range.first));
        onPositionUpdate(scrollPosition, virtualHeight);
    }

    void Scroll::endHold() {mouseYOffset = 0.f;}

    void Scroll::hover() {if ((bool)onHover) onHover(this);}
    void Scroll::unHover() {if ((bool)onUnHover) onUnHover(this);}
    void Scroll::click() {if ((bool)onClick) onClick(this);}
    void Scroll::unClick() {if ((bool)onUnClick) onUnClick(this);}
};

#endif