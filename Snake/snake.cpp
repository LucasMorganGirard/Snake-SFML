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
#include "ResourcePath.hpp"
#include <iostream>
#include "food.hpp"

#define snakeHead mSnakeBody[0]

Snake::Snake(const int& x, const int& y, sf::RenderWindow& win)
:mSize(1), mCase(20), mTourner(RIGHT), mNeedNewRect(true), mLastX(20), mLastY(20), mWin(win), mScore(0)
{
    sf::RectangleShape tete;
    tete.setSize(sf::Vector2f(mCase, mCase));
    tete.setFillColor(sf::Color::White);
    tete.setPosition(x, y);
    snakeBloc s(tete,RIGHT);
    mSnakeBody.push_back(s);
    
    if(!mFont.loadFromFile(resourcePath()+"sansation.ttf")){
        return EXIT_FAILURE;
    }
    mText.setFont(mFont);
    mText.setCharacterSize(50);
    mText.setFillColor(sf::Color::Red);
    mText.setString(std::to_string(mScore));
};

void Snake::drawSnake(){
    for (snakeBloc s : mSnakeBody) {
        mWin.draw(s.r);
    }
    mText.setString(std::to_string(mScore));
    mWin.draw(mText);
};

const bool Snake::onCadriage() const{
    return (int)snakeHead.r.getPosition().x % 20 == 0 && (int)snakeHead.r.getPosition().y % 20 == 0;
}

void Snake::move(Food& plate){
    
    for (unsigned i = mSize-1; i > 0; i--) {
        if(onCadriage()){
            mSnakeBody[i].d = mSnakeBody[i-1].d;
        }
        switch (mSnakeBody[i].d) {
            case UP:
                mSnakeBody[i].r.setPosition(mSnakeBody[i].r.getPosition().x, mSnakeBody[i].r.getPosition().y - 4);
                break;
            case DOWN:
                mSnakeBody[i].r.setPosition(mSnakeBody[i].r.getPosition().x, mSnakeBody[i].r.getPosition().y + 4);
                break;
            case LEFT:
                mSnakeBody[i].r.setPosition(mSnakeBody[i].r.getPosition().x - 4, mSnakeBody[i].r.getPosition().y);
                break;
            case RIGHT:
                mSnakeBody[i].r.setPosition(mSnakeBody[i].r.getPosition().x + 4, mSnakeBody[i].r.getPosition().y);
                break;
            default:
                break;
        }
    }
    
    if(onCadriage()){
        snakeHead.d = mTourner;
    }
    
    switch (snakeHead.d) {
        case UP:
            snakeHead.r.setPosition(snakeHead.r.getPosition().x, snakeHead.r.getPosition().y - 4);
            break;
        case DOWN:
            snakeHead.r.setPosition(snakeHead.r.getPosition().x, snakeHead.r.getPosition().y + 4);
            break;
        case LEFT:
            snakeHead.r.setPosition(snakeHead.r.getPosition().x - 4, snakeHead.r.getPosition().y);
            break;
        case RIGHT:
            snakeHead.r.setPosition(snakeHead.r.getPosition().x + 4, snakeHead.r.getPosition().y);
            break;
        default:
            break;
    }
    
    if(onCadriage()){
        for (unsigned i = 1; i < mSize; i++) {
            if(snakeHead.r.getPosition() == mSnakeBody[i].r.getPosition() || snakeHead.r.getPosition().x < 0 || snakeHead.r.getPosition().x > 780 || snakeHead.r.getPosition().y < 0 ||  snakeHead.r.getPosition().y > 780){
                for (unsigned i = 0; i<mSize; i++) {
                    mSnakeBody[i].d = STOP;
                }
            }
        }
    }
    
    if(onCadriage() && mNeedNewRect){
        sf::RectangleShape toAdd = sf::RectangleShape(sf::Vector2f(mCase,mCase));
        toAdd.setPosition(mLastX, mLastY);
        toAdd.setFillColor(sf::Color::White);
        snakeBloc s(toAdd,mSnakeBody.back().d);
        mSnakeBody.push_back(s);
        mNeedNewRect=false;
        mSize++;
    }
    
    for (unsigned i = 0; i < plate.drawFood().size(); i++) {
        if(snakeHead.r.getPosition() == plate.drawFood()[i].getPosition()){
            mNeedNewRect=true;
            plate.getEaten(i);
            mScore++;
        }
    }
    
    if(onCadriage()){
        mLastX = mSnakeBody[mSize-1].r.getPosition().x;
        mLastY = mSnakeBody[mSize-1].r.getPosition().y;
    }
    
}

void Snake::setDir(const direction dir){

    if(snakeHead.d != STOP){
        mTourner=dir;
    }
    switch (mTourner) {
        case UP:
            if(snakeHead.d==DOWN){
                for (unsigned i = 0; i<mSize; i++) {
                    mSnakeBody[i].d = STOP;
                }
            }
            break;
        case DOWN:
            if(snakeHead.d==UP){
                for (unsigned i = 0; i<mSize; i++) {
                    mSnakeBody[i].d = STOP;
                }
            }
            break;
        case LEFT:
            if(snakeHead.d==RIGHT){
                for (unsigned i = 0; i<mSize; i++) {
                    mSnakeBody[i].d = STOP;
                }
            }
            break;
        case RIGHT:
            if(snakeHead.d==LEFT){
                for (unsigned i = 0; i<mSize; i++) {
                    mSnakeBody[i].d = STOP;
                }
            }
            break;
            
            
        default:
            break;
    }
};

