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

Snake::Snake(sf::RenderWindow& win)
:mSize(3), mCase(20), mTourner(RIGHT), mNeedNewRect(false), mLastX(0), mLastY(0), mWin(win), mScore(0)
{
    setup();
    
    if(!mFont.loadFromFile(resourcePath()+"sansation.ttf")){
        return EXIT_FAILURE;
    }
    mText.setFont(mFont);
    mText.setCharacterSize(50);
    mText.setFillColor(sf::Color::Red);
    mText.setString(std::to_string(mScore));
    
    mOpacite=0;
    mDeath.setFont(mFont);
    mDeath.setCharacterSize(50);
    mDeath.setFillColor(sf::Color(255,0,0,mOpacite));
    mDeath.setString("YOU DIED");
    mDeath.setPosition(270, 300);
};

void Snake::setup(){
    int x(40);
    int y(40);
    mLastX=0;
    mLastY=0;
    mTourner=RIGHT;
    mSnakeBody.clear();
    sf::RectangleShape tete, coup, coup2;
    tete.setSize(sf::Vector2f(mCase, mCase));
    tete.setFillColor(sf::Color::White);
    tete.setPosition(x, y);
    snakeBloc s(tete,RIGHT);
    coup.setSize(sf::Vector2f(mCase, mCase));
    coup.setFillColor(sf::Color::White);
    coup.setPosition(x-mCase, y);
    snakeBloc s2(coup,RIGHT);
    coup2.setSize(sf::Vector2f(mCase, mCase));
    coup2.setFillColor(sf::Color::White);
    coup2.setPosition(x-mCase*2, y);
    snakeBloc s3(coup2,RIGHT);
    mSnakeBody.push_back(s);
    mSnakeBody.push_back(s2);
    mSnakeBody.push_back(s3);
    mSize=3;
    mScore=0;
}


void Snake::drawSnake(){
    for (snakeBloc s : mSnakeBody) {
        mWin.draw(s.r);
    }
    mText.setString(std::to_string(mScore));
    mWin.draw(mText);
    if(mOpacite>0){
        mDeath.setFillColor(sf::Color(255,0,0,mOpacite));
        mOpacite -= 2;
    }
    mWin.draw(mDeath);
};

const bool Snake::onCadriage() const{
    return (int)snakeHead.r.getPosition().x % 20 == 0 && (int)snakeHead.r.getPosition().y % 20 == 0;
}

const bool Snake::move(Food& plate){
    
    bool vivant=true;
    
    for (unsigned i = mSize-1; i > 0; i--) {
        if(onCadriage() && snakeHead.d != STOP){
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
    
    if(onCadriage() && snakeHead.d != STOP){
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
                    vivant=false;
                    mOpacite = 200;
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
    
    return vivant;
    
}

void Snake::setDir(const direction dir){

    if(snakeHead.d != STOP){
        mTourner=dir;
    }
};

