#pragma once
#ifndef GENERIC_TYPE_LIST_H
#define GENERIC_TYPE_LIST_H
#include <vector>


//need empity constructor
/*
CODE EXAMPLE:
GenericTypeList<Entity> list;
list.AddType<Player>();

Entity* ent = typelist.Instance(0);
delete ent;
*/

template<class base>
class MetaGenerator {
public:
	virtual base* Generate() {
		return new base();
	}
};

template<class T, class base>
class Generator : public MetaGenerator<base> {
public:
	base* Generate() {
		return new T();
	}
};

template<class base>
class GenericTypeList
{
public:
	GenericTypeList() {

	}
	~GenericTypeList() {
		for (int i = 0; i < list.size(); i++)
			delete list[i];
		list.clear();
	}

	template<class T>
	void AddType() {
		this->list.push_back(new Generator<T, base>());
	}

	base* Instantiate(int index) {
		return this->list[index]->Generate();
	}
	
	size_t size() {
		return this->list.size();
	}

private:
	std::vector<MetaGenerator<base>*> list;
};

#endif // !GENERIC_TYPE_LIST_H
