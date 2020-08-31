# Conway's Game of Life

Conway's Game of Life implemented with C++ and and SFML.

## Setting up SFML to comile and run code

The [link](https://www.sfml-dev.org/tutorials/2.5/start-linux.php) to the tutorial section that shows how set up SFML for development.

Makefile provided can be used to build and run. Use `build` with the make command for MinGW make.

THe SFML `.dll` files provided in the bin folder of SFML need to be copied to the place where the build `.exe` file is placed.

## Settings

Some of the game values can be easily changed in code to your liking.

* Main.cpp

1. WINDOW_X and WINDOW_Y : Change to set screen resolution in pixel value. Default is set to 800 Width and 600 height.

2. TILE_SIZE : Change the size of individual block render that interact with each other. Basically the size of individual cell in the game of life. (Default : 10). Prefer values in multiple of 5 as the tile are implemented as `int` and operations while displaying might lead to rounding values and inaccurate positions.

3. GENERATIONS_PER_SEC : This is the number of generations that take place each second. Larger the value faster the cells interact.

4. title : Denotes the tile of the window. Nothing to do with actual game. Just changes title of the render window.

5. There are other values that can be changed but these are the things that are easy to change.

* Prefabs.cpp
  
New Prefabs can be added to the file that can be then selected and placed directly as contiguous blocks in the window.

Adding the prefab :

```c++
    //Size of array of prefab
    const unsigned int prefab_glider_size{10};
    //Square grid that represents the glider. In this case 3*3
    //This is basically the square bounding box that the prefab will completely fit in.
    const unsigned int prefab_glider_gridsize{3};
    //x, y cordinates in sequence.
    //Each i(x) and i+1(y) value represents the top left corner of the rectangle 
    //and width is determined by TILE_SIZE that we had set.
    const unsigned int prefab_glider[10]{
        0,0, 2,0,
        1,1, 2,1,
        1,2
        };
```

As we want to select it with mouse the prefab that we add also need to be put in the switch statement.

```c++
public:
    //code
    //Change the value to represent the total number of prefabs that exist.
    const unsigned int totalNumberOfPrefabs = 4;
    //code

    switch (switch_number)
    {
    //Other cases
    case 3:
        return get_prefab(x, y, tile_size, prefab_heavy_spaceship, prefab_heavy_spaceship_size);
        break;
    //Add a number for your prefab here and call the get_Prefab statement as shown above with proper arguments.
    }

```

## Playing/Using

1. Initially there are no alive cells in the window and the game is paused.

2. `A` and `S` buttons are used to *pause* and *play* respectively.

3. *Left click/Hold Mouse button to add alive cells* to the game. This can be done when the game is running/playing, but the cell will die immediately if there are no other cells around it to interact. So Pause the game to add the cells in structures you want.

4. *Right click to add the selected prefab*. If the button is held when the game is running multiple prefabs will be added to the window and they will interact with each other. If you want that they dont interact immediately pause the game.

5. Press and hold the middle mouse button to see the selected prefab. Press and Hold and scroll up/down the middle mouse button to select the a prefab.
