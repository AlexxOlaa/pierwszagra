#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{   
    srand(time(0));
    RenderWindow window(VideoMode(400, 400), "Saper!");

    Texture texture;
    texture.loadFromFile("sztuka.jpg");
    Sprite sprite(texture);

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
                window.close();

            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                {
                    showarea[x][y] = area[x][y];
                }
                else if (event.key.code == Mouse::Right)
                {
                    showarea[x][y] = 11;
                }
        }

        window.clear(Color::Blue);

        for (int i = 1; i <= 10; i++)
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

        window.display();
    }
    return 0;
}