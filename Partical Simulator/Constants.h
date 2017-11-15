#pragma once
#include <SFML/Graphics.hpp>

const unsigned long amount = 2097152;

const unsigned int width = 1280;
const unsigned int height = 720;

const unsigned int width_D2 = width/2;
const unsigned int height_D2 = height/2;

const unsigned long sqrtAmount = sqrt(amount);

const float zSpeed = 2;
const float speed = 512;
const float min = 1;
const float force = 1024;
const float maxZoom = (1.f/8.f);

const sf::Color front = sf::Color(255, 255, 255);
const sf::Color back = sf::Color(255, 255, 255);