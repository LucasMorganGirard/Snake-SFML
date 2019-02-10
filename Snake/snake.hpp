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
    RIGHT
} direction;

class Snake{
public:
    Snake(const int&, const int&);
    std::vector<sf::RectangleShape>& drawSnake();
    const bool onCadriage() const;
    void move(Food&);
    void setDir(const direction);
    
private:
    std::vector<sf::RectangleShape> mSnakeBody;
    unsigned mSize;
    const unsigned mCase;
    direction mDirection;
    direction mTourner;
    bool mNeedNewRect;
    unsigned mLastX;
    unsigned mLastY;
};

#endif /* snake_hpp */
