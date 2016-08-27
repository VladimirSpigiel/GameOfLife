#pragma once
#include <vector>
#include <iostream>
#include <CL\cl.hpp>
#include "Model.h"
#include "IObservable.h"

class OpenCLController
{
public:
	OpenCLController(Model * const model, std::string source, const char * functorName);
	~OpenCLController();

	/* GETTERS */
	cl::Kernel *getKernel() { return &_kernel; }
	cl::CommandQueue *getCommandQueue() { return &_queue; }
	cl::Context *getContext() { return &_context; }

	/* SETTERS */
	void setView(IObservable * view);

	/* METHODS */
	float step();
	void toggle_cell(int x, int y);

protected:

	/* RELATIVE TO OPENCL */
	cl::CommandQueue _queue;
	cl::Kernel _kernel;
	cl::Context _context;

	cl::Buffer _d_grid_before;
	cl::Buffer _d_grid_after;

private:

	/* MODEL TO WORK ON */
	Model *_model;

	/* VIEW TO RENDER MODEL */
	IObservable *_view;

	/* PRIVATE METHODS */
	void updateView() const;


};

