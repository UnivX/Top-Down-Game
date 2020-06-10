#pragma once
#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <math.h>

class Task {
public:
	virtual void Do();
};

class Thread {
public:

	Thread();
	void Start();
	void Stop();
	bool IsWorking();
	void AddTask(Task* task);

private:
	std::thread* m_thread;
	std::vector<Task*> m_tasks;
	bool run;

	void Loop();
};

class ThreadPool {
public:
	ThreadPool(int size);
	void Start();
	void Stop();
	void AddTask(Task* task);
	bool AllThreadComputed();

private:
	int m_size;
	int m_last_thread_used;
	std::vector<Thread> m_threads;
};

#endif //!MULTI_THREADING_H