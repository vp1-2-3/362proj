#include <SFML/Graphics.hpp>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML Calculator");
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text displayText("", font, 40);
    displayText.setPosition(50, 50);

    // Create buttons for digits 0-9
    sf::RectangleShape digitButtons[10];
    sf::Text digitText[10];

    for (int i = 0; i < 10; ++i) {
        digitButtons[i].setSize(sf::Vector2f(80, 80));
        digitButtons[i].setFillColor(sf::Color::White);
        digitButtons[i].setPosition(15 + (i % 3) * 100, 200 + (i / 3) * 100);

        digitText[i].setFillColor(sf::Color::Black);
        digitText[i].setFont(font);
        digitText[i].setCharacterSize(40);
        digitText[i].setString(std::to_string(i)); // Set numbers on buttons
        digitText[i].setPosition(25 + (i % 3) * 100, 225 + (i / 3) * 100);
    }

    // Create operator buttons
    sf::RectangleShape addButton(sf::Vector2f(80, 80));
    addButton.setFillColor(sf::Color::Blue);
    addButton.setPosition(10 + 3 * 100, 200);
    sf::Text addText("+", font, 40);
    addText.setPosition(75 + 3 * 90, 225);

    sf::RectangleShape subtractButton(sf::Vector2f(80, 80));
    subtractButton.setFillColor(sf::Color::Blue);
    subtractButton.setPosition(10 + 3 * 100, 300);
    sf::Text subtractText("-", font, 40);
    subtractText.setPosition(75 + 3 * 90, 325);

    sf::RectangleShape multiplyButton(sf::Vector2f(80, 80));
    multiplyButton.setFillColor(sf::Color::Blue);
    multiplyButton.setPosition(10 + 3 * 100, 400);
    sf::Text multiplyText("x", font, 40);
    multiplyText.setPosition(75 + 3 * 90, 425);

    sf::RectangleShape divideButton(sf::Vector2f(80, 80));
    divideButton.setFillColor(sf::Color::Blue);
    divideButton.setPosition(10 + 3 * 100, 500);
    sf::Text divideText("/", font, 40);
    divideText.setPosition(75 + 3 * 90, 525);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < 10; ++i) {
                    if (digitButtons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        displayText.setString(displayText.getString() + std::to_string(i));
                    }
                }

                if (addButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "+");
                }
                else if (subtractButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "-");
                }
                else if (multiplyButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "x");
                }
                else if (divideButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "/");
                }
            }
        }

        window.clear();
        window.draw(displayText);

        for (int i = 0; i < 10; ++i) {
            window.draw(digitButtons[i]);
            window.draw(digitText[i]); // Display numbers on buttons
        }

        window.draw(addButton);
        window.draw(addText);
        window.draw(subtractButton);
        window.draw(subtractText);
        window.draw(multiplyButton);
        window.draw(multiplyText);
        window.draw(divideButton);
        window.draw(divideText);

        window.display();
    }

    return 0;
}
