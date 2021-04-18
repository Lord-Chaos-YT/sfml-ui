#ifndef TABLE_HPP
#define TABLE_HPP

#include <SFML/Graphics.hpp>
#include "multielements.hpp"
#include "concrete_h.hpp"
#include "background.hpp"
#include <table_h.hpp>

namespace UI {
    template<class BackgroundType> Table<BackgroundType>::Table(
        const std::vector<std::vector<MultiElement<BackgroundType>>>& initElems, const sf::Vector2f& size, const sf::Vector2f& innerPad, const sf::Vector2f& outerPad
    ) : elements{initElems}, defDim{defD}, innerPadding{innerPad}, outerPadding{outerPad} {
        if (!std::is_base_of<sf::RectangleType, BackgroundType>::value) throw "Invalid type specifier. Type must inherit from class sf::RectangleShape!";
        this->recomputeSizes();
    }

    template<class BackgroundType> void Table<BackgroundType>::recomputePos() {
        sf::Vector2f pos = background.getPosition() + outerPadding;
        for (std::size_t i = 0u; i < elements.size(); i++)
            for (std::size_t j = 0u, g = 0u; j < elements[i].size(); j++, g += elements[i][j].getGridSpace().y)
                elements[i][j].setPosition(pos + {(calcedElementSize.x * (float)i) + ((float)(i - 1u) * innerPadding.x), (calcedElementSize.y * (float)g) + ((float)(g - 1u) * innerPadding.y)});
    }

    template<class BackgroundType> void Table<BackgroundType>::recomputeSizes() {
        calcedGridSize = {elements.size(), 0u};
        for (auto& column : elements) {
            std::size_t temp = 0u;
            for (MultiElement<BackgroundType>& element : column) temp += element.getGridSpace().y;
            if (temp > calcedGridSize.y) calcedGridSize.y = temp;
        }
        calcedElementSize = background.getSize() - {(innerPadding.x * (float)(calcedGridSize.x - 1u)) + (outerPadding.x * 2.f), (innerPadding.y * (float)(calcedGridSize.y - 1u)) + (outerPadding.y * 2.f)};
        calcedElementSize.x = calcedElementSize.x / calcedGridSize.x;
        calcedElementSize.y = calcedElementSize.y / calcedGridSize.y;
        for (std::vector<MultiElement<BackgroundType>>& column : elements) for (MultiElement<BackgroundType>& element : column) {
            element.setPadding(innerPadding);
            element.setSize(calcedElementSize);
        }
        this->recomputePos();
    }

    template<class BackgroundType> void Table<BackgroundType>::setPosition(const sf::Vector2f& pos) {
        background.setPosition(pos);
        this->recomputePos();
    }

    template<class BackgroundType> void Table<BackgroundType>::setSize(const sf::Vector2f& size) {
        background.setSize(size);
        this->recomputeSizes();
    }

    template<class BackgroundType> void Table<BackgroundType>::setAllElements(const std::vector<std::vector<MultiElement<BackgroundType>>>& elems) {
        elements = elems;
        this->recomputeSizes();
    }

    template<class BackgroundType> void Table<BackgroundType>::insert(const MultiElement<BackgroundType>& inserted, const sf::Vector2u& place, bool lockY) {
        if (place.x > elements.size()) elements.push_back({inserted});
        else if (lockY && !place.y) elements.insert(place.x, 1, {inserted});
        else elements[place.x].insert(place.y, 1, inserted);
        this->recomputeSizes();
    }

    template<class BackgroundType> void Table<BackgroundType>::erase(const sf::Vector2u& place) {
        if (!place.y && [place.x].size() == 1) elements.erase(place.x);
        else elements[place.x].erase(place.y);
        this->recomputeSizes();
    }

    template<class BackgroundType> void Table<BackgroundType>::replaceElement(const MultiElement<BackgroundType>& replaced, sf::Vector2u place) {
        if (place.x == -1u) place.x = elements.size() - 1;
        if (place.y == -1u) place.y = elements.at(0).size() - 1;
        sf::Vector2u gridSpaceCurrent = elements.at(place.x).at(place.y).getGridSpace(), gridSpaceReplaced = replaced.getGridSpace();
        elements[place.x][place.y] = replaced;
        if (gridSpaceCurrent.x < gridSpaceReplaced.x) {
            if (place.x + gridSpaceReplaced.x < elements.size()) ;
        }
        this->recomputeSizes();
    }

    template<class BackgroundType> const std::vector<const std::vector<const MultiElement<BackgroundType>>>& Table<BackgroundType>::getElements() const {return elements;}
    template<class BackgroundType> sf::Vector2f Table<BackgroundType>::getPosition() const {return background.getPosition();}
    template<class BackgroundType> sf::Vector2f Table<BackgroundType>::getSize() const {return background.getSize();}
    
    template<class BackgroundType> sf::Vector2u Table<BackgroundType>::getTableSize() const {return calcedGridDim;}
};

#endif