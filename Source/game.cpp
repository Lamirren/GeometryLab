#include <SFML/Graphics.hpp>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>
#include <iostream>

class Card
{
public:
	bool isFlipped;
	bool isMatched;
	int pairID;
	sf::RectangleShape shape;

	Card(int id) : pairID(id), isFlipped(false), isMatched(false)
	{
		shape.setSize(sf::Vector2f(60, 60));
		shape.setFillColor(sf::Color::White);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1);
	}
};

class MemoryGame
{
private:
	std::vector<Card> cards;
	int selectedCard;
	int secondSelectedCard;
	sf::Clock timer;
	bool isChecking;
	std::vector<sf::Color> matchColors;
	sf::RectangleShape restartButton;
	sf::Font font;
	sf::Text restartText;

public:
	MemoryGame() : selectedCard(-1), secondSelectedCard(-1), isChecking(false)
	{
		// Инициализация кнопки перезапуска
		if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) //шрифты что лежат в папке fonts не работают. Почему? а фиг его знает
		{ 
			std::cerr << "Error loading font from file!" << std::endl;
		}
		restartText.setFont(font);
		restartText.setString("Restart");
		restartText.setCharacterSize(24);
		restartText.setFillColor(sf::Color::Black);

		restartButton.setSize(sf::Vector2f(100, 50));
		/*restartText.setPosition(
			restartButton.getPosition().x + (restartButton.getSize().x - restartText.getLocalBounds().width) / 2,
			restartButton.getPosition().y + (restartButton.getSize().y - restartText.getLocalBounds().height) / 2 - restartText.getLocalBounds().height / 2);*/

		restartButton.setFillColor(sf::Color::White);
		restartButton.setOutlineColor(sf::Color::Black);
		restartButton.setOutlineThickness(2);
		restartButton.setPosition(10, 300); // Задайте нужное положение
		restartText.setPosition(10 + (100 - restartText.getLocalBounds().width) / 2, 300 + (50 - restartText.getLocalBounds().height) / 2);

		initGame();
	}

	void initGame()
	{
		cards.clear();
		int numPairs = 8;
		for (int i = 0; i < numPairs; ++i)
		{
			cards.emplace_back(i);
			cards.emplace_back(i);
		}
		std::random_shuffle(cards.begin(), cards.end());

		for (size_t i = 0; i < cards.size(); ++i)
		{
			cards[i].shape.setPosition(70 * (i % 4) + 10, 70 * (i / 4) + 10);
		}

		matchColors = {sf::Color::Red,	   sf::Color::Green, sf::Color::Blue,		 sf::Color::Yellow,
					   sf::Color::Magenta, sf::Color::Cyan,	 sf::Color(255, 128, 0), sf::Color(128, 0, 128)};
	}

	void handleClick(int x, int y)
	{
		if (restartButton.getGlobalBounds().contains(x, y))
		{
			initGame();
			return;
		}

		if (isChecking)
			return;

		for (size_t i = 0; i < cards.size(); ++i)
		{
			if (cards[i].shape.getGlobalBounds().contains(x, y) && !cards[i].isFlipped)
			{
				cards[i].isFlipped = true;

				if (selectedCard == -1)
				{
					selectedCard = i;
				}
				else if (secondSelectedCard == -1)
				{
					secondSelectedCard = i;
					timer.restart();
					isChecking = true;
				}
				break;
			}
		}
	}

	void update()
	{
		if (isChecking && timer.getElapsedTime().asSeconds() >= 1.0f)
		{
			if (selectedCard != -1 && secondSelectedCard != -1)
			{
				if (cards[selectedCard].pairID != cards[secondSelectedCard].pairID)
				{
					cards[selectedCard].isFlipped = false;
					cards[secondSelectedCard].isFlipped = false;
				}
				else
				{
					cards[selectedCard].isMatched = true;
					cards[secondSelectedCard].isMatched = true;
				}
				selectedCard = -1;
				secondSelectedCard = -1;
				isChecking = false;
			}
			isChecking = false;
		}
	}

	void draw(sf::RenderWindow &window)
	{
		for (auto &card : cards)
		{
			if (!card.isFlipped && !card.isMatched)
			{
				card.shape.setFillColor(sf::Color::White);
			}
			else if (card.isMatched)
			{
				card.shape.setFillColor(matchColors[card.pairID]);
			}
			else
			{
				// Измените цвет на соответствующий цвет из массива matchColors
				card.shape.setFillColor(matchColors[card.pairID]);
			}
			window.draw(card.shape);
		}

		// Отрисовка кнопки перезапуска
		window.draw(restartButton);
		window.draw(restartText);
	}
};
