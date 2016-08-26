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

	std::cout << "GENERATION :" << _generation << std::endl;
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

	if ((int) key == 32)
		GLUTView::m_instance->_controller->step();


}

void GLUTView::render(){

	// PROLOGUE
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const int width = GLUTView::m_instance->getWidth();
	const int height = GLUTView::m_instance->getHeight();
	const Cell const * cells = GLUTView::m_instance->getGrid();

	glBegin(GL_LINES);

	// DRAW VERTICAL LINES
	for (int y = 0; y < height; y++) {
		glVertex2f(y*TILE_SIZE, 0);
		glVertex2f(y*TILE_SIZE, height * TILE_SIZE);
	}

	// DRAW HORIZONTAL LINES
	for (int x = 0; x < width; x++) {
		glVertex2f(0, x*TILE_SIZE);
		glVertex2f(width * TILE_SIZE, x*TILE_SIZE);
	}

	glEnd();


	// DRAW CELLS
	glBegin(GL_POLYGON);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			// GET CURRENT CELL
			Cell cell = cells[y * width + x];

			if (cell == ALIVE_CELL) {

				// DRAW A RECTANGLE WHICH REPRESENTS A CELL 
				glVertex2d(x*TILE_SIZE, y*TILE_SIZE);

				glVertex2d(x*TILE_SIZE + TILE_SIZE, y*TILE_SIZE);

				glVertex2d(x*TILE_SIZE + TILE_SIZE, y*TILE_SIZE + TILE_SIZE);

				glVertex2d(x*TILE_SIZE, y*TILE_SIZE + TILE_SIZE);

				glVertex2d(x*TILE_SIZE, y*TILE_SIZE);
			}
		}
	}
	glEnd();

	// EPILOGUE
	glutSwapBuffers();

}




