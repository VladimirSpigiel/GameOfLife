#include "stdafx.h"
#include "GLUTView.h"
#include <string>

GLUTView *GLUTView::m_instance = NULL;

GLUTView::GLUTView(OpenCLController * controller)
	:_controller(controller),
	_gridWidth(DEFAULT_WIDTH),
	_gridHeight(DEFAULT_HEIGHT)
{
	m_instance = this;
	controller->setView(this);
		
	/* SET GLUT ENV */
	int argc = 0;
	char *argv = "";
	const int windowWidth = TILE_SIZE * _gridWidth;
	const int windowHeight = TILE_SIZE * _gridHeight + GUI_SIZE_HEIGHT;

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


void GLUTView::notify() const
{
	render();
}

void GLUTView::onKeyboard(unsigned char key, int x, int y)
{
	int k = (int)key;
	std::cout << k;

	if (k == STEP_KEY)
		std::cout << GLUTView::m_instance->_controller->step() << "s" << std::endl;

	else if (k == FILL_EMPTY_KEY)
		std::cout << GLUTView::m_instance->_controller->fill(FILL_EMPTY) << "s" << std::endl;
	else if (k == FILL_FULL_KEY)
		std::cout << GLUTView::m_instance->_controller->fill(FILL_FULL) << "s" << std::endl;
	else if (k == FILL_RANDOM_KEY)
		std::cout << GLUTView::m_instance->_controller->fill(FILL_RANDOM) << "s" << std::endl;

	else if (k == TOGGLE_DISPLAY_GRID_KEY) {
		GLUTView::m_instance->_gridDisplayed = !GLUTView::m_instance->_gridDisplayed;
		GLUTView::m_instance->notify();
	}

	else if (k == EXIT_KEY)
		exit(0);
}

void GLUTView::onMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		GLUTView::m_instance->toggleCell(x, y);
	
}

void GLUTView::onMotion(int x, int y)
{
	GLUTView::m_instance->toggleCell(x, y);
}

void GLUTView::toggleCell(int x, int y)
{
	int xReal = (int)(x / TILE_SIZE);
	int yReal = (int)(y / TILE_SIZE);
	GLUTView::m_instance->_controller->toggleCell(xReal, yReal);
}

void GLUTView::render(){

	// PROLOGUE
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const int gridWidth = GLUTView::m_instance->getGridWidth();
	const int gridHeight = GLUTView::m_instance->getGridHeight();
	const Cell const * cells = GLUTView::m_instance->getGrid();
	const bool gridDisplayed = GLUTView::m_instance->_gridDisplayed;

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);

	// DRAW VERTICAL LINES
	if (gridDisplayed) {

		for (int y = 0; y < gridHeight; y++) {
			glVertex2f(y*TILE_SIZE, 0);
			glVertex2f(y*TILE_SIZE, gridHeight * TILE_SIZE);
		}

		// DRAW HORIZONTAL LINES
		for (int x = 0; x < gridWidth; x++) {
			glVertex2f(0, x*TILE_SIZE);
			glVertex2f(gridWidth * TILE_SIZE, x*TILE_SIZE);
		}
	}

	glEnd();

	// DRAW CELLS
	glColor3f(1, 0.7, 0);
	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {

			// GET CURRENT CELL
			Cell cell = cells[y * gridWidth + x];

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


	//DRAW GUI
	glColor3f(1, 1, 1);

	glBegin(GL_LINES);
	glVertex2d(0, gridHeight * TILE_SIZE);
	glVertex2d(gridWidth * TILE_SIZE, gridHeight * TILE_SIZE);
	glEnd();

	std::string infoGeneration = "Generation : ";
	infoGeneration += std::to_string(GLUTView::m_instance->_generation);
	glRasterPos2i(0, gridHeight * TILE_SIZE + 0.4 * GUI_SIZE_HEIGHT);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *) infoGeneration.c_str());
	
	std::string infoControls = "KEYS : {Enter : toggle grid, Space : step up, Escape : exit}";
	glRasterPos2i(0, gridHeight * TILE_SIZE + 0.4 * GUI_SIZE_HEIGHT + 20);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char *)infoControls.c_str());
	
	// EPILOGUE
	glutSwapBuffers();

}




