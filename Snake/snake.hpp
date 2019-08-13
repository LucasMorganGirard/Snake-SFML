//
//  snake.hpp
//  Snake
//
//  Created by GIRARD Lucas on 08/02/2019.
//

#ifndef snake_hpp
#define snake_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "food.hpp"

class Snake{
public:
    Snake(sf::RenderWindow&);
    void drawSnake();
    const bool onCadriage() const;
    const bool move(Food&);
    void setDir(const direction);
    void setup();
    std::vector<snakeBloc>& getBody();
    const unsigned short getScore() const;
    
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
    sf::Text mDeath;
    sf::Font mFont;
    unsigned short mOpacite;
    unsigned short mScore;
};

#endif /* snake_hpp */
