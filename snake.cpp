#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

const float paddleWidth = 25.f;
const float paddleHeight = 100.f;
const float ballRadius = 10.f;
const float paddleSpeed = 400.f;
const float ballSpeed = 400.f;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    sf::RectangleShape leftPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    leftPaddle.setFillColor(sf::Color::Green);
    leftPaddle.setPosition(50.f, window.getSize().y / 2 - paddleHeight / 2);

    sf::RectangleShape rightPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    rightPaddle.setFillColor(sf::Color::Red);
    rightPaddle.setPosition(window.getSize().x - 50.f - paddleWidth, window.getSize().y / 2 - paddleHeight / 2);

    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(window.getSize().x / 2 - ballRadius, window.getSize().y / 2 - ballRadius);

    sf::Vector2f ballVelocity(-ballSpeed, -ballSpeed);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Paddle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0) {
            leftPaddle.move(0.f, -paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + paddleHeight < window.getSize().y) {
            leftPaddle.move(0.f, paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0) {
            rightPaddle.move(0.f, -paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + paddleHeight < window.getSize().y) {
            rightPaddle.move(0.f, paddleSpeed * deltaTime);
        }

        // Ball movement
        ball.move(ballVelocity * deltaTime);

        // Ball collision with top and bottom
        if (ball.getPosition().y <= 0 || ball.getPosition().y + 2 * ballRadius >= window.getSize().y) {
            ballVelocity.y = -ballVelocity.y;
        }

        // Ball collision with paddles
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballVelocity.x = -ballVelocity.x;
        }

        // Ball reset if it goes out of bounds
        if (ball.getPosition().x <= 0 || ball.getPosition().x + 2 * ballRadius >= window.getSize().x) {
            ball.setPosition(window.getSize().x / 2 - ballRadius, window.getSize().y / 2 - ballRadius);
            ballVelocity = sf::Vector2f(-ballSpeed, -ballSpeed);
        }

        window.clear();
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}

