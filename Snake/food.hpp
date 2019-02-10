//
//  food.hpp
//  Snake
//
//  Created by GIRARD Lucas on 08/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#ifndef food_hpp
#define food_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Food{
public:
    Food();
    std::vector<sf::RectangleShape>& drawFood();
    void setUpFood(const unsigned numberOfFood);
    void getEaten(const unsigned);
    
private:
    std::vector<sf::RectangleShape> mFood;
};

#endif /* food_hpp */
