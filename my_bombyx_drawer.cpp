/*
** 2023
** 106bombyx drawer
** File description:
** math project, own graphique generator
** comes with bombyx_cpp
*/

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>

std::vector<sf::Vector2f> data_manager()
{
    float x = 0;
    float y = 0;
    std::vector<sf::Vector2f> points;

    std::ifstream inputFile("data");
    if (!inputFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return points;
    }
    while (inputFile >> x >> y)
        points.push_back(sf::Vector2f(x, y));
    inputFile.close();
    return points;
}

int tab_creator(sf::RenderWindow& window, const std::vector<sf::Vector2f>& points)
{
    float y_max = 0;
    std::vector<sf::CircleShape> circles;

    if (points.empty())
        return 84;
    for (const auto& point : points) {
        if (point.y > y_max)
            y_max = point.y;
    }
    y_max = std::ceil(y_max);
    for (const auto& point : points) {
        float yPos = (point.y / y_max) * (window.getSize().y - 100) + 50;
        float xPos = ((point.x - 1) / 3) * (window.getSize().x - 100) + 50;
        sf::CircleShape circle(2);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(xPos, window.getSize().y - yPos);
        circles.push_back(circle);
    }
    for (const auto& circle : circles)
        window.draw(circle);
    return 0;
}

void y_axis_drawer(sf::RenderWindow& window, float maxY)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
        return;
    }
    //axe Y
    sf::VertexArray y_axis(sf::Lines, 2);
    y_axis[0].position = sf::Vector2f(50.0f, 50.0f);
    y_axis[1].position = sf::Vector2f(50.0f, window.getSize().y - 50);
    window.draw(y_axis);

    //gradutations Y
    for (int i = 0; i <= maxY; i += 100) {
        sf::Text label;
        label.setFont(font);
        label.setString(std::to_string(i));
        label.setCharacterSize(12);
        label.setFillColor(sf::Color::White);
        label.setPosition(25.0f, window.getSize().y - 50 - (i * (window.getSize().y - 80) / maxY));
        window.draw(label);
    }
}

void x_axis_drawer(sf::RenderWindow& window)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
        return;
    }
    //axe X
    sf::VertexArray x_axis(sf::Lines, 2);
    x_axis[0].position = sf::Vector2f(50.0f, window.getSize().y - 50);
    x_axis[1].position = sf::Vector2f(window.getSize().x - 50, window.getSize().y - 50);
    window.draw(x_axis);

    //graduations X
    for (int i = 1; i <= 3; i++) {
        sf::Text label;
        label.setFont(font);
        label.setString(std::to_string(i));
        label.setCharacterSize(12);
        label.setFillColor(sf::Color::White);
        label.setPosition(50 + i * ((window.getSize().x - 100) / 3), window.getSize().y - 25);
        window.draw(label);
    }

}

int window_creator()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphique de Points");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        std::vector<sf::Vector2f> points = data_manager();
        if (points.empty())
            return 84;
        float maxY = 0;
        for (const auto& point : points) {
            if (point.y > maxY)
                maxY = point.y;
        }
        maxY = std::ceil(maxY);
        if (tab_creator(window, points) == 84)
            return 84;
        y_axis_drawer(window, maxY);
        x_axis_drawer(window);
        window.display();
    }
    return 0;
}

int main()
{
    if (window_creator() == 84)
        return 84;
    return 0;
}
