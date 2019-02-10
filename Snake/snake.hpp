//
//  snake.hpp
//  Snake
//
//  Created by GIRARD Lucas on 08/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#ifndef snake_hpp
#define snake_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "food.hpp"

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
} direction;

typedef struct snakeBloc {
    snakeBloc(sf::RectangleShape rect, direction direc):r(rect),d(direc){};
    sf::RectangleShape r;
    direction d;
} snakeBloc;

class Snake{
public:
    Snake(const int&, const int&, sf::RenderWindow&);
    void drawSnake();
    const bool onCadriage() const;
    void move(Food&);
    void setDir(const direction);
    
private:
    std::vector<snakeBloc> mSnakeBody;
    unsigned mSize;
    const unsigned mCase;
    direction mTourner;
    bool mNeedNewRect;
    unsigned mLastX;
    unsigned mLastY;
    sf::RenderWindow& mWin;
    sf::Text mText;
    sf::Font mFont;
    unsigned short mScore;
};

#endif /* snake_hpp */
