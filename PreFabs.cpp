#ifndef PREFABS_CPP
#define PREFABS_CPP

#include <vector>
#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>

namespace Prefabs
{
    class Point_Cordinate
    {
    public:
        unsigned int x;
        unsigned int y;

        Point_Cordinate(unsigned int x, unsigned int y)
        {
            this->x = x;
            this->y = y;
        }
    };

    class PreFabs_Factory
    {
    private:
        std::vector<Point_Cordinate> selectedVector{};

        //TODO : Add rotation transformation method
        // const unsigned int* rotate(float angle, const unsigned int prefab_array[], const unsigned int size)
        // {
        //     unsigned int returnArray[size];

        //     for(int i = 0; i < size; i=i+2)
        //     {
        //         returnArray[i] =
        //     }
        // }

        //Size of array of prefab
        const unsigned int prefab_glider_size{10};
        //Square grid that represents the glider. In this case 3*3
        const unsigned int prefab_glider_gridsize{3};
        //x, y cordinates in sequence.
        const unsigned int prefab_glider[10]{
            0, 0, 2, 0,
            1, 1, 2, 1,
            1, 2};

        const unsigned int prefab_lightweight_spaceship_size{24};
        const unsigned int prefab_lightweight_spaceship_gridsize{5};
        const unsigned int prefab_lightweight_spaceship[24]{
            2, 0, 3, 0,
            0, 1, 1, 1, 3, 1, 4, 1,
            0, 2, 1, 2, 2, 2, 3, 2,
            1, 3, 2, 3};

        const unsigned int prefab_middleweight_spaceship_size{22};
        const unsigned int prefab_middleweight_spaceship_gridsize{6};
        const unsigned int prefab_middleweight_spaceship[22]{
            0, 0, 1, 0, 2, 0, 3, 0, 4, 0,
            0, 1, 5, 1,
            0, 2,
            1, 3, 5, 3,
            3, 4};

        const unsigned int prefab_heavy_spaceship_size{26};
        const unsigned int prefab_heavy_spaceship_gridsize{7};
        const unsigned int prefab_heavy_spaceship[26]{
            0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0,
            0, 1, 6, 1,
            0, 2,
            1, 3, 6, 3,
            3, 4, 4, 4};

        std::vector<Point_Cordinate> get_prefab(unsigned int x,
                                                unsigned int y,
                                                unsigned int tile_size,
                                                const unsigned int prefab[],
                                                unsigned int size)
        {
            std::vector<Point_Cordinate> returnVector;

            x = (x / tile_size) * tile_size;
            y = (y / tile_size) * tile_size;

            for (int i = 0; i < size; i = i + 2)
            {
                returnVector.push_back(Point_Cordinate{(prefab[i] * tile_size) + x, (prefab[i + 1] * tile_size) + y});
            }

            return returnVector;
        }

    public:
        PreFabs_Factory() {}

        float selected_prefab_number = 0.0;
        const unsigned int totalNumberOfPrefabs = 4;

        //Right now not being used but might be used in future developement.
        //Used in the switch statement to get number with a name.
        enum prefab_names
        {
            glider,
            LightWeightSpaceship,
            MiddleWeightSpaceShip,
            HeavyWeightSpaceship
        };

        std::vector<Point_Cordinate> getPrefabByName(
            unsigned int x, unsigned int y,
            unsigned int tile_size,
            prefab_names name, int number = -1)
        {
            int switch_number = 0;

            if (number >= 0)
            {
                switch_number = number;
            }
            else
            {
                switch_number = name;
            }

            switch (switch_number)
            {
            case 0:
                return get_prefab(x, y, tile_size, prefab_glider, prefab_glider_size);
                break;
            case 1:
                return get_prefab(x, y, tile_size, prefab_lightweight_spaceship, prefab_lightweight_spaceship_size);
                break;
            case 2:
                return get_prefab(x, y, tile_size, prefab_middleweight_spaceship, prefab_middleweight_spaceship_size);
                break;
            case 3:
                return get_prefab(x, y, tile_size, prefab_heavy_spaceship, prefab_heavy_spaceship_size);
                break;
            }

            return std::vector<Point_Cordinate>{};
        }

        //Select Prefab to insert by holding middle mouse button and scrolling to select.
        void selectPrefab(sf::RenderWindow &window, sf::Event &event, unsigned int tile_size)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                int x = (sf::Mouse::getPosition(window).x / tile_size) * tile_size;
                int y = (sf::Mouse::getPosition(window).y / tile_size) * tile_size;

                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.delta > 0)
                    {
                        selected_prefab_number += 0.1;
                        if (selected_prefab_number >= totalNumberOfPrefabs)
                        {
                            selected_prefab_number = totalNumberOfPrefabs - 1;
                        }
                        selectedVector.clear();
                        selectedVector = getPrefabByName(x, y, tile_size, glider, selected_prefab_number);
                    }
                    else if (event.mouseWheelScroll.delta < 0)
                    {
                        selected_prefab_number -= 0.1;
                        if (selected_prefab_number < 0)
                        {
                            selected_prefab_number = 0;
                        }
                        selectedVector.clear();
                        selectedVector = getPrefabByName(x, y, tile_size, glider, selected_prefab_number);
                    }
                }

                for (Point_Cordinate point : selectedVector)
                {
                    sf::RectangleShape rect;
                    rect.setSize(sf::Vector2f{(float)tile_size, (float)tile_size});
                    rect.setFillColor(sf::Color{252, 190, 3, 255});
                    rect.setPosition(point.x, point.y);
                    window.draw(rect);
                }
            }
        }
    };
} // namespace Prefabs

#endif //PREFABS_CPP