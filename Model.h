#pragma once

#include "Constants.h"

class Model
{
public:
	Model(int width, int height);
	~Model();

	/* GETTERS */
	inline int * getGrid() const { return _h_grid; }
	inline const int getWidth() const { return _width; }
	inline const int getHeight() const { return _height; }
	inline const int getGeneration() const { return _generation; }

	/* SETTERS */
	inline void nextGeneration() { _generation++; }

	/* METHODS */
	void toggle_cell(int x, int y);
	

private: 
	Cell  *_h_grid = 0;
	
	int _width;
	int _height;

	int _generation;
};

