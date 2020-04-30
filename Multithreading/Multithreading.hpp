#pragma once

#include "Utilities.hpp"

struct Job {
	std::size_t startIndex;
	std::size_t endIndex;
	std::size_t imageIndex;
};

class Controller {
public:
	Controller(std::shared_ptr<World>& world);

	void createThreads();

	void createJobs();

	void addToQueue(Job j);

	Job removeFromQueue();

	std::size_t getQueueLength();

	void addResult(std::size_t insertIndex, std::vector<Colour>& result);

	std::vector<Colour> getImage();

private:
	std::queue<Job> jobs;
	std::vector<std::vector<Colour>> image;
	std::shared_ptr<World>& imageWorld;
};

class JobThread {
public:
	JobThread(std::shared_ptr<World>& world, std::shared_ptr<Controller>& mc);

	void getJob();

	void executeJob();

	int mainJobLoop();

private:
	Job j;
	std::shared_ptr<Controller> mainController;
	std::shared_ptr<World> imageWorld;
};
