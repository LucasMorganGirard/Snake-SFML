//
//  snake.cpp
//  Snake
//
//  Created by GIRARD Lucas on 08/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#include "snake.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "food.hpp"

Snake::Snake(const int& x, const int& y)
:mSize(1), mCase(20), mDirection(RIGHT), mTourner(RIGHT), mNeedNewRect(true), mLastX(20), mLastY(20)
{
    sf::RectangleShape tete;
    tete.setSize(sf::Vector2f(mCase, mCase));
    tete.setFillColor(sf::Color::White);
    tete.setPosition(x, y);
    mSnakeBody.push_back(tete);
};

std::vector<sf::RectangleShape>& Snake::drawSnake(){
    return mSnakeBody;
};

const bool Snake::onCadriage() const{
    return (int)mSnakeBody[0].getPosition().x % 20 == 0 && (int)mSnakeBody[0].getPosition().y % 20 == 0;
}

void Snake::move(Food& plate){
    
    if(onCadriage()){
        mDirection = mTourner;
    }
    
    for (unsigned i = mSize-1; i > 0; i--) {
        mSnakeBody[i].setPosition(mSnakeBody[i-1].getPosition().x, mSnakeBody[i-1].getPosition().y);
    }
    
    switch (mDirection) {
        case UP:
            mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x, mSnakeBody[0].getPosition().y - 2);
            break;
        case DOWN:
            mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x, mSnakeBody[0].getPosition().y + 2);
            break;
        case LEFT:
            mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x - 2, mSnakeBody[0].getPosition().y);
            break;
        case RIGHT:
            mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x + 2, mSnakeBody[0].getPosition().y);
            break;
    }
    
    if(onCadriage() && mNeedNewRect){
        sf::RectangleShape toAdd = sf::RectangleShape(sf::Vector2f(mCase,mCase));
        toAdd.setPosition(20, 20);
        toAdd.setFillColor(sf::Color::White);
        mSnakeBody.push_back(toAdd);
        mNeedNewRect=false;
        mSize++;
    }
    
    for (unsigned i = 0; i < plate.drawFood().size(); i++) {
        if(mSnakeBody[0].getPosition() == plate.drawFood()[i].getPosition()){
            mNeedNewRect=true;
            plate.getEaten(i);
        }
    }
    
    if(onCadriage()){
        mLastX = mSnakeBody[mSize-1].getPosition().x;
        mLastY = mSnakeBody[mSize-1].getPosition().y;
    }
    
}

void Snake::setDir(const direction dir){

    mTourner=dir;

};

