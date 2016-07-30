#include "stdafx.h"
#include "View.h"


View::View(OpenCLController & controller)
	:_controller(controller),
	_width(DEFAULT_WIDTH),
	_height(DEFAULT_HEIGHT)
{
	controller.setView(this);
}

View::~View()
{
}

const int View::getWidth() const
{
	return _width;
}

const int View::getHeight() const
{
	return _height;
}

void View::setWidth(const int w)
{
	_width = w;
}

void View::setHeight(const int h)
{
	_height = h;
}

void View::setGeneration(const int g)
{
	_generation = g;

	std::cout << "GENERATION :" << _generation << std::endl;
}

void View::draw(const Cell const * grid)
{

	
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++)
			std::cout << grid[y *_width + x] << ",";
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
