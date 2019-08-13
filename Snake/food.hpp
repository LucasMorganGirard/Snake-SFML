//
//  food.hpp
//  Snake
//
//  Created by GIRARD Lucas on 08/02/2019.
//

#ifndef food_hpp
#define food_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

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

class Food{
public:
    Food(sf::RenderWindow&);
    void drawFood();
    void setUpFood(const unsigned numberOfFood, const std::vector<snakeBloc>&);
    void getEaten(const unsigned, const std::vector<snakeBloc>&);
    const sf::Vector2f choixPoint(const std::vector<snakeBloc>&) const;
    const std::vector<sf::RectangleShape>& getFood() const;
    
private:
    std::vector<sf::RectangleShape> mFood;
    sf::RenderWindow& mWin;
};

#endif /* food_hpp */
