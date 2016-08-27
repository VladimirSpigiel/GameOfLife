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
	virtual const int getWidth() const { return _width; }
	virtual const int getHeight() const { return _height; }
	virtual const Cell const* getGrid() const { return _grid; }

	/* SETTERS */
	virtual void setWidth(const int w) { _width = w; }
	virtual void setHeight(const int h) { _height = h; }
	virtual void setGeneration(const int g) { _generation = g; }
	virtual void setGrid(const Cell const * grid) { _grid = grid; }

	/* METHODS */
	virtual void notify() const;

	/* DECLARED AS STATIC BECAUSE GLUT NEEDS THOSE GLOBAL FUNCTIONS */
	static void render();
	static void onKeyboard(unsigned char key, int x, int y);
	static void onMouse(int button, int state, int x, int y);
	static void onMotion(int x, int y);

private:
	int _width;
	int _height;
	int _generation;
	const Cell const *_grid = NULL;
	OpenCLController *_controller;

	bool _gridDisplayed = false;

	void toggle_cell(int x, int y);
};

