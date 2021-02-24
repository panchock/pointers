#pragma once
#include <iostream>
#include "Counter.h"

using std::cout;
using std::endl;

template<typename T>
class SharedPtr {
public:
	SharedPtr(T* ptr);
	~SharedPtr();
	// Allow copy
	SharedPtr(const SharedPtr<T>& other);
	SharedPtr<T>& operator=(const SharedPtr<T>& other);
	// Allow move
	SharedPtr(SharedPtr<T>&& other);
	SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;

	T& operator*() const;
	T* operator->() const;
private:
	void destroy();
	T* m_ptr;
	Counter* m_refCount;
};
 
#include "SharedPtr.inl"