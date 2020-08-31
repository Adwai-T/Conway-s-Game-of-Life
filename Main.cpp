#include <string>
#include <array>
#include <thread>
#include <chrono>

#include "PreFabs.cpp"

const unsigned int WINDOW_X{800}, WINDOW_Y{600}, TILE_SIZE{10}, GENERATIONS_PER_SEC{15};
const std::string title{"Game Of life"};
const sf::Vector2f TILE_RECT_SIZE{TILE_SIZE, TILE_SIZE};

class GameOfLife
{
private:
  std::vector<sf::RectangleShape> rectangles;
  std::array<std::array<bool, WINDOW_X / TILE_SIZE + 2>, WINDOW_Y / TILE_SIZE + 2> aliveCells;

public:
  GameOfLife()
  {
    reset_aliveCells();
  }
  ~GameOfLife()
  {
  }

  void reset_aliveCells()
  {
    for (int row = 0; row < WINDOW_Y / TILE_SIZE + 2; row++)
    {
      for (int col = 0; col < WINDOW_X / TILE_SIZE + 2; col++)
      {
        aliveCells[row][col] = false;
      }
    }
  }

  std::vector<sf::RectangleShape> getrectangles()
  {
    return rectangles;
  }

  bool addRectangle(int x, int y)
  {

    if (x >= 0 && y >= 0 && x <= WINDOW_X - TILE_SIZE && y <= WINDOW_Y - TILE_SIZE)
    {
      x = (x / TILE_SIZE) * TILE_SIZE;
      y = (y / TILE_SIZE) * TILE_SIZE;

      for (sf::RectangleShape nowRect : rectangles)
      {
        if (nowRect.getPosition().x == x && nowRect.getPosition().y == y)
          return false;
      }

      sf::RectangleShape rect;
      rect.setSize(TILE_RECT_SIZE);
      rect.setPosition(x, y);
      rect.setFillColor(sf::Color{50, 168, 82, 255});
      rectangles.push_back(rect);

      return true;
    }
  }

  void update_aliveCells()
  {
    for (sf::RectangleShape rect : rectangles)
    {
      aliveCells[(rect.getPosition().y / TILE_SIZE) + 1][(rect.getPosition().x / TILE_SIZE) + 1] = true;
    }
  }

  //For Debugging.
  // void print_aliveCells()
  // {
  //   for(std::array<bool, WINDOW_Y/TILE_SIZE+2> arr : aliveCells)
  //   {
  //     for(bool alive : arr)
  //     {
  //       std::cout << alive << " ";
  //     }
  //     std::cout << std::endl;
  //   }
  // }

  unsigned int getNumberOfSurroundingCells(int row, int col)
  {
    unsigned int surrounding = 0;

    if (aliveCells[row - 1][col - 1])
    {
      surrounding++;
    }
    if (aliveCells[row - 1][col])
    {
      surrounding++;
    }
    if (aliveCells[row - 1][col + 1])
    {
      surrounding++;
    }
    if (aliveCells[row][col - 1])
    {
      surrounding++;
    }
    if (aliveCells[row][col + 1])
    {
      surrounding++;
    }
    if (aliveCells[row + 1][col - 1])
    {
      surrounding++;
    }
    if (aliveCells[row + 1][col])
    {
      surrounding++;
    }
    if (aliveCells[row + 1][col + 1])
    {
      surrounding++;
    }

    return surrounding;
  }

  void nextGeneration()
  {
    reset_aliveCells();
    update_aliveCells();
    rectangles.clear();

    unsigned int surrounding = 0;

    for (int row = 1; row <= WINDOW_Y / TILE_SIZE; row++)
    {
      for (int col = 1; col <= WINDOW_X / TILE_SIZE; col++)
      {
        surrounding = getNumberOfSurroundingCells(row, col);

        if (surrounding == 3)
        {
          addRectangle((col - 1) * TILE_SIZE, (row - 1) * TILE_SIZE);
        }
        else if (surrounding == 2 && aliveCells[row][col])
        {
          addRectangle((col - 1) * TILE_SIZE, (row - 1) * TILE_SIZE);
        }
      }
    }
  }

  void addPrefab(std::vector<Prefabs::Point_Cordinate> prefab_vector)
  {
    for (Prefabs::Point_Cordinate point : prefab_vector)
    {
      addRectangle(point.x, point.y);
    }
  }

  void clearRectangle()
  {
    rectangles.clear();
  }
};

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), title, sf::Style::Close);

  //Game
  GameOfLife game;
  Prefabs::PreFabs_Factory prefab_factory;

  //Text
  sf::Font font;
  sf::Text game_state;
  const std::string pause{"Paused"};
  const std::string playing{"Playing"};

  //Font
  try
  {
    font.loadFromFile("./resources/CHLORINR.TTF");
    game_state.setFillColor(sf::Color::Red);
    game_state.setString(pause);
    game_state.setFont(font);
    game_state.setCharacterSize(25);
    game_state.setPosition(5, 5);
  }
  catch (std::exception e)
  {
    std::cout << "Font could not be Loaded." << std::endl;
  }

  //Game Loop
  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    //Clear the previously rendered window.
    window.clear();

    //Left mouse button to add Tiles one at a time.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      int x = sf::Mouse::getPosition(window).x;
      int y = sf::Mouse::getPosition(window).y;
      game.addRectangle(x, y);
    }

    //Right Mouse Button to add Prefab selected.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
      int x = sf::Mouse::getPosition(window).x;
      int y = sf::Mouse::getPosition(window).y;
      game.addPrefab(
          prefab_factory.getPrefabByName(
              x, y, TILE_SIZE, prefab_factory.glider, (int)prefab_factory.selected_prefab_number));
    }

    //Middle Mouse button to Select the prefab
    prefab_factory.selectPrefab(window, event, TILE_SIZE);

    for (sf::RectangleShape rect : game.getrectangles())
    {
      window.draw(rect);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      game_state.setString(pause);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      game_state.setString(playing);
    }

    if (game_state.getString() == playing)
    {
      game.nextGeneration();
    }

    window.draw(game_state);

    window.display();

    //Pause thread to control framerate.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / GENERATIONS_PER_SEC));
  }

  return EXIT_SUCCESS;
}