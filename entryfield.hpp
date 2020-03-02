#define SFML_STATIC

#ifndef ENTRYFIELD_HPP
#define ENTRYFIELD_HPP

#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "concrete.hpp"
#include "textbox.hpp"
#include <functional>
#include "button.hpp"
#include <iostream>

//using namespace std;

namespace UI {
    class EntryField : public sf::Drawable {
    private:
        float padding;
        sf::Vector2f size;
        function<void(EntryField* entryfield)> onHover, onUnHover, onClick, onUnClick;

        void recomputePos();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
            target.draw(textbox, states);
            target.draw(button, states);
            target.draw(title, states);
        }
    public:
        Background background;
        sf::Text title;
        TextBox_0 textbox;
        Button<> button;

        EntryField(
            const sf::Font& font,
            const std::string& titleText,
            const std::string& buttonText = "Submit",
            const sf::Vector2f& size = {256.f, 64.f},
            const sf::Vector2f& pos = {0.f, 0.f},
            float pad = 8.f,
            const sf::Color& bgColor = lGrey,
            float outlineThickness = 1.f
        );

        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setPadding(float pad);
        void setOutlineColor(const sf::Color& color);
        void setOutlineThickness(float thickness);

        sf::Vector2f getPosition();
        sf::Vector2f getSize();
    };

    EntryField::EntryField(
        const sf::Font& font,
        const std::string& titleText,
        const std::string& buttonText,
        const sf::Vector2f& size,
        const sf::Vector2f& pos,
        float pad,
        const sf::Color& bgColor,
        float outlineThickness
    ) {
        padding = pad;
        button.setFont(font);
        button.setString(buttonText);

        title.setFont(font);
        title.setString(titleText);

        textbox.setFont(font);

        background.setPosition(pos);
        background.setSize(size);
        this->recomputePos();
    }

    void EntryField::recomputePos() {
        sf::Vector2f pos = background.getPosition(), size = background.getSize(), buttonSize = button.getSize();
        float outline = background.getOutlineThickness();

        title.setPosition({pos.x + padding, pos.y + padding});
        textbox.setPosition({pos.x + padding, (pos.y + size.x) - ((textbox.getSize().x) + padding)});
        button.setPosition({
            (pos.x + size.x) - (buttonSize.x + padding),
            (pos.y + size.y) - (buttonSize.y + padding)
        });
    }

    void EntryField::setPosition(const sf::Vector2f& pos) {
        background.setPosition(pos);
        this->recomputePos();
    }

    void EntryField::setPosition(float x, float y) {
        background.setPosition(x, y);
        this->recomputePos();
    }

    void EntryField::setPadding(float pad) {
        padding = pad;
        this->recomputePos();
    }

    void EntryField::setOutlineColor(const sf::Color& color) {background.setOutlineColor(color);}
    void EntryField::setOutlineThickness(float thickness) {background.setOutlineThickness(thickness);}

    sf::Vector2f EntryField::getPosition() {return background.getPosition();}
    sf::Vector2f EntryField::getSize() {return background.getSize();}

    /*bool EntryField::isMouseOver(const sf::Vector2f& mousePos) {
        sf::Vector2f pos = this->getPosition();
        sf::FloatRect bounds = this->getLocalBounds();
        return (sf::FloatRect{pos.x, pos.y, bounds.width, bounds.height}).contains(mousePos);
    }*/
};

#endif