#include <SFML/Graphics.hpp>
#include <vector>
#include<stdlib.h>
#include<cstdlib>
#include<time.h>
#include<ctime>
#include<iostream>

using namespace std;

#pragma region variables
int rectanglesMaximumNumber = 100;
int window_height = 600;
int window_width = 800;
vector<sf::RectangleShape> rectangles;
#pragma endregion variables

int random(int minimum, int maximum) {

	static bool first = true;
	if (first) {
		srand((unsigned int)time(NULL));
		first = false;
	}
	int randomNumber = minimum + (int)(rand() % (maximum - minimum + 1));
	return randomNumber;
}

sf::Color colorRectangle(int ColorProbability) {
	int nb_alea = random(0, 100);
	if (nb_alea < ColorProbability) {
		int numeroCouleur = random(1, 3);
		switch (numeroCouleur)
		{
		case(1):
			return sf::Color::Blue;
			break;
		case(2):
			return sf::Color::Red;
			break;
		case(3):
			return sf::Color::Yellow;
			break;
		}
	}
	return sf::Color::White;
}

void initializeRectangleList() {

	rectangles.clear();
	sf::RectangleShape rectangle(sf::Vector2f((float)window_width - 2, (float)window_height - 2));
	rectangle.setFillColor(sf::Color(255, 255, 255));
	rectangle.setPosition(sf::Vector2f(1, 1));
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color(0, 0, 0));
	rectangles.push_back(rectangle);
}

void split(sf::RectangleShape selectedRectangle, int index, int colorProbability) {

	sf::Vector2f size = selectedRectangle.getSize();
	sf::Vector2f position = selectedRectangle.getPosition();
	int axis = random(1, 2);
	switch (axis)
	{
	case(1):
		if (size.x - 30 >= 0) {
			int x_cut = 15 + random(0, (int)size.x - 30);
			sf::RectangleShape rectangle1(sf::Vector2f((float)x_cut - 1, size.y));
			sf::RectangleShape rectangle2(sf::Vector2f(size.x - x_cut, size.y));
			rectangle1.setPosition(sf::Vector2f(position.x, position.y));
			rectangle2.setPosition(sf::Vector2f(position.x + x_cut, position.y));
			rectangle1.setOutlineThickness(1);
			rectangle2.setOutlineThickness(1);
			colorRectangle(colorProbability);
			rectangle1.setFillColor(colorRectangle(colorProbability));
			rectangle2.setFillColor(colorRectangle(colorProbability));
			rectangle1.setOutlineColor(sf::Color(0, 0, 0));
			rectangle2.setOutlineColor(sf::Color(0, 0, 0));
			rectangles.erase(rectangles.begin() + index);
			rectangles.push_back(rectangle1);
			rectangles.push_back(rectangle2);
		}
		break;
	case(2):
		if (size.y - 30 >= 0) {
			int y_cut = 15 + random(0, (int)size.y - 30);
			sf::RectangleShape rectangle1(sf::Vector2f(size.x, (float)y_cut - 1));
			sf::RectangleShape rectangle2(sf::Vector2f(size.x, size.y - y_cut));
			rectangle1.setPosition(sf::Vector2f(position.x, position.y));
			rectangle2.setPosition(sf::Vector2f(position.x, position.y + y_cut));
			rectangle1.setOutlineThickness(1);
			rectangle2.setOutlineThickness(1);
			rectangle1.setFillColor(colorRectangle(colorProbability));
			rectangle2.setFillColor(colorRectangle(colorProbability));
			rectangle1.setOutlineColor(sf::Color(0, 0, 0));
			rectangle2.setOutlineColor(sf::Color(0, 0, 0));
			rectangles.erase(rectangles.begin() + index);
			rectangles.push_back(rectangle1);
			rectangles.push_back(rectangle2);
		}
		break;
	}
}

void generateRectangleList() {

	int rectanglesLimitNumber = random(2, rectanglesMaximumNumber);
	int colorProbability = random(0, 100);
	initializeRectangleList();
	int iteration = 0;
	while (iteration < rectanglesLimitNumber)
	{
		int selector = random(0, rectangles.size() - 1);
		sf::RectangleShape rectangleSelected = rectangles[selector];
		split(rectangleSelected, selector, colorProbability);
		iteration += 1;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Masterpiece");

	generateRectangleList();
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if(event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Space) {
					generateRectangleList();
				}
			}
		}

		for (unsigned int i = 0; i < rectangles.size(); i++)
		{
			window.draw(rectangles[i]);
		}
	
		window.display();
		window.clear();
	}

	return 0;
} 