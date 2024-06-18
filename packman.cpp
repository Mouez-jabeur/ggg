#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

using namespace std;

// Constants
const int tileSize = 24;
const int numRows = 21;
const int numCols = 21;
const int windowWidth = numCols * tileSize;
const int windowHeight = numRows * tileSize;
const float speed = 100.0f;

// Directions
enum Direction { STOP, LEFT, RIGHT, UP, DOWN };

// Map layout
const int map[numRows][numCols] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1},
    {1,0,1,1,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,1,1},
    {1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1},
    {1,0,1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1},
    {1,0,0,0,0,0,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1},
    {1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
    {1,0,1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1},
    {1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1},
    {1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1},
    {1,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Check collision with walls
bool checkCollision(int x, int y) {
    int row = y / tileSize;
    int col = x / tileSize;
    return map[row][col] == 1;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pac-Man");

    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    sf::CircleShape pacman(tileSize / 2 - 2);
    pacman.setFillColor(sf::Color::Yellow);

    // Set Pac-Man's initial position
    sf::Vector2f pacmanPos(windowWidth / 2, windowHeight / 2);
    Direction dir = STOP;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    dir = LEFT;
                    break;
                case sf::Keyboard::Right:
                    dir = RIGHT;
                    break;
                case sf::Keyboard::Up:
                    dir = UP;
                    break;
                case sf::Keyboard::Down:
                    dir = DOWN;
                    break;
                default:
                    break;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        sf::Vector2f movement(0.f, 0.f);

        switch (dir) {
        case LEFT:
            movement.x -= speed * deltaTime;
            break;
        case RIGHT:
            movement.x += speed * deltaTime;
            break;
        case UP:
            movement.y -= speed * deltaTime;
            break;
        case DOWN:
            movement.y += speed * deltaTime;
            break;
        default:
            break;
        }

        // Check collision
        if (!checkCollision(pacmanPos.x + movement.x, pacmanPos.y + movement.y)) {
            pacmanPos += movement;
        }

        window.clear();

        // Draw the map
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                if (map[row][col] == 1) {
                    tile.setFillColor(sf::Color::Blue);
                } else {
                    tile.setFillColor(sf::Color::Black);
                }
                tile.setPosition(col * tileSize, row * tileSize);
                window.draw(tile);
            }
        }

        // Draw Pac-Man
        pacman.setPosition(pacmanPos);
        window.draw(pacman);

        window.display();
    }

    return 0;
}

