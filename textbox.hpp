#define SFML_STATIC

#ifndef TEXTBOX0_HPP
#define TEXTBOX0_HPP

#include <SFML/Graphics.hpp>
#include "textcursor.hpp"
#include "concrete.hpp"
#include "methods.hpp"
#include <functional>
#include "keymap.hpp"
#include "pop.hpp"
#include <string>

namespace UI {
    class TextBox_0 : public Focus {
    private:
        sf::RectangleShape background;
        sf::RenderTexture texture;
        sf::Text text;
        TextCursor cursor;
        sf::Sprite sprite;
        Pop pop;
        unsigned int curPos = 0, boundPos = 0;
        bool align = false;
        sf::Vector2f padding;
        sf::Time focusTime;
        std::function<void(TextBox_0* textbox)> onHover, onUnHover, onClick, onUnClick;
        std::function<void(TextBox_0* textbox, std::string buffer)> onEnter;

        void recomputeText();
        void recomputePos();
        void recomputeSizes();

        float getStrWidth(std::string str, sf::Text& test);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
            target.draw(sprite, states);
            target.draw(pop, states);
            target.draw(cursor, states);
        }
    public:
        TextBox_0(
            const sf::Font& font,
            unsigned int characterSize = 16,
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Vector2f& pad = {2.f, 2.f},
            const sf::Vector2f& size = {64.f, -1.f},
            const sf::Color& bgColor = sWhite,
            const sf::Color& txtColor = sBlack,
            const std::pair<sf::Color, sf::Color> popColors = {dGrey, lGrey},
            float outlineThickness = 1.f
        );
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2f& size);
        void setFont(const sf::Font& font);
        void setCharacterSize(unsigned int size, bool autoResize = true);
        void setHoverAction(std::function<void(TextBox_0* textbox)> fnc);
        void setUnHoverAction(std::function<void(TextBox_0* textbox)> fnc);
        void setClickAction(std::function<void(TextBox_0* textbox)> fnc);
        void setUnClickAction(std::function<void(TextBox_0* textbox)> fnc);
        void setEnterAction(std::function<void(TextBox_0* textbox, std::string buffer)> fnc);
        void setBuffer(std::string str = "");

        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        std::string getBuffer();

        void startFocus(const sf::Time& time);
        void focusTick(const sf::Time& time);
        void endFocus();
        void registerKeystroke(const sf::Keyboard::Key& key, bool shiftPressed);

        void hover();
        void unHover();
        void click();
        void unClick();

        /*void drawText(sf::RenderTarget& target) {
            text.setPosition({192.f, 64.f});
            target.draw(text);
        }*/
    };

    TextBox_0::TextBox_0(
        const sf::Font& font,
        unsigned int characterSize,
        const sf::Vector2f& pos,
        const sf::Vector2f& pad,
        const sf::Vector2f& size,
        const sf::Color& bgColor,
        const sf::Color& txtColor,
        const std::pair<sf::Color, sf::Color> popColors,
        float outlineThickness
    ) {
        padding = pad;
        text.setFont(font);
        text.setFillColor(txtColor);
        text.setCharacterSize(characterSize);
        sprite.setTexture(texture.getTexture());
        pop.setDrawOrder(2);
        pop.setColors(popColors);
        background.setPosition(pos);
        if (size.y == -1.f) background.setSize({size.x, (float)characterSize + (padding.y * 2.f)});
        else background.setSize(size);
        background.setFillColor(bgColor);
        background.setOutlineColor(sBlack);
        background.setOutlineThickness(outlineThickness);
        this->recomputeSizes();
    }

    void TextBox_0::recomputeText() {
        sf::Vector2f
            pos = background.getPosition(),
            size = background.getSize(),
            textSize = {size.x - (padding.x * 2.f), size.y - (padding.y * 2.f)};
        sf::Text test;
        test.setFont(*text.getFont());
        test.setCharacterSize(text.getCharacterSize());
        std::string buffer = text.getString();
        float curOffset, bufferWidth = this->getStrWidth(buffer, test) + (padding.x * 2.f);

        bool recompute = true;
        while (recompute) {
            recompute = false;
            if ((curPos > boundPos || boundPos > buffer.size()) && align) {
                boundPos = curPos, recompute = true;
                continue;
            } else if (curPos < boundPos && !align) {
                boundPos = curPos, recompute = true;
                continue;
            }
            std::string temp = "";
            float width = 0.f;
            curOffset = 0.f;
            int i = boundPos;
            if (align) {
                if (bufferWidth < textSize.x) {
                    boundPos = 0, align = false, recompute = true;
                    continue;
                }
                for (i--; width < textSize.x && i >= 0; i--) {
                    temp = buffer[i] + temp;
                    width = this->getStrWidth(temp, test);
                    if (i == (int)curPos) curOffset = width;
                }
                if ((int)curPos - 1 <= i) {
                    boundPos = curPos, align = false, recompute = true;
                    continue;
                }
            } else {
                for (; width < textSize.x && i < buffer.size(); i++) {
                    temp += buffer[i];
                    width = this->getStrWidth(temp, test);
                    if (i + 1 == (int)curPos) curOffset = width;
                }
                if ((int)curPos >= i && width > textSize.x) {
                    boundPos = curPos, align = true, recompute = true;
                    continue;
                }
            }
        }
        float
            calcedCurPos = (align ? (pos.x + textSize.x) - (curOffset + padding.x) : pos.x + (padding.x * 2.f) + curOffset),
            calcedOffset = this->getStrWidth(((std::string)text.getString()).substr(0, boundPos), test) - (align ? textSize.x - (padding.x * 2.f) : 0.f);
        
        cursor.setPosition(calcedCurPos, center({0.f, (float)cursor.getCharacterSize()}, {0.f, pos.y + (size.y / 2.f)}).y);
        sprite.setTextureRect({(int)calcedOffset, 0, (int)textSize.x, (int)textSize.y});

        text.setPosition({0.f, centerStrInBounds({0.f, (float)text.getCharacterSize()}, {0.f, textSize.y}, {0.f, 0.f}).y});

        texture.create((unsigned int)(bufferWidth > textSize.x ? bufferWidth : textSize.x), (unsigned int)textSize.y);
        texture.clear(background.getFillColor());
        texture.draw(text);
        texture.display();
    }

    void TextBox_0::recomputePos() {
        sf::Vector2f pos = background.getPosition();
        sprite.setPosition({pos.x + padding.x, pos.y + padding.y});
        pop.setPosition(pos);
        this->recomputeText();
    }

    void TextBox_0::recomputeSizes() {
        sf::Vector2f size = background.getSize();
        cursor.setCharacterSize(text.getCharacterSize());
        pop.setSize(size);
        this->recomputePos();
    }

    float TextBox_0::getStrWidth(std::string str, sf::Text& test) {
        test.setString(str);
        return test.getLocalBounds().width;
    }

    void TextBox_0::setPosition(const sf::Vector2f& pos) {
        background.setPosition(pos);
        this->recomputePos();
    }

    void TextBox_0::setPosition(float x, float y) {
        background.setPosition(x, y);
        this->recomputePos();
    }

    void TextBox_0::setSize(const sf::Vector2f& size) {
        if (size.y == -1.f) background.setSize({size.x, (float)text.getCharacterSize() + (padding.y * 2.f)});
        else background.setSize(size);
        this->recomputeSizes();
    }

    void TextBox_0::setCharacterSize(unsigned int size, bool autoResize) {
        text.setCharacterSize(size);
        if (autoResize) background.setSize({background.getSize().x, (float)size + (padding.y * 2.f)});
        this->recomputeSizes();
    }

    void TextBox_0::setFont(const sf::Font& font) {
        text.setFont(font);
        this->recomputeSizes();
    }

    void TextBox_0::setHoverAction(std::function<void(TextBox_0* textbox)> fnc) {onHover = fnc;}
    void TextBox_0::setUnHoverAction(std::function<void(TextBox_0* textbox)> fnc) {onUnHover = fnc;}
    void TextBox_0::setClickAction(std::function<void(TextBox_0* textbox)> fnc) {onClick = fnc;}
    void TextBox_0::setUnClickAction(std::function<void(TextBox_0* textbox)> fnc) {onUnClick = fnc;}
    void TextBox_0::setEnterAction(std::function<void(TextBox_0* textbox, std::string buffer)> fnc) {onEnter = fnc;}

    void TextBox_0::setBuffer(std::string str) {
        text.setString(str);
        curPos = 0;
        this->recomputeText();
    }

    sf::Vector2f TextBox_0::getPosition() {return background.getPosition();}
    sf::Vector2f TextBox_0::getSize() {return background.getSize();}
    std::string TextBox_0::getBuffer() {return text.getString();}

    void TextBox_0::startFocus(const sf::Time& time) {
        cursor.display();
        focusTime = time;
    }

    void TextBox_0::focusTick(const sf::Time& time) {
        if (time.asMilliseconds() % 1000 < 500) cursor.display();
        else cursor.hide();
    }

    void TextBox_0::endFocus() {cursor.hide();}

    void TextBox_0::registerKeystroke(const sf::Keyboard::Key& key, bool shiftPressed) {
        if (key == sf::Keyboard::Enter && (bool)onEnter) onEnter(this, text.getString());
        else if (key == sf::Keyboard::BackSpace && curPos > 0) {
            std::string buffer = text.getString();
            text.setString(buffer.substr(0, curPos - 1) + buffer.substr(curPos, buffer.size()));
            curPos--;
        } else if (key == sf::Keyboard::Left && curPos > 0) curPos--;
        else if (key == sf::Keyboard::Right && curPos < text.getString().getSize()) curPos++;
        else if (sfKeyToChar.count(key) > 0) {
            std::string buffer = text.getString();
            text.setString(
                buffer.substr(0, curPos)
                + (shiftPressed ? sfKeyToChar.at(key).upper : sfKeyToChar.at(key).lower)
                + buffer.substr(curPos, buffer.size())
            );
            curPos++;
        }
        this->recomputeText();
    }

    void TextBox_0::hover() {if ((bool)onHover) onHover(this);}
    void TextBox_0::unHover() {if ((bool)onUnHover) onUnHover(this);}
    void TextBox_0::click() {if ((bool)onClick) onClick(this);}
    void TextBox_0::unClick() {if ((bool)onUnClick) onUnClick(this);}
};

#endif