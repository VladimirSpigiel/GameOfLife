#pragma once

#include "IObservable.h"
#include "OpenCLController.h"

class View : public IObservable
{
public:
	View(OpenCLController &controller);
	~View();

	/* GETTERS */
	virtual const int getWidth() const;
	virtual const int getHeight() const;

	/* SETTERS */
	virtual void setWidth(const int w);
	virtual void setHeight(const int h);
	virtual void setGeneration(const int g);

	/* METHODS */
	virtual void draw(const Cell const * grid);

private:
	int _width;
	int _height;
	int _generation;
	OpenCLController _controller;
};

