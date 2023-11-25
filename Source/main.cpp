#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "game.cpp"

int main()
{
    // ������������� SFML ���� � ������� �����������
    sf::RenderWindow window(sf::VideoMode(800, 600), "Memory Game");
    MemoryGame game;

    // �������� ������� ����
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // ��������� ����� �� ������������
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    game.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        // ���������� ��������� ����
        game.update();

        // ������� ����
        window.clear();

        // ��������� ����������� ����
        game.draw(window);

        // ����������� ����������� ����
        window.display();
    }

    return 0;
}
