#include "Game.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

//int max(int x, int y)
//{
//	return x > y ? x : y;
//}
//
//double max(double x, double y)
//{
//	return x > y ? x : y;
//}

enum class Person { Health = 35, Mana = 35 };

struct PersonInfo
{
	std::string m_name;
	std::vector<std::string> m_phoneNumber;
};

//Struct have their members public by defualt

class NotAbstractClass
{
public:
	std::string name;
	unsigned int age;
};

class AbstractClass
{
private:
	std::string m_name;
	unsigned int age;
};


int main()
{
	//Game game(sf::Vector2u(640, 480), "SFML Game Engine");
	//while (game.isRunning())
	//{
	//	game.update();
	//	game.render();
	//	game.lateUpdate();
	//}

	std::string name = "Ryan Swann";
	std::string* pName = &name;
	std::string* ppName = pName;
	std::string* pppName = ppName;

	//copied elements into a vector
	std::string name;
	std::vector<std::string> names;
	names.push_back(name);
	
	//Construct a new element within the vector - Not Copying.
	names.emplace_back(new std::string("wew"));

	char c;
	std::cin >> c;
	return 0;


}
