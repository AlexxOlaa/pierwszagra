#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{   
    srand(time(0));
    RenderWindow window(VideoMode(400, 500), "Saper!");

    Texture texture;
    texture.loadFromFile("sztuka.jpg");
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
    texture1.loadFromFile("Alexander.png");
    Sprite sprite1;
    sprite1.setTexture(texture1);
    sprite1.setPosition(10, 10);

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

    while (window.isOpen())
    {
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

        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 10; j++)
            {
                if (showarea[x][y] == 9)
                {
                    showarea[i][j] = area[i][j];
                }
                sprite.setTextureRect(IntRect(showarea[i][j] * width, 0, width, width));
                sprite.setPosition(i * width, j * width);
                window.draw(sprite);
            }
        }
        window.draw(text);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(sprite1);
        window.display();
    }
    return 0;
}