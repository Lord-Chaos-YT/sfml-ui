#define SFML_STATIC

#ifndef SCROLLWINDOW_HPP
#define SCROLLWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "concrete.hpp"
#include "elements.hpp"
#include "scroll.hpp"
#include <vector>

//using namespace std;

namespace UI {
    template<class DataType = Element> class ScrollWindow_0 : public Hold {
    private:
        Scroll scrollbar;
        sf::RectangleShape background;
        sf::RenderTexture texture;
        sf::Sprite sprite;
        std::vector<DataType>* data = nullptr;

        float getFullElemHeight();

        void recomputePos();
        void recomputeSizes();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
            target.draw(sprite, states);
            target.draw(scrollbar, states);
        }
    public:
        ScrollWindow_0(
            std::vector<DataType>* initData = nullptr,
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Vector2f& size = {128.f, 64.f},
            float scrollbarWidth = 16.f
        );

        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2f& size);
        void setHoverAction(std::function<void(Scroll* scrollbar)> fnc);
        void setUnHoverAction(std::function<void(Scroll* scrollbar)> fnc);
        void setClickAction(std::function<void(Scroll* scrollbar)> fnc);
        void setUnClickAction(std::function<void(Scroll* scrollbar)> fnc);
        void setData(std::vector<DataType>* newData);

        sf::Vector2f getPosition();
        sf::Vector2f getSize();

        void startHold(const sf::Vector2f& mousePos);
        void updateHold(const sf::Vector2f& mousePos);
        void endHold();
        bool isMouseOverElem(const sf::Vector2f& mousePos);

        void hover();
        void unHover();
        void click();
        void unClick();

        void drawSprite(sf::RenderTarget& target) {target.draw(sprite);}

        void recomputeInternalData();
    };

    template<class DataType> ScrollWindow_0<DataType>::ScrollWindow_0(
        std::vector<DataType>* initData,
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        float scrollbarWidth
    ) {
        if (!std::is_base_of<sf::Drawable, DataType>::value) throw "Invalid type specifier. Type must inherit from class sf::Drawable!";

        data = initData;

        float fullElemHeight = this->getFullElemHeight();
        texture.create((unsigned int)size.x, (fullElemHeight > 0 ? (unsigned int)fullElemHeight : (unsigned int)size.y));
        sprite.setTexture(texture.getTexture());

        background.setPosition(pos);
        background.setSize(size);

        scrollbar.setSize({scrollbarWidth, size.y});
        scrollbar.setScrollVirtualHeight(this->getFullElemHeight());
        scrollbar.setScrollSize({0, (data != nullptr ? data->size() : 0)});

        this->recomputeSizes();

        scrollbar.setPositionUpdateAction([this](float percentilePos, float contentHeight) -> void {
            this->recomputePos();
        });
    }

    template<class DataType> void ScrollWindow_0<DataType>::recomputePos() {
        sf::Vector2f pos = background.getPosition(), size = background.getSize(), scrollbarSize = scrollbar.getSize();
        if (data != nullptr) {
            float scrollPosition = scrollbar.getScrollPosition() / data->size(),
                hiddenAbove = scrollPosition * (this->getFullElemHeight() - size.y);
            
            sprite.setTextureRect({0, (int)hiddenAbove, (int)(size.x - scrollbarSize.x), (int)size.y});
        }

        sprite.setPosition(pos);
        scrollbar.setPosition({pos.x + (size.x - scrollbarSize.x), pos.y});
    }

    template<class DataType> void ScrollWindow_0<DataType>::recomputeSizes() {
        scrollbar.setSize({scrollbar.getSize().x, background.getSize().y});
        float fullElemHeight = this->getFullElemHeight();
        sf::Vector2f size = background.getSize();
        texture.create((unsigned int)size.x, (fullElemHeight > 0 ? (unsigned int)fullElemHeight : (unsigned int)size.y));
        texture.clear(background.getFillColor());

        if (data != nullptr) {
            float curOffset = 0.f;
            for (int i = 0; i < data->size(); i++) {
                data->at(i).setPosition({0.f, curOffset});
                texture.draw(data->at(i));
                curOffset += data->at(i).getSize().y;
            }
        }
        texture.display();

        this->recomputePos();
    }

    template<class DataType> float ScrollWindow_0<DataType>::getFullElemHeight() {
        float sum = 0.f;
        if (data != nullptr) for (int i = 0; i < data->size(); i++) sum += data->at(i).getSize().y;
        return sum;
    }

    template<class DataType> void ScrollWindow_0<DataType>::setPosition(const sf::Vector2f& pos) {
        background.setPosition(pos);
        this->recomputePos();
    }

    template<class DataType> void ScrollWindow_0<DataType>::setPosition(float x, float y) {
        background.setPosition(x, y);
        this->recomputePos();
    }

    template<class DataType> void ScrollWindow_0<DataType>::setSize(const sf::Vector2f& size) {
        background.setSize(size);
        this->recomputeSizes();
    }

    template<class DataType> void ScrollWindow_0<DataType>::setHoverAction(std::function<void(Scroll* scrollbar)> fnc) {scrollbar.setHoverAction(fnc);}
    template<class DataType> void ScrollWindow_0<DataType>::setUnHoverAction(std::function<void(Scroll* scrollbar)> fnc) {scrollbar.setUnHoverAction(fnc);}
    template<class DataType> void ScrollWindow_0<DataType>::setClickAction(std::function<void(Scroll* scrollbar)> fnc) {scrollbar.setClickAction(fnc);}
    template<class DataType> void ScrollWindow_0<DataType>::setUnClickAction(std::function<void(Scroll* scrollbar)> fnc) {scrollbar.setUnClickAction(fnc);}

    template<class DataType> void ScrollWindow_0<DataType>::setData(std::vector<DataType>* newData) {
        data = newData;
        this->recomputeInternalData();
    }

    template<class DataType> sf::Vector2f ScrollWindow_0<DataType>::getPosition() {return background.getPosition();}
    template<class DataType> sf::Vector2f ScrollWindow_0<DataType>::getSize() {return background.getSize();}

    template<class DataType> void ScrollWindow_0<DataType>::startHold(const sf::Vector2f& mousePos) {scrollbar.startHold(mousePos);}
    template<class DataType> void ScrollWindow_0<DataType>::updateHold(const sf::Vector2f& mousePos) {scrollbar.updateHold(mousePos);}
    template<class DataType> void ScrollWindow_0<DataType>::endHold() {scrollbar.endHold();}

    template<class DataType> bool ScrollWindow_0<DataType>::isMouseOverElem(const sf::Vector2f& mousePos) {
        if (data == nullptr) return false;
        sf::Vector2f size = background.getSize();
        float
            scrollPosition = scrollbar.getScrollPosition() / data->size(),
            hiddenAbove = scrollPosition * (this->getFullElemHeight() - size.y);
        sf::Vector2f
            pos = background.getPosition(),
            adjustedPos = {mousePos.x - pos.x, (mousePos.y - pos.y) + hiddenAbove};
        
        if (adjustedPos.x < 0.f
        || adjustedPos.y < 0.f
        || adjustedPos.x > size.x + pos.x
        || adjustedPos.y > size.y + pos.y) return false;
        
        for (int i = 0; i< data->size(); i++) if (data->at(i).isMouseOver(adjustedPos)) return true;
        return false;
    }

    template<class DataType> void ScrollWindow_0<DataType>::hover() {scrollbar.hover();}
    template<class DataType> void ScrollWindow_0<DataType>::unHover() {scrollbar.unHover();}
    template<class DataType> void ScrollWindow_0<DataType>::click() {scrollbar.click();}
    template<class DataType> void ScrollWindow_0<DataType>::unClick() {scrollbar.unClick();}

    template<class DataType> void ScrollWindow_0<DataType>::recomputeInternalData() {
        scrollbar.setScrollVirtualHeight(this->getFullElemHeight());
        scrollbar.setScrollSize({0, (data != nullptr ? data->size() : 0)});
        this->recomputeSizes();
    }
};

#endif