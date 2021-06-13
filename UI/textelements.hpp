#define SFML_STATIC

#ifndef UI_TEXTELEMENTS_HPP
#define UI_TEXTELEMENTS_HPP

#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "elements.hpp"

//using namespace std;

namespace UI {
    template<class BackgroundType = PopBackground> class TextElement : public Element<BackgroundType> {
    protected:
        sf::Text text;

        void recomputePosFallthrough();
        void recomputePos();
        void recomputeSizes();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(Element<BackgroundType>::background, states);
            target.draw(text, states);
        }
    public:
        TextElement(
            sf::Font& font,
            std::string str = "",
            unsigned int charSize = 16,
            const sf::Vector2f& initSize = {-1.f, -1.f},
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Color& textColor = sBlack,
            const sf::Color& bgColor = sWhite
        );

        void setString(std::string str);
        void setTextColor(const sf::Color& color);
        void setCharacterSize(float size);

        std::string getString() const;
        sf::Color getTextColor() const;
        std::size_t getCharacterSize() const;
    };

    template<class BackgroundType> TextElement<BackgroundType>::TextElement(
        sf::Font& font,
        std::string str,
        unsigned int charSize,
        const sf::Vector2f& initSize,
        const sf::Vector2f& pos,
        const sf::Color& textColor,
        const sf::Color& bgColor
    ) : Element<BackgroundType>{initSize, pos, bgColor}, text{str, font, charSize} {
        if (!std::is_base_of<sf::RectangleShape, BackgroundType>::value) throw "Invalid type specifier. Type must inherit from class sf::RectangleShape!";
        text.setFillColor(textColor);

        this->recomputeSizes();
    }

    template<class BackgroundType> void TextElement<BackgroundType>::recomputePosFallthrough() {
        sf::Vector2f pos = this->Element<BackgroundType>::getPosition();
        text.setPosition(centerStrInBounds(
            {text.getLocalBounds().width, (float)text.getCharacterSize()},
            Element<BackgroundType>::background.getSize(), pos
        ));
    }

    template<class BackgroundType> void TextElement<BackgroundType>::recomputePos() {
        this->Element<BackgroundType>::recomputePos();
        this->recomputePosFallthrough();
    }

    template<class BackgroundType> void TextElement<BackgroundType>::recomputeSizes() {
        this->Element<BackgroundType>::recomputeSizes();
        sf::Vector2f textSize = {text.getLocalBounds().width, (float)text.getCharacterSize()},
            sizes = {0.f, 0.f};
        if (sizeDefault.x == -1.f) sizes.x = textSize.x + 16.f;
        else sizes.x = sizeDefault.x;
        if (sizeDefault.y == -1.f) sizes.y = textSize.y + 8.f;
        else sizes.y = sizeDefault.y;
        Element<BackgroundType>::background.setSize(sizes);
        this->recomputePosFallthrough();
    }

    template<class BackgroundType> void TextElement<BackgroundType>::setString(std::string str) {
        text.setString(str);
        this->recomputeSizes();
    }

    template<class BackgroundType> void TextElement<BackgroundType>::setTextColor(const sf::Color& color) {text.setFillColor(color);}

    template<class BackgroundType> void TextElement<BackgroundType>::setCharacterSize(float size) {
        text.setCharacterSize(size);
        this->recomputeSizes();
    }

    template<class BackgroundType> std::string TextElement<BackgroundType>::getString() const {return text.getString();}
    template<class BackgroundType> sf::Color TextElement<BackgroundType>::getTextColor() const {return text.getFillColor();}
    template<class BackgroundType> std::size_t TextElement<BackgroundType>::getCharacterSize() const {return text.getCharacterSize();}
};

#endif