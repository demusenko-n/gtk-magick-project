#include "BackgroundWorker.h"

BackgroundWorker::BackgroundWorker() : worker_([this] { workerAction(); }) {}

BackgroundWorker::~BackgroundWorker()
{
	isTerminated_.store(true);
	worker_.join();
}

void BackgroundWorker::workerAction()
{
	for (;;)
	{
		std::function<void()> task_to_complete;
		{
			std::unique_lock l(mutexQueue_);
			condVariableNewTask_.wait(
				l, [this] { return !tasks_.empty() || isTerminated_; });
			if (isTerminated_)
			{
				break;
			}
			task_to_complete = std::move(tasks_.front());
			tasks_.pop();
		}
		task_to_complete();
	}
}
