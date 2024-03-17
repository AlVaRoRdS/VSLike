#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

int main()
{
    // Create the window
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    // Creates Game Class
    Game* game = new Game();
    game->initGame(window);

    // Creates clock
    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        // Checks if any of the events of the windows closes the window, and then closes it 
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update
        game->updateGame(clock.restart().asMilliseconds());
        // Render
        game->renderGame(window);
    }
    return 0;
}
