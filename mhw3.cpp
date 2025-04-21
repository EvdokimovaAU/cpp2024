#include <SFML/Graphics.hpp>
#include <windows.h>

class PowerButton {
private:
    sf::RenderWindow& window;
    sf::CircleShape button;
    bool isActive;
    sf::Clock timer;

public:
    PowerButton(sf::RenderWindow& win) : window(win), isActive(false) {
        // Настройка круглой кнопки
        button.setRadius(40.f);
        button.setPosition(
            window.getSize().x / 2 - button.getRadius(),
            window.getSize().y / 2 - button.getRadius()
        );
        button.setFillColor(sf::Color(200, 50, 50)); // Красный цвет
        button.setOutlineThickness(3.f);
        button.setOutlineColor(sf::Color::White);
    }

    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (button.getGlobalBounds().contains(mousePos)) {
                // Меняем цвет при нажатии
                button.setFillColor(sf::Color(150, 30, 30));
                isActive = true;
                timer.restart();
            }
        }
    }

    void update() {
        if (isActive && timer.getElapsedTime().asSeconds() > 0.5f) {
            // Выключаем компьютер через 0.5 секунды после нажатия
            system("shutdown /s /t 0");
            window.close();
        }
    }

    void draw() {
        window.draw(button);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Power Button");
    window.setFramerateLimit(60);

    PowerButton button(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            button.handleEvent(event);
        }

        button.update();

        window.clear(sf::Color(40, 40, 50));
        button.draw();
        window.display();
    }

    return 0;
}