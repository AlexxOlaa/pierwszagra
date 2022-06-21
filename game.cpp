#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;
using namespace sf;

bool gameOver = false;
bool gameOver1 = false;

int main()
{   
    srand(time(0));
    RenderWindow window(VideoMode(400, 500), "Saper!");

    Texture texture;
    texture.loadFromFile("Pattern.jpg");
    Sprite sprite(texture);

    Font font;
    font.loadFromFile("arial.ttf");
    Text text, text1, text2, text3;
    text.setFont(font);
    text.setPosition(10, 400);
    text.setCharacterSize(15);
    text.setString("Game rules:");
    text1.setFont(font);
    text1.setPosition(10, 415);
    text1.setCharacterSize(15);
    text1.setString("Click left mouse button to open the cell");
    text2.setFont(font);
    text2.setPosition(10, 430);
    text2.setCharacterSize(15);
    text2.setString("Click right mouse button to mark the cell with a flower");
    text3.setFont(font);
    text3.setPosition(10, 445);
    text3.setCharacterSize(15);
    text3.setString("Good luck!");

    Texture texture1;
    texture1.loadFromFile("Clock.png");
    Sprite sprite1;
    sprite1.setTexture(texture1);
    sprite1.setPosition(215, 360);

    Clock clock;
    Time time;
    stringstream ss;
    int s = 0;
    int m = 0;
    int h = 0;
    Text timer;
    timer.setFont(font);
    timer.setPosition(250, 360);
    timer.setCharacterSize(25);
    timer.setString("");

    Texture texture2;
    texture2.loadFromFile("Game_Over.png");
    Sprite sprite2;
    sprite2.setTexture(texture2);
    sprite2.setPosition(0, 0);

    int area[12][12];
    int showarea[12][12]; 

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            showarea[i][j] = 10;
            if (rand() % 5 == 0)
            {
                area[i][j] = 9;
            }
            else
            {
                area[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            int n = 0;
            if (area[i][j] == 9)
                continue;
            if (area[i + 1][j] == 9)
                n++;
            if (area[i][j + 1] == 9)
                n++;
            if (area[i - 1][j] == 9)
                n++;
            if (area[i][j - 1] == 9)
                n++;
            if (area[i + 1][j + 1] == 9)
                n++;
            if (area[i - 1][j - 1] == 9)
                n++;
            if (area[i - 1][j + 1] == 9)
                n++;
            if (area[i + 1][j - 1] == 9)
                n++;
           area[i][j] = n;
        }
    }

    while (window.isOpen() && gameOver1 == false)
    {
        if (gameOver == true)
        {
            Sleep(20);
        }

        int width = 32;
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / width;
        int y = pos.y / width;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    showarea[x][y] = area[x][y];
                }
                else if (event.key.code == Mouse::Right)
                {
                    showarea[x][y] = 11;
                }
            }
        }

        window.clear(Color::Blue);

        ss.str("");
        time = clock.getElapsedTime();
        s = time.asSeconds();
        h = s / 3600;
        m = (s - (h * 3600)) / 60;
        s = s - (h * 3600 + m * 60);
        if(h<10)
        {
          ss<<"0"<<h;
        }
        else
        {
           ss<<h;
        }
        if(m<10)
        {
            ss<<":"<<"0"<<m;
        }
        else
        {
            ss<<":"<<m;
        }
        if(s<10)
        {
            ss<<":"<<"0"<<s;
        }
        else
        {
            ss<<":"<<s;
        }
        timer.setString(ss.str());

        window.draw(text);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(sprite1);
        window.draw(timer);

        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 10; j++)
            {
                sprite.setTextureRect(IntRect(showarea[i][j] * width, 0, width, width));
                sprite.setPosition(i * width, j * width);
                window.draw(sprite);
                if (showarea[x][y] == 9)
                {
                    showarea[i][j] = area[i][j];
                    clock.restart();
                    window.draw(sprite2);
                    gameOver = true;
                }
                else if ((showarea[x][y] == 0 || showarea[x][y] == 1 || showarea[x][y] == 2 || showarea[x][y] == 3 || showarea[x][y] == 4 || showarea[x][y] == 5 || showarea[x][y] == 6 || showarea[x][y] == 7 || showarea[x][y] == 8 || showarea[x][y] == 9 || showarea[x][y] == 10 || showarea[x][y] == 11 ) && gameOver == true)
                {
                    for (int i = 0; i < 1000; i++)
                    {
                        window.draw(sprite2);
                    }
                    gameOver1 = true;
                }
            }
        }
        window.display();
    }
    return 0;
}