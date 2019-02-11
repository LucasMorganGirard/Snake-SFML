
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "snake.hpp"
#include "food.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window", sf::Style::None);
    Snake sss(window);
    Food plate;
    plate.setUpFood(2);
    sf::VertexArray grille;
    grille.setPrimitiveType(sf::Lines);
    for(unsigned i = 20; i < 800; i+=20){
        grille.append(sf::Vertex(sf::Vector2f(i,0), sf::Color(100,100,100)));
        grille.append(sf::Vertex(sf::Vector2f(i,800), sf::Color(100,100,100)));
        grille.append(sf::Vertex(sf::Vector2f(0,i), sf::Color(100,100,100)));
        grille.append(sf::Vertex(sf::Vector2f(800,i), sf::Color(100,100,100)));
    }
    
    sf::Font font;
    if(!font.loadFromFile(resourcePath()+"sansation.ttf")){
        return EXIT_FAILURE;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setPosition(320, 300);
    text.setString("PAUSE");
    
    bool pause=false;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        
        window.setFramerateLimit(60);
        
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                sss.setDir(UP);
            }else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                sss.setDir(DOWN);
            }else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                sss.setDir(LEFT);
            }else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                sss.setDir(RIGHT);
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                pause=!pause;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                sss.setup();
            }
            
        }

        // Clear screen
        window.clear();
        if(!pause){
            if(!sss.move(plate)){
                sss.setup();
            }
        }else{
            window.draw(text);
        }
        for (sf::RectangleShape r1 : plate.drawFood()) {
            window.draw(r1);
        }
        sss.drawSnake();
        window.draw(grille);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
