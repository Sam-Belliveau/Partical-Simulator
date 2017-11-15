#pragma once
#include "Constants.h"
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <omp.h>
#include <vector>

struct Camera
{
	sf::Vector2f offSet = sf::Vector2f(0.f, 0.f);
	float zoom = 3;
};

struct vertexData
{
	sf::Vector2f vel = sf::Vector2f(0.f, 0.f);
	sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
};

class Group
{
public:
	Group();
	~Group();

	void drawUpdate(sf::RenderWindow & win, float & fps);
	void updateMouse(sf::Vector2i mouse);
	void negUpdateMouse(sf::Vector2i mouse);
	void reset();

	Camera cam;

	std::vector <vertexData> point;

	sf::VertexArray draw = sf::VertexArray(sf::Points, amount);
};

