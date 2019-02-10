//
//  food.cpp
//  Snake
//
//  Created by GIRARD Lucas on 08/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#include "food.hpp"
#include <stdio.h>
#include <math.h>

Food::Food(){};

std::vector<sf::RectangleShape>& Food::drawFood(){
    return mFood;
};

void Food::setUpFood(const unsigned numberOfFood){
    for(unsigned i = 0; i < numberOfFood; i++){
        sf::RectangleShape toAdd = sf::RectangleShape(sf::Vector2f(20.f,20.f));
        toAdd.setPosition(fmod(rand(),39)*20, fmod(rand(),39)*20);
        toAdd.setFillColor(sf::Color::Red);
        mFood.push_back(toAdd);
    }
};

void Food::getEaten(const unsigned i){
    sf::RectangleShape toAdd = sf::RectangleShape(sf::Vector2f(20.f,20.f));
    toAdd.setPosition(fmod(rand(),39)*20, fmod(rand(),39)*20);
    toAdd.setFillColor(sf::Color::Red);
    mFood[i]=toAdd;
};
