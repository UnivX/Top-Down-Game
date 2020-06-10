#include "MultiThreading.h"

void Task::Do() {
	std::cout << "started basic task\n";
}


Thread::Thread() {
	this->m_thread = nullptr;
	this->run = false;
}


void Thread::Start() {
	this->m_thread = new std::thread(&Thread::Loop, this);
	this->run = true;
}


void Thread::Stop() {
	this->run = false;
}


bool Thread::IsWorking() {
	return this->m_tasks.size() != 0;
}


void Thread::AddTask(Task* task) {
	this->m_tasks.push_back(task);
}


void Thread::Loop() {

	while (run) {
		if (this->m_tasks.size() != 0)
		{
			this->m_tasks[0]->Do();
			this->m_tasks.erase(this->m_tasks.begin());
		}
	}

}


ThreadPool::ThreadPool(int size) {
	for (int i = 0; i < size; i++) {
		this->m_threads.push_back(Thread());
	}
	this->m_size = size;
	this->m_last_thread_used = 0;
}


void ThreadPool::Start() {
	for (int i = 0; i < this->m_threads.size(); i++) {
		this->m_threads[i].Start();
	}
}


void ThreadPool::Stop() {
	for (int i = 0; i < this->m_threads.size(); i++) {
		this->m_threads[i].Stop();
	}
}


void ThreadPool::AddTask(Task* task) {
	this->m_threads[this->m_last_thread_used].AddTask(task);
	this->m_last_thread_used++;
	if (this->m_last_thread_used >= this->m_size)
		this->m_last_thread_used = 0;
}


bool ThreadPool::AllThreadComputed() {
	for (int i = 0; i < this->m_threads.size(); i++) {
		if (this->m_threads[i].IsWorking())
			return false;
	}
	return true;
}