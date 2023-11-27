#include "LinearHash.h"
#include <iostream>
#include <string>
#include "tester.h"
#include <SFML/Graphics.hpp>

using namespace std;

template <typename K, typename V>
class LinearHashVisualizer {
private:
    LinearHash<K, V>& linearHash;
    sf::RenderWindow window;

public:
    LinearHashVisualizer(LinearHash<K, V>& linearHash) : linearHash(linearHash), window(sf::VideoMode(800, 600), "Linear Hash Table Visualization") {}

    void drawBucket(int index, int x, int y) {
        sf::RectangleShape rect(sf::Vector2f(150, 80));
        rect.setPosition(x, y);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2);

        window.draw(rect);

        // Display bucket information
        std::string text = "Bucket " + std::to_string(index) + "\n" + linearHash.getBucketInfo(index);
        sf::Font font;
        if (!font.loadFromFile("../arial.ttf")) {
            // handle font loading error
        }

        sf::Text info(text, font, 12);
        info.setPosition(x + 10, y + 10);
        info.setFillColor(sf::Color::Black);

        window.draw(info);
    }

    void drawTable() {
        window.clear(sf::Color::White);

        int x = 50;
        int y = 50;

        for (int i = 0; i < linearHash.getSize(); ++i) {
            drawBucket(i, x, y);
            x += 170; // Move to the next bucket with some spacing
        }

        window.display();
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            drawTable();
        }
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
