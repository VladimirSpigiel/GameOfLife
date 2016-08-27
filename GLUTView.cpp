#include "stdafx.h"
#include "GLUTView.h"

GLUTView *GLUTView::m_instance = NULL;

GLUTView::GLUTView(OpenCLController * controller)
	:_controller(controller),
	_width(DEFAULT_WIDTH),
	_height(DEFAULT_HEIGHT)
{
	m_instance = this;
	controller->setView(this);
		
	/* SET GLUT ENV */
	int argc = 0;
	char *argv = "";
	const int windowWidth = TILE_SIZE * DEFAULT_WIDTH;
	const int windowHeight = TILE_SIZE * DEFAULT_HEIGHT;

	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Game Of Life - GPU PoC");
	gluOrtho2D(0, windowWidth, windowHeight, 0);

	/* FUNC USED BY GLUT TO RENDER */
	glutDisplayFunc(render);
	glutKeyboardFunc(onKeyboard);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutMainLoop();
}

GLUTView::~GLUTView()
{
}

const int GLUTView::getWidth() const
{
	return _width;
}

const int GLUTView::getHeight() const
{
	return _height;
}

const Cell const * GLUTView::getGrid() const
{
	return _grid;
}

void GLUTView::setWidth(const int w)
{
	_width = w;
}

void GLUTView::setHeight(const int h)
{
	_height = h;
}

void GLUTView::setGeneration(const int g)
{
	_generation = g;
}

void GLUTView::setGrid(const Cell const * grid)
{
	_grid = grid;
}

void GLUTView::notify() const
{
	render();
}

void GLUTView::onKeyboard(unsigned char key, int x, int y)
{
	if ((int) key == STEP_KEY)
		GLUTView::m_instance->_controller->step();

	if ((int) key == TOGGLE_DISPLAY_GRID_KEY) {
		GLUTView::m_instance->_gridDisplayed = !GLUTView::m_instance->_gridDisplayed;
		GLUTView::m_instance->notify();
	}
}

void GLUTView::onMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		GLUTView::m_instance->toggle_cell(x, y);
	
}

void GLUTView::onMotion(int x, int y)
{
	GLUTView::m_instance->toggle_cell(x, y);
}

void GLUTView::toggle_cell(int x, int y)
{
	int xReal = (int)(x / TILE_SIZE);
	int yReal = (int)(y / TILE_SIZE);
	GLUTView::m_instance->_controller->toggle_cell(xReal, yReal);
}

void GLUTView::render(){

	// PROLOGUE
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const int width = GLUTView::m_instance->getWidth();
	const int height = GLUTView::m_instance->getHeight();
	const Cell const * cells = GLUTView::m_instance->getGrid();
	const bool gridDisplayed = GLUTView::m_instance->_gridDisplayed;

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);

	// DRAW VERTICAL LINES

	if (gridDisplayed) {

		for (int y = 0; y < height; y++) {
			glVertex2f(y*TILE_SIZE, 0);
			glVertex2f(y*TILE_SIZE, height * TILE_SIZE);
		}

		// DRAW HORIZONTAL LINES
		for (int x = 0; x < width; x++) {
			glVertex2f(0, x*TILE_SIZE);
			glVertex2f(width * TILE_SIZE, x*TILE_SIZE);
		}
	}

	glEnd();

	// DRAW CELLS
	glColor3f(1, 0.7, 0);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			// GET CURRENT CELL
			Cell cell = cells[y * width + x];

			if (cell == ALIVE_CELL) {
				
				// DRAW A RECTANGLE WHICH REPRESENTS A CELL 
				glBegin(GL_POLYGON);
				glVertex2d(x*TILE_SIZE, y*TILE_SIZE);
				glVertex2d(x*TILE_SIZE + TILE_SIZE, y*TILE_SIZE);
				glVertex2d(x*TILE_SIZE + TILE_SIZE, y*TILE_SIZE + TILE_SIZE);
				glVertex2d(x*TILE_SIZE, y*TILE_SIZE + TILE_SIZE);
				glEnd();
			}
		}
	}
	
	// EPILOGUE
	glutSwapBuffers();

}




