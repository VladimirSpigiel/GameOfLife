#pragma once

#include "IObservable.h"
#include "OpenCLController.h"
#include <GL/freeglut.h>



class GLUTView : public IObservable
{
public:
	static GLUTView *m_instance;
	GLUTView(OpenCLController *controller);
	~GLUTView();

	/* GETTERS */
	virtual const int getWidth() const;
	virtual const int getHeight() const;
	virtual const Cell const* getGrid() const;

	/* SETTERS */
	virtual void setWidth(const int w);
	virtual void setHeight(const int h);
	virtual void setGeneration(const int g);
	virtual void setGrid(const Cell const * grid);

	/* METHODS */
	virtual void notify() const;

	/* DECLARED AS STATIC BECAUSE GLUT NEEDS THOSE GLOBAL FUNCTIONS */
	static void render();
	static void onKeyboard(unsigned char key, int x, int y);

private:
	int _width;
	int _height;
	int _generation;
	const Cell const *_grid = NULL;
	OpenCLController *_controller;
};
