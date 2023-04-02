#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

/**
 * \brief BackgroundWorker class for executing tasks in dedicated thread.
 */
class BackgroundWorker
{
public:
	/**
	 * Create a new BackgroundWorker object
	 * \brief Constructor.
	 */
	BackgroundWorker();

	/**
	 * \brief Destructor.
	 */
	~BackgroundWorker();

	/**
	 * \brief Add a new detached task to the queue.
	 * \param function Function to be executed.
	 * \param args Arguments to the function.
	 */
	template <class Function, class... Args>
		requires std::invocable<Function, Args...>
	void addTask(Function&& function, Args&&... args);

private:
	void workerAction();

	mutable std::mutex mutexQueue_;
	mutable std::condition_variable condVariableNewTask_;
	std::atomic_bool isTerminated_ = false;

	std::queue<std::function<void()>> tasks_;

	std::thread worker_;
};

template <class Function, class... Args>
	requires std::invocable<Function, Args...>
void BackgroundWorker::addTask(Function&& function, Args&&... args)
{
	{
		std::lock_guard l(mutexQueue_);
		tasks_.emplace(std::bind(std::forward<Function>(function),
								 std::forward<Args>(args)...));
	}
	condVariableNewTask_.notify_one();
}