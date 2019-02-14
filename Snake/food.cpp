//
//  food.cpp
//  Snake
//
//  Created by GIRARD Lucas on 08/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#include "food.hpp"
#include <math.h>
#include <iostream>
#include <ctime>
#include <random>

Food::Food(sf::RenderWindow& win):mWin(win){};

void Food::drawFood(){
    for (sf::RectangleShape r : mFood) {
        mWin.draw(r);
    }
};

const sf::Vector2f Food::choixPoint(const std::vector<snakeBloc>& snake) const{
    std::random_device generator;
    std::uniform_int_distribution<int> range(1,39);
    int randInt = range(generator);
    float x(randInt*20);
    randInt = range(generator);
    float y(randInt*20);
    bool notOnSnake = true;
    do{
        notOnSnake=true;
        for (snakeBloc s : snake) {
            if(s.r.getPosition().x == x && s.r.getPosition().y == y){
                notOnSnake = false;
            }
        }
        if(!notOnSnake){
            if (x < 780) {
                x += 20;
            }else{
                x = 0;
                if(y < 780){
                    y += 20;
                }else{
                    y = 0;
                }
            }
        }
    }while(!notOnSnake);
    return sf::Vector2f(x,y);
};


void Food::setUpFood(const unsigned numberOfFood, const std::vector<snakeBloc>& posSnake){
    for(unsigned i = 0; i < numberOfFood; i++){
        sf::RectangleShape toAdd = sf::RectangleShape(sf::Vector2f(20.f,20.f));
        toAdd.setPosition(choixPoint(posSnake));
        toAdd.setFillColor(sf::Color::Red);
        mFood.push_back(toAdd);
    }
};

void Food::getEaten(const unsigned i, const std::vector<snakeBloc>& posSnake){
    sf::RectangleShape toAdd = sf::RectangleShape(sf::Vector2f(20.f,20.f));
    toAdd.setPosition(choixPoint(posSnake));
    toAdd.setFillColor(sf::Color::Red);
    mFood[i] = toAdd;
};

const std::vector<sf::RectangleShape>& Food::getFood() const{
    return mFood;
};

