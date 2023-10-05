#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <ctype.h>
//#include <bits/stdc++.h> 
int main() {
    std::string fast, last;// Res;
    int operand1, operand2, operators;
    float answer;
    
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

    sf::RectangleShape clearButton(sf::Vector2f(80,80));
    clearButton.setFillColor(sf::Color::Blue);
    clearButton.setPosition(10 + 2 * 100 , 500);
    sf::Text clearText("C", font, 40);
    clearText.setPosition(75 + 2 * 90 ,525);

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
    
    sf::RectangleShape equalsButton(sf::Vector2f(80,80));
    equalsButton.setFillColor(sf::Color::Blue);
    equalsButton.setPosition(10 + 4 * 100 , 200);
    sf::Text equalsText("=", font, 40);
    equalsText.setPosition(75 + 4 * 90 ,225);

    sf::RectangleShape exponentButton(sf::Vector2f(80,80));
    exponentButton.setFillColor(sf::Color::Blue);
    exponentButton.setPosition(10 + 4 * 100, 300);
    sf::Text exponentText("^", font, 40);
    exponentText.setPosition(75 + 4 * 90 ,325);

    sf::RectangleShape logButton(sf::Vector2f(80,80));
    logButton.setFillColor(sf::Color::Blue);
    logButton.setPosition(10 + 4 * 100, 400);
    sf::Text logText("lg", font, 40);
    logText.setPosition(75 + 4 *90 ,425);

    sf::RectangleShape modButton(sf::Vector2f(80,80));
    modButton.setFillColor(sf::Color::Blue);
    modButton.setPosition(10 + 4 * 100, 500);
    sf::Text modText("%", font, 40);
    modText.setPosition(75 + 4 * 90 ,525);

    sf::RectangleShape sinButton(sf::Vector2f(80,80));
    sinButton.setFillColor(sf::Color::Blue);
    sinButton.setPosition(10 + 5 * 100 , 200);
    sf::Text sinText("sin", font, 40);
    sinText.setPosition(75 + 5 * 90 ,225);

    sf::RectangleShape cosButton(sf::Vector2f(80,80));
    cosButton.setFillColor(sf::Color::Blue);
    cosButton.setPosition(10 + 5 * 100 , 300);
    sf::Text cosText("cos", font, 40);
    cosText.setPosition(75 + 5 * 90 ,325);

    sf::RectangleShape tanButton(sf::Vector2f(80,80));
    tanButton.setFillColor(sf::Color::Blue);
    tanButton.setPosition(10 + 5 * 100 , 400);
    sf::Text tanText("tan", font, 40);
    tanText.setPosition(75 + 5 * 90 ,425);

    sf::RectangleShape piButton(sf::Vector2f(80,80));
    piButton.setFillColor(sf::Color::Blue);
    piButton.setPosition(10 + 5 * 100 , 500);
    sf::Text piText("pi", font, 40);
    piText.setPosition(75 + 5 * 90 ,525);

    std::vector<std::string> input_history; //change to vector

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
                        displayText.setString(std::to_string(i));
                    }
                }

                if (addButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    fast = displayText.getString();
                    operand1 = stoi(fast);
                    operators = 1;
                    displayText.setString("0");

                }
                else if (subtractButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    fast = displayText.getString();
                    operand1 = stoi(fast);
                    operators = 2;
                    //displayText.setString(displayText.getString() + "-");
                }
                else if (multiplyButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "x");
                }
                else if (divideButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "/");
                }
                else if (equalsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    last = displayText.getString();
                    operand2 = stoi(last);
                    switch (operators){
                    case 1:
                        answer = float(operand1) + float(operand2);
                        displayText.setString(std::to_string(answer));
                        break;
                    case 2:
                        answer = float(operand1) - float(operand2);
                        displayText.setString(std::to_string(answer));
                        break;
                    }
                    //displayText.setString(displayText.getString() + "=");
                    //operand_1 = displayText.getString();
                }
                else if (modButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "%");

                }
                else if (exponentButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "^");
                }
                else if (logButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "log");
                }
                else if (sinButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "sin");
                }
                else if (cosButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "cos");
                }
                else if (tanButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "tan");
                }
                else if (piButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString(displayText.getString() + "pi");

                }
                else if (clearButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    displayText.setString("");
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
        window.draw(equalsButton);
        window.draw(equalsText);
        window.draw(exponentButton);
        window.draw(exponentText);
        window.draw(modButton);
        window.draw(modText);
        window.draw(logButton);
        window.draw(logText);
        window.draw(sinButton);
        window.draw(sinText);
        window.draw(cosButton);
        window.draw(cosText);
        window.draw(tanButton);
        window.draw(tanText);
        window.draw(piButton);
        window.draw(piText);
        window.draw(clearButton);
        window.draw(clearText);
        window.display();
    }

    return 0;
}
