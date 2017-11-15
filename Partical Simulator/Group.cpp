#include "Group.h"

Group::Group()
{
	reset();
}
Group::~Group()
{
}

void Group::drawUpdate(sf::RenderWindow & win, float & fps)
{
	#pragma omp parallel
	{
		#pragma omp for
		for (unsigned long i = 0; i < amount; i++)
		{
			point[i].pos.x += point[i].vel.x/fps;
			point[i].pos.y += point[i].vel.y/fps;

			draw[i].position.x = point[i].pos.x / cam.zoom + cam.offSet.x + width_D2;
			draw[i].position.y = point[i].pos.y / cam.zoom + cam.offSet.y + height_D2;
		}
	}
	win.draw(draw);
}

void Group::updateMouse(sf::Vector2i mouse)
{
	for (unsigned long i = 0; i < amount; i++)
	{
		float xDis = point[i].pos.x - (((float)mouse.x - cam.offSet.x - width_D2)*cam.zoom);
		float yDis = point[i].pos.y - (((float)mouse.y - cam.offSet.y - height_D2)*cam.zoom);

		if (xDis < 0 && xDis > -min*cam.zoom) { xDis = -min*cam.zoom; }
		else if (xDis >= 0 && xDis < min*cam.zoom) { xDis = min*cam.zoom; }

		if (yDis < 0 && yDis > -min*cam.zoom) { yDis = -min*cam.zoom; }
		else if (yDis >= 0 && yDis < min*cam.zoom) { yDis = min*cam.zoom; }

		const float distance = sqrtf((xDis*xDis) + (yDis*yDis)) / cam.zoom;

		if (xDis > 0) { point[i].vel.x -= (((force / distance) * abs(xDis)) / (abs(yDis) + abs(xDis))); }
		else { point[i].vel.x += (((force / distance) * abs(xDis)) / (abs(yDis) + abs(xDis))); }

		if (yDis > 0) { point[i].vel.y -= (((force / distance) * abs(yDis)) / (abs(yDis) + abs(xDis))); }
		else { point[i].vel.y += (((force / distance) * abs(yDis)) / (abs(yDis) + abs(xDis))); }
	}
}

void Group::negUpdateMouse(sf::Vector2i mouse)
{
	for (unsigned long i = 0; i < amount; i++)
	{
		float xDis = point[i].pos.x - (((float)mouse.x - cam.offSet.x - width_D2)*cam.zoom);
		float yDis = point[i].pos.y - (((float)mouse.y - cam.offSet.y - height_D2)*cam.zoom);

		if (xDis < 0 && xDis > -min) { xDis = -min; } else if (xDis >= 0 && xDis < min) { xDis = min; }

		if (yDis < 0 && yDis > -min) { yDis = -min; } else if (yDis >= 0 && yDis < min) { yDis = min; }

		const float distance = sqrtf((xDis*xDis) + (yDis*yDis)) / cam.zoom;

		if (xDis > 0) { point[i].vel.x += (((force / distance) * abs(xDis)) / (abs(yDis) + abs(xDis))); } else { point[i].vel.x -= (((force / distance) * abs(xDis)) / (abs(yDis) + abs(xDis))); }

		if (yDis > 0) { point[i].vel.y += (((force / distance) * abs(yDis)) / (abs(yDis) + abs(xDis))); } else { point[i].vel.y -= (((force / distance) * abs(yDis)) / (abs(yDis) + abs(xDis))); }
	}
}

void Group::reset()
{
	point.resize(0);
	point.clear();
	for (unsigned long i = 0; i < amount; i++)
	{
		vertexData temp;
		temp.vel = sf::Vector2f(0, 0);
		temp.pos = sf::Vector2f(i % sqrtAmount, ((i - (i % sqrtAmount)) / sqrtAmount));
		draw[i].color = sf::Color((temp.pos.x * 255.f) / sqrtAmount, (temp.pos.y * 255.f) / sqrtAmount, 255.f - ((temp.pos.x * 255.f) / sqrtAmount));
		point.push_back(temp);
	}
}


