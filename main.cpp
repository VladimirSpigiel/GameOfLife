// main.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <CL\cl.hpp>
#include "Model.h"
#include "OpenCLController.h"
#include "View.h"

int main() {

	/* 
	   MVC PROJECT BECAUSE I DONT KNOW IF IM GONNA USE
	   OPENGL OR VULKAN OR SDL AS A RENDER LIBRARY
	*/
	
	Model *model = new Model(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	OpenCLController controller(model, "kernel.cl", "gameStep");
	View view(controller);


	for (int i = 0; i < 20; i++)
		std::cout << "STEP TOOK : " << controller.step() << "ms" << std::endl;


	return 0;
}

