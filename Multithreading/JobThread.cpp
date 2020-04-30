#include "Multithreading.hpp"
#include "Camera.hpp"

JobThread::JobThread(std::shared_ptr<World>& world, std::shared_ptr<Controller>& mc) :
	imageWorld{ world }, mainController{ mc }, j{}
{}

int JobThread::mainJobLoop() {
	//std::cout << "Thread starting \n";
	while (mainController->getQueueLength() > 0) {
		getJob();
		if (j.endIndex == (imageWorld->height + 5)) {
			break;
		}
		executeJob();
	}
	return 0;
}

void JobThread::getJob() {
	if (mainController->getQueueLength() > 0) {
		j = mainController->removeFromQueue();
	}
	else {
		j.endIndex = imageWorld->height + 5;
	}
}

void JobThread::executeJob() {
	std::vector<Colour> pixels{};
	Camera camera = Camera();
	camera.setD(100.0f);
	camera.setEye({ -150.0f, -80.0f, -50.0f });
	camera.setLookAt({ 0,0,0 });
	camera.setUpVector({ 0,1,0 });
	camera.computeUVW();
	pixels = camera.renderScene(imageWorld, j.startIndex, j.endIndex);
	mainController->addResult(j.imageIndex, pixels);
}