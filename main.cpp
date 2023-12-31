#include "LinearHash.h"
#include "tester.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename K, typename V>
class LinearHashVisualizer {
private:
    LinearHash<K, V>& linearHash;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text closeButton;
    sf::Text inputLabel;
    sf::RectangleShape inputBox;
    sf::Text keyInputLabel;
    sf::RectangleShape keyInputBox;
    sf::Text keyInputText;
    sf::Text valueInputLabel;
    sf::RectangleShape valueInputBox;
    sf::Text valueInputText;
    sf::Text insertButton;
    bool isKeyInputActive = true;

    // Tamaño máximo del cubo antes de reducir
    const int maxBucketWidth = 200;
    const int maxBucketHeight = 80;

public:
    LinearHashVisualizer(LinearHash<K, V>& linearHash) : linearHash(linearHash) {
        // Configurar ventana en pantalla completa
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.create(desktop, "Linear Hash Table Visualization", sf::Style::Fullscreen);

        if (!font.loadFromFile("../arial.ttf")) {
            // handle font loading error
        }

        closeButton.setFont(font);
        closeButton.setString("Close");
        closeButton.setCharacterSize(16);
        closeButton.setFillColor(sf::Color::Black);
        closeButton.setPosition(10, window.getSize().y - 30);

        keyInputLabel.setFont(font);
        keyInputLabel.setString("Key:");
        keyInputLabel.setCharacterSize(16);
        keyInputLabel.setFillColor(sf::Color::Black);
        keyInputLabel.setPosition(10, window.getSize().y - 120);

        keyInputBox.setSize(sf::Vector2f(100, 20));
        keyInputBox.setOutlineColor(sf::Color::Black);
        keyInputBox.setOutlineThickness(2);
        keyInputBox.setPosition(50, window.getSize().y - 125);

        keyInputText.setFont(font);
        keyInputText.setCharacterSize(16);
        keyInputText.setFillColor(sf::Color::Black);
        keyInputText.setPosition(55, window.getSize().y - 123);

        valueInputLabel.setFont(font);
        valueInputLabel.setString("Value:");
        valueInputLabel.setCharacterSize(16);
        valueInputLabel.setFillColor(sf::Color::Black);
        valueInputLabel.setPosition(160, window.getSize().y - 120);

        valueInputBox.setSize(sf::Vector2f(100, 20));
        valueInputBox.setOutlineColor(sf::Color::Black);
        valueInputBox.setOutlineThickness(2);
        valueInputBox.setPosition(220, window.getSize().y - 125);

        valueInputText.setFont(font);
        valueInputText.setCharacterSize(16);
        valueInputText.setFillColor(sf::Color::Black);
        valueInputText.setPosition(225, window.getSize().y - 123);

        insertButton.setFont(font);
        insertButton.setString("Insert");
        insertButton.setCharacterSize(16);
        insertButton.setFillColor(sf::Color::Black);
        insertButton.setPosition(10, window.getSize().y - 160);
    }

    void drawBucket(int index, int x, int y) {
        // Ajustar tamaño del cubo si es necesario
        int bucketWidth = std::min(int(maxBucketWidth), int(window.getSize().x - x));
        int bucketHeight = std::min(int(maxBucketHeight), int(window.getSize().y - y));

        // Reducir tamaño si se sale de la pantalla
        if (bucketWidth < maxBucketWidth || bucketHeight < maxBucketHeight) {
            bucketWidth = std::max(0, bucketWidth); // Ajustar a 0 si es negativo
            bucketHeight = std::max(0, bucketHeight); // Ajustar a 0 si es negativo
        }

        sf::RectangleShape rect(sf::Vector2f(bucketWidth, bucketHeight));
        rect.setPosition(x, y);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2);

        window.draw(rect);

        std::string text = "Bucket " + std::to_string(index) + "\n" + linearHash.getBucketInfo(index);
        sf::Text info(text, font, 12);
        info.setPosition(x + 10, y + 10);
        info.setFillColor(sf::Color::Black);

        window.draw(info);

        window.draw(inputLabel);
        window.draw(inputBox);
        window.draw(keyInputLabel);
        window.draw(keyInputBox);
        window.draw(valueInputLabel);
        window.draw(valueInputBox);
        window.draw(insertButton);
        window.draw(closeButton);

        // Draw input texts
        window.draw(keyInputText);
        window.draw(valueInputText);
    }

    void handleTextInput(sf::Event event) {
        if (event.type == sf::Event::TextEntered) {
            // Seleccionar la caja de texto activa
            sf::Text& activeText = isKeyInputActive ? keyInputText : valueInputText;

            // Handle input for active text
            if (event.text.unicode == 8 && !activeText.getString().isEmpty()) {
                activeText.setString(activeText.getString().substring(0, activeText.getString().getSize() - 1));
            } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                activeText.setString(activeText.getString() + static_cast<char>(event.text.unicode));
            }
        }
    }


    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (closeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                               static_cast<float>(mousePos.y))) {
                        window.close();
                    } else if (insertButton.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                                       static_cast<float>(mousePos.y))) {
                        // Insert key-value pair
                        K key = static_cast<K>(std::stoi(keyInputText.getString().toAnsiString()));
                        V value = valueInputText.getString().toAnsiString();
                        linearHash.put(key, value);
                        keyInputText.setString("");
                        valueInputText.setString("");
                    } else if (keyInputBox.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                                      static_cast<float>(mousePos.y))) {
                        // Activar la caja de texto de clave
                        isKeyInputActive = true;
                    } else if (valueInputBox.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                                        static_cast<float>(mousePos.y))) {
                        // Activar la caja de texto de valor
                        isKeyInputActive = false;
                    }
                }

                handleTextInput(event);
            }

            drawTable();
        }
    }

    void drawTable() {
        window.clear(sf::Color::White);

        int x = 50;
        int y = 50;

        for (int i = 0; i < linearHash.getSize(); ++i) {
            drawBucket(i, x, y);
            y += maxBucketHeight + 10; // Move to the next bucket with some spacing
        }

        window.display();
    }
};

int main(int argc, char const *argv[])
{

    LinearHash<int, string> linearHashing(2, 2);
    LinearHashVisualizer<int, std::string> visualizer(linearHashing);

    linearHashing.put(1, "Alo");
    linearHashing.put(2, "quien");
    linearHashing.put(3, "es");
    linearHashing.put(5, "quien");
    linearHashing.put(14, "habla");
    linearHashing.put(7, "porfavor");

    visualizer.run();


    ASSERT(linearHashing.search(1) == true, "search is not working");
    ASSERT(linearHashing.search(45) == false, "search is not working");

    cout << linearHashing.toString() << endl;

    ASSERT(linearHashing.get(1) == "Alo", "get is not working");
    ASSERT(linearHashing.get(45) == "", "get is not working");
    /*
    0: []
    1: [1:"Alo", 5:"quien"]
    2: [2:"quien", 14:"habla"]
    3: [3:"es", 7:"porfavor"]
    */

    //assert del print
    ASSERT(linearHashing.toString() == "0: []\n1: [1:Alo, 5:quien]\n2: [2:quien, 14:habla]\n3: [3:es, 7:porfavor]\n", "toString is not working");

    linearHashing.erase(1);
    linearHashing.erase(2);
    ASSERT(linearHashing.search(1) == false, "search is not working");
    ASSERT(linearHashing.search(2) == false, "search is not working");
    //Assert get
    ASSERT(linearHashing.get(1) == "", "get is not working");
    ASSERT(linearHashing.get(2) == "", "get is not working");
    ASSERT(linearHashing.get(3) == "es", "get is not working");

    return 0;
}
