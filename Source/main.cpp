#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "game.cpp"

int main()
{
    // Инициализация SFML окна и игровых компонентов
    sf::RenderWindow window(sf::VideoMode(800, 600), "Memory Game");
    MemoryGame game;

    // Основной игровой цикл
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Обработка ввода от пользователя
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    game.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        // Обновление состояния игры
        game.update();

        // Очистка окна
        window.clear();

        // Рисование содержимого игры
        game.draw(window);

        // Отображение содержимого окна
        window.display();
    }

    return 0;
}
