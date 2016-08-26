#include "stdafx.h"
#include "OpenCLController.h"
#include <fstream>
#include "Constants.h"


OpenCLController::OpenCLController(Model * const model, std::string source, const char * functorName)
	:_model(model)
{


	std::ifstream ifs(source);
	
	std::string content;

	if(ifs.is_open()){
		content = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	}
	else {
		std::cout << "Could not open " + source + " file" << std::endl;
		exit(1);
	}
	
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	//get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device = all_devices[0];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";

	_context = cl::Context({ default_device });

	cl::Program::Sources sources;

	// kernel calculates for each element C=A+B                                                                         ";
	sources.push_back({ content.c_str(), content.length() });

	cl::Program program(_context, sources);
	if (program.build({ default_device }) != CL_SUCCESS) {
		std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
		exit(1);
	}

	_queue = cl::CommandQueue(_context, default_device, CL_QUEUE_PROFILING_ENABLE);

	_kernel = cl::Kernel(program, functorName);


	/* ALLOCATE MEMORY ON DEVICE */
	_d_grid_before = cl::Buffer(_context, CL_MEM_READ_ONLY, sizeof(Cell) * _model->getWidth() * _model->getHeight());
	_d_grid_after = cl::Buffer(_context, CL_MEM_WRITE_ONLY, sizeof(Cell) * _model->getWidth() * _model->getHeight());

	/* SET KERNEL ARGUEMENTS */
	_kernel.setArg(1, _d_grid_after);
	_kernel.setArg(2, _model->getWidth());
	_kernel.setArg(3, _model->getHeight());
	
}


OpenCLController::~OpenCLController()
{
	_view = NULL;
}

void OpenCLController::setView(IObservable * view) { 
	_view = view; 
	_view->setGrid(_model->getGrid());
}

float OpenCLController::step()
{
	std::cout << "STEP" << std::endl;

	/* UPDATE FIRST ARGUMENT */
	_kernel.setArg(0, _d_grid_before);

	/* WRITE DATA TO DEVICE */
	_queue.enqueueWriteBuffer(_d_grid_before, CL_TRUE, 0, sizeof(Cell) * _model->getWidth() * _model->getHeight(), _model->getGrid());

	/* LAUNCH KERNEL */
	cl::Event evt;
	_queue.enqueueNDRangeKernel(_kernel, cl::NullRange, cl::NDRange(_model->getWidth(), _model->getHeight()), cl::NullRange, NULL, &evt);
	evt.wait();

	/* READ BACK VALUES */
	_queue.enqueueReadBuffer(_d_grid_after, CL_TRUE, 0, sizeof(Cell) * _model->getWidth() * _model->getHeight(), _model->getGrid());

	/* ESTIMATE THE KERNEL RUNTIME DURATION */
	float nanoElapsed = evt.getProfilingInfo<CL_PROFILING_COMMAND_END>() - evt.getProfilingInfo<CL_PROFILING_COMMAND_START>();
	
	_model->nextGeneration();
	this->updateView();

	/* N = N + 1 */
	_d_grid_before = _d_grid_after;

	return nanoElapsed / 1000 / 1000;

}

void OpenCLController::updateView() const
{
	_view->setGeneration(_model->getGeneration());
	_view->setGrid(_model->getGrid());
	
	_view->notify();

}
