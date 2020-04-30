#include "Multithreading.hpp"

Controller::Controller(std::shared_ptr<World>& world) :
	imageWorld{ world }, image{}, jobs{}
{
	image.reserve(world->height);
	image.resize(world->height);
	createJobs();
	//createThreads();
}

void Controller::createJobs() {
	Job j{};
	for (std::size_t i{ 0 }; i < imageWorld->height; ++i) {
		j.imageIndex = i;
		j.startIndex = i;
		j.endIndex = i + 1;
		jobs.push(j);
	}
}



Job Controller::removeFromQueue() {
	std::lock_guard<std::mutex> guard(jobs_lock);
	Job j = jobs.front();
	jobs.pop();
	//std::cout << jobs.size() << "\n";
	return j;
}

std::size_t Controller::getQueueLength() {
	return jobs.size();
}

void Controller::addResult(std::size_t insertIndex, std::vector<Colour>& result) {
	std::lock_guard<std::mutex> guard(futures_lock);
	image[insertIndex] = result;
}

std::vector<Colour> Controller::getImage() {
	std::vector<Colour> finalImage{};
	for (auto vector : image) {
		finalImage.insert(finalImage.end(), vector.begin(), vector.end());
	}
	return finalImage;
}