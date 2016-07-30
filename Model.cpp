#include "stdafx.h"
#include "Model.h"
#include <iostream>


Model::Model(int width, int height):
	_width(width),
	_height(height),
	_generation(0)
{
	/* INIT THE GRID THAT CONTAINS THE CELLS*/
	_h_grid = new Cell[_width * _height];
	for (int i = 0; i < _width * _height; i++)
		_h_grid[i] = DEAD_CELL;

	for (int i = 0; i < _height; i++)
		_h_grid[i * _width] = ALIVE_CELL;

	
}

Model::~Model()
{
	if (_h_grid != NULL){
		delete _h_grid;
		_h_grid = NULL;
	}
}




