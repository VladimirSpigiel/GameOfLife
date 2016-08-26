// main.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <CL\cl.hpp>
#include "Model.h"
#include "OpenCLController.h"
#include "GLUTView.h"

int main(int argc, char **argv) {

	/* 
	   MVC PROJECT BECAUSE I DONT KNOW IF IM GONNA USE
	   OPENGL OR VULKAN OR SDL AS A RENDER LIBRARY
	*/
	
	Model *model = new Model(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	OpenCLController *controller = new OpenCLController(model, "kernel.cl", "gameStep");
	GLUTView view(controller);


	float avg = 0.0;

	
	avg += controller->step();


	std::cout << "STEP TOOK : " << avg << "ms";

	


	return 0;
}

