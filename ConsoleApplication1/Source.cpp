#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Aditya");
    sf::View view(sf::Vector2f(256.0f, 256.0f), sf::Vector2f(512.0f, 512.0f));
    sf::Clock clock;
    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    player.setFillColor(sf::Color::Magenta);
    sf::CircleShape ball(20.0f, 30);
    ball.setFillColor(sf::Color::White);
    player.setOrigin(50.0f, 50.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Textures/block texture.jpg");
    player.setTexture(&playerTexture);
    int i = 0;
    sf::Vector2f ballPos;
    bool falling = true;
    bool going_right = true;
    float hvelocity = (rand() % 50);


    while (window.isOpen()) {

        //events//////
        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {

            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                //std::cout << "New window width:" << evnt.size.width << " New window height: " << evnt.size.height << std::endl;
                printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128) {

                    printf("%c", evnt.text.unicode);
                }
            }
        }
        //////////////


        //start//////
        if (i == 0) {
            player.setPosition(256.0f, 256.0f);
            i = 1;
        }
        //////

        //movement//////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            player.move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            player.move(0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            player.move(0.0f, 0.1f);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float)mousePos.x, (float)mousePos.y);
        }
        ///////////////

        //ball phyhsics///
        sf::Time elapsed = clock.getElapsedTime();
           float t = elapsed.asSeconds();
           //printf("%f", t);
           float a = 9.8;
           ballPos = ball.getPosition();
           if (ballPos.y <= 512-20*2) {

               if (falling == true) {

                   float velocity = 0.1 * 0.5 * a * t * t;
                   ball.move(0.0f, velocity);
                   if (ballPos.x >= 512 - 20 * 2) {
                       going_right = false;
                       ball.move(-hvelocity / 500, 0.0f);
                   }
                   else {
                       if (going_right == true) {
                           ball.move(hvelocity / 500, 0.0f);
                       }

                   }
                   if (going_right == false) {
                       ball.move(-hvelocity / 500, 0.0f);
                   }
               }
               if (falling == false) {

                   float velocity = -10 * 0.5 /( a * t * t);
                   ball.move(0.0f, velocity);

                   if (ballPos.x >= 512 - 20 * 2) {
                       going_right = false;
                       ball.move(-hvelocity / 500, 0.0f);
                   }
                   else {
                       if (going_right == true) {
                           ball.move(hvelocity / 500, 0.0f);
                       }

                   }
                   if (going_right == false) {
                       ball.move(-hvelocity / 500, 0.0f);
                   }
                   if (velocity >= -0.1) {
                       if (velocity <= 0) {
                           clock.restart();
                           falling = true;

                       }
                   }
               }
           }
           else {
               falling = false;
               float hvelocity =(rand() % 50);
               printf("%f", hvelocity);
               float velocity = -10 * 0.5 / (a * t * t);
               ball.move(0.0f, velocity);
               if (ballPos.x >= 512 - 20 * 2) {
                   going_right = false;
                   ball.move(-hvelocity / 500, 0.0f);
               }
               else {
                   if (going_right == true) {
                       ball.move(hvelocity / 500, 0.0f);
                   }

               }
               if (going_right == false) {
                   ball.move(-hvelocity / 500, 0.0f);
               }
           }
        //////
           
           printf("%d\n", going_right);

        window.clear(sf::Color::Black);
        window.setView(view);
        window.draw(player);
        window.draw(ball);
        window.display();
    }

    return 0;
}