#define SFML_STATIC

#ifndef TEXTCURSOR_HPP
#define TEXTCURSOR_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"

namespace UI {
    class TextCursor : public sf::Drawable {
    private:
        sf::RectangleShape cursor;
        bool displayed = false;
        float padding;
        unsigned int charSize;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            if (displayed) target.draw(cursor, states);
        }
    public:
        TextCursor(const sf::Vector2f& pos = {0.f, 0.f}, unsigned int textSize = 16, const sf::Color& color = sBlack, float pad = 1.f);

        void display();
        void hide();
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setCharacterSize(unsigned int size);
        void setPadding(float pad);
        void setFillColor(const sf::Color& color);

        unsigned int getCharacterSize();
        sf::Color getFillColor();
        bool isDisplayed();
    };

    TextCursor::TextCursor(const sf::Vector2f& pos, unsigned int textSize, const sf::Color& color, float pad) {
        cursor.setPosition({pos.x - (padding = pad), pos.y - padding});
        cursor.setSize({padding * 2.f, (charSize = textSize) + (padding * 2.f)});
        cursor.setFillColor(color);
    }

    void TextCursor::display() {displayed = true;}
    void TextCursor::hide() {displayed = false;}
    void TextCursor::setPosition(const sf::Vector2f& pos) {cursor.setPosition({pos.x - padding, pos.y - padding});}
    void TextCursor::setPosition(float x, float y) {cursor.setPosition(x - padding, y - padding);}
    void TextCursor::setCharacterSize(unsigned int size) {cursor.setSize({padding * 2.f, (charSize = size) + (padding * 2.f)});}

    void TextCursor::setPadding(float pad) {
        sf::Vector2f pos = cursor.getPosition();
        cursor.setPosition({pos.x - (padding = pad), pos.y - padding});
    }

    void TextCursor::setFillColor(const sf::Color& color) {cursor.setFillColor(color);}

    unsigned int TextCursor::getCharacterSize() {return charSize;}
    sf::Color TextCursor::getFillColor() {return cursor.getFillColor();}
    bool TextCursor::isDisplayed() {return displayed;}
};

#endif