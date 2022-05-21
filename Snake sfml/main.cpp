#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <windows.h>
#include "Sound.h"


const float SNAKE_SIZE = 50.f;
const float WINDOW_HEIGHT = 900.f;
const float WINDOW_WIDTH = 1500.f;

std::default_random_engine RNG(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<> DIST_X(0, 29);
std::uniform_int_distribution<> DIST_Y(0, 17);

enum Entity { WALL, FRUIT, BODY, NONE };

class Snake {

public:
    std::list<sf::RectangleShape> body;
    sf::Vector2f snakeVector;
    void move(); 
    void grow();
    void draw(sf::RenderWindow& window); 
    Entity collisionHead(sf::RectangleShape& fruit);
    bool collisionBody(sf::RectangleShape& fruit);
    //constructor
    Snake() {

        sf::RectangleShape tail(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
        tail.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        tail.setFillColor(sf::Color::Green);
        tail.setOutlineColor(sf::Color::Black);
        tail.setOutlineThickness(2.f);
        this->body.push_back(tail);

    }

};

inline void Snake::grow() {

    sf::RectangleShape tail(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
    sf::Vector2f tailVector;
    std::list<sf::RectangleShape>::iterator it = this->body.end();
    --it;
    if (it->getPosition().y < this->body.back().getPosition().y) {
        tailVector = sf::Vector2f(0.f, SNAKE_SIZE);
    }
    else if (it->getPosition().y > this->body.back().getPosition().y) {
        tailVector = sf::Vector2f(0.f, -SNAKE_SIZE);
    }
    else if (it->getPosition().x < this->body.back().getPosition().x) {
        tailVector = sf::Vector2f(-SNAKE_SIZE, 0.f);
    }
    else if (it->getPosition().x > this->body.back().getPosition().x) {
        tailVector = sf::Vector2f(SNAKE_SIZE, 0.f);
    }

    tail.setPosition(this->body.back().getPosition() - tailVector);
    tail.setFillColor(sf::Color::Green);
    tail.setOutlineColor(sf::Color::Black);
    tail.setOutlineThickness(2.f);
    this->body.push_back(tail);

}

inline void Snake::move() {



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->snakeVector != sf::Vector2f(0.f, SNAKE_SIZE)) {
        this->snakeVector = sf::Vector2f(0.f, -SNAKE_SIZE);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->snakeVector != sf::Vector2f(0.f, -SNAKE_SIZE)) {
        this->snakeVector = sf::Vector2f(0.f, SNAKE_SIZE);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && this->snakeVector != sf::Vector2f(SNAKE_SIZE, 0.f)) {
        this->snakeVector = sf::Vector2f(-SNAKE_SIZE, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && this->snakeVector != sf::Vector2f(-SNAKE_SIZE, 0.f)) {
        this->snakeVector = sf::Vector2f(SNAKE_SIZE, 0.f);
    }


    this->body.back().setPosition(this->body.front().getPosition() + snakeVector);
    this->body.push_front(this->body.back());
    this->body.pop_back();


}

inline void Snake::draw(sf::RenderWindow& window) {
    for (auto& part : this->body) {

        window.draw(part);
    }
    window.draw(this->body.front());
}


inline Entity Snake::collisionHead(sf::RectangleShape& fruit) {

    sf::Vector2f head = this->body.front().getPosition();

    if (fruit.getPosition() == head) {
        return FRUIT;
    }
    else if (head.y < 0 || head.y >= WINDOW_HEIGHT || head.x < 0 || head.x >= WINDOW_WIDTH) {
        return WALL;
    }
    else {

        std::list<sf::RectangleShape>::iterator it = this->body.begin();
        for (++it; it != this->body.end(); ++it) {
            if (it->getPosition() == head) {
                return BODY;
            }
        }

        return NONE;
    }
}

//returns true if body collisions with body
inline bool Snake::collisionBody(sf::RectangleShape& fruit) {

    sf::Vector2f fruitPos = fruit.getPosition();
    for (auto& part : this->body) {
        if (part.getPosition() == fruitPos) return true;
    }

    return false;
}

class Menu {

public:
    Menu(float width, float height) {

        font.loadFromFile("RoughenCornerRegular-7RjV.ttf");

        selectedItemIndex = 0;

        menu[0].setFont(font);
        menu[0].setFillColor(sf::Color::White);
        menu[0].setStyle(sf::Text::Bold);
        menu[0].setCharacterSize(150);
        menu[0].setPosition(300, 350);

        menu[1].setFont(font);
        menu[1].setFillColor(sf::Color::White);
        menu[1].setString("Exit");
        menu[1].setStyle(sf::Text::Bold);
        menu[1].setCharacterSize(100);
        menu[1].setPosition(300, 550);

        menu[2].setFont(font);
        menu[2].setFillColor(sf::Color::White);
        menu[2].setString("Score: ");
        menu[2].setStyle(sf::Text::Bold);
        menu[2].setCharacterSize(50);

        menu[3].setFont(font);
        menu[3].setFillColor(sf::Color::White);
        menu[3].setStyle(sf::Text::Bold);

    }

    void drawGameMenu(sf::RenderWindow& window, int score) {

        menu[0].setString("PLAY");
        window.draw(menu[0]);
        window.draw(menu[1]);

    }

    void drawScore(sf::RenderWindow& window, int score) {

        menu[2].setPosition(1150, 915);
        window.draw(menu[2]);
        menu[3].setCharacterSize(50);
        menu[3].setPosition(1350, 915);
        menu[3].setString(std::to_string(score-1));
        window.draw(menu[3]);

    }

    void drawFinalScore(sf::RenderWindow& window, int score) {

        menu[3].setCharacterSize(150);
        menu[3].setPosition(450, 650);
        menu[3].setString(std::to_string(score-1));
        window.draw(menu[3]);

    }


    void moveDown() {
        menu[0].setFillColor(sf::Color::White);
        menu[1].setFillColor(sf::Color::Black);
        selectedItemIndex = 1;
    }

    void moveUp() {
        menu[0].setFillColor(sf::Color::Black);
        menu[1].setFillColor(sf::Color::White);
        selectedItemIndex = 0;
    }

    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[4];

};


Sound sound;

int main() {

    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;

    int gameRunning = 1;

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Snake", sf::Style::Close | sf::Style::Titlebar);

    sound.PlayMusic();

    window.setFramerateLimit(20);
    
    Menu menu(WINDOW_WIDTH, WINDOW_HEIGHT);
    Snake mySnake;
    sf::Texture bg,plgr, apples, lose;
    //load background
    bg.loadFromFile("images/background.png");
    //load san choi
    plgr.loadFromFile("images/grass.png");
    //load man hinh game over
    lose.loadFromFile("images/GameOver.png");
    sf::Sprite background(bg);
    sf::Sprite playground(plgr);
    sf::Sprite LoseMenu(lose);
    
    background.setPosition(0, 0);

    //tao thuc an tai diem ngau nhien
    sf::RectangleShape fruit(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
    fruit.setFillColor(sf::Color::Red);
    fruit.setPosition(DIST_X(RNG) * 50.f, DIST_Y(RNG) * 50.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyReleased:
                //menu game
                if (gameRunning==1) {
                    switch (event.key.code) {
                    case sf::Keyboard::Up:
                        menu.moveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.moveDown();
                        break;
                    case sf::Keyboard::Enter:
                        if (menu.selectedItemIndex == 0) {

                            gameRunning = 2;
                            mySnake.snakeVector = sf::Vector2f(0.f, 0.f);

                            mySnake.body.clear();
                            sf::RectangleShape tail(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
                            tail.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                            tail.setFillColor(sf::Color::Green);
                            tail.setOutlineColor(sf::Color::Black);
                            tail.setOutlineThickness(2.f);
                            mySnake.body.push_back(tail);

                        }
                        else window.close();
                        break;

                    default:
                        break;
                    }

                }
                break;

            default:
                break;
            }
        }

        //play game
        if (gameRunning==2) {
            mySnake.move();
            

            Entity collidedEntity = mySnake.collisionHead(fruit);

            if (collidedEntity == FRUIT) {
                sound.PlayEat();
                mySnake.grow();
                fruit.setPosition(DIST_X(RNG) * 50.f, DIST_Y(RNG) * 50.f);

                while (mySnake.collisionBody(fruit))
                    fruit.setPosition(DIST_X(RNG) * 50.f, DIST_Y(RNG) * 50.f);
            }
            else if (collidedEntity == WALL) {
                if (mySnake.body.size() != 1) {
                    sound.PlayLose();
                    mySnake.body.pop_front();
                    mySnake.grow();
                    mySnake.body.front().setFillColor(sf::Color::White);
                    gameRunning = 3;
                }
                else {
                    mySnake.body.front().setPosition(mySnake.body.front().getPosition() - mySnake.snakeVector);
                    mySnake.body.front().setFillColor(sf::Color::White);
                    sound.PlayLose();
                    gameRunning = 3;
                }
            }
            else if (collidedEntity == BODY) {
                mySnake.body.front().setFillColor(sf::Color::White);
                sound.PlayLose();
                gameRunning = 3;
            }

        }

        window.clear();

        //delay man hinh game over-> menu(5s)
        if (gameRunning == 0) {
            sleep_for(10ns);
            sleep_until(system_clock::now() + 5s);
            gameRunning = 1;
        }

        if (gameRunning==1) {

            window.draw(background);
            menu.drawGameMenu(window, mySnake.body.size());
        }
        if (gameRunning==2) {
            window.draw(playground);
            window.draw(fruit);
            mySnake.draw(window);
            menu.drawScore(window, mySnake.body.size());
        }
        //ve man hinh game over
        if (gameRunning == 3) {
            window.draw(LoseMenu);
            menu.drawFinalScore(window, mySnake.body.size());
            gameRunning=0;
        }


        window.display();

    }

    return 0;
}