#ifndef PREFABS_CPP
#define PREFABS_CPP

#include <vector>
#include <iostream>

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
            const unsigned int prefab_glider_size{ 10 };
            const unsigned int prefab_glider[10]
            {
                0, 0, 2, 0,
                1, 1, 2, 1,
                1, 2
            };

            const unsigned int prefab_lightweight_spaceship_size{ 24 };
            const unsigned int prefab_lightweight_spaceship[24]
            {
                2, 0, 3, 0,
                0, 1, 1, 1, 3, 1, 4, 1,
                0, 2, 1, 2, 2, 2, 3, 2,
                1, 3, 2, 3
            };
            
            std::vector<Point_Cordinate> get_prefab
                (unsigned int x,
                 unsigned int y,
                 unsigned int tile_size,
                 const unsigned int prefab[],
                 unsigned int size
                 )
            {
                std::vector<Point_Cordinate> returnVector;
                  
                x = (x/tile_size) * tile_size;
                y = (y/tile_size) * tile_size;  

                for(int i = 0; i < size; i = i+2)
                {
                    returnVector.push_back(Point_Cordinate{ (prefab[i]*tile_size)+x, (prefab[i+1]*tile_size)+y });
                }
                std::cout << "Return Vector ReadY " << std::endl;
                for(Point_Cordinate arr : returnVector)
                {
                    std::cout << arr.x << " : " << arr.y << std::endl;
                }
                return returnVector;
            }

        public:
            PreFabs_Factory(){}

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
                prefab_names name)
            {
                switch(name)
                {
                    case glider:
                        return get_prefab(x, y, tile_size, prefab_glider, prefab_glider_size);
                        break;
                    case LightWeightSpaceship:
                        return get_prefab(x, y, tile_size, prefab_lightweight_spaceship, prefab_lightweight_spaceship_size);
                        break;
                }

                return std::vector<Point_Cordinate>{};
            }
    };
}

#endif //PREFABS_CPP