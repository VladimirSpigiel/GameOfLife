#pragma once

#include "Constants.h"

class IObservable
{


public:

	/* GETTERS TO IMPLEMENT */
	virtual const int getWidth() const = 0;
	virtual const int getHeight() const = 0;

	/* SETTERS TO IMPLEMENT */
	virtual void setWidth(const int w) = 0;
	virtual void setHeight(const int h) = 0;
	virtual void setGeneration(const int g) = 0;
	virtual void setGrid(const Cell const * grid) = 0;

	/* METHODS TO IMPLEMENT */
	virtual void notify() const = 0;




};

