#pragma once
#include <iostream>

using std::cout;
using std::endl;

template<typename T>
class UniquePtr {
public:
	UniquePtr(T* ptr);
	~UniquePtr();
	// Don't allow copy
	UniquePtr(const UniquePtr<T>& other) = delete;
	UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;
	// Allow move
	UniquePtr(UniquePtr<T>&& other);
	UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept;

	T& operator*() const;
	T* operator->() const;
private:
	T* m_ptr;
};

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr) : m_ptr(ptr) {
	cout << "UniquePtr ctor" << endl;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
	cout << "UniquePtr dtor" << endl;
	if (m_ptr) {
		cout << "delete UniquePtr m_ptr" << endl;
		delete m_ptr;
	}
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) {
	// Check if other is the same object instance. If yes, don't do anything
	if (this == &other) {
		cout << "self move ctor" << endl;
		return;
	}
	cout << "move ctor" << endl;
	// Move phase
	m_ptr = other.m_ptr;

	// Reset phase
	other.m_ptr = nullptr;
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
	// Check if other is the same object instance. If yes, don't do anything
	if (this == &other) {
		cout << "self move assignment" << endl;
		return *this;
	}

	cout << "move assignment" << endl;
	// Delete phase
	if (m_ptr) {
		delete m_ptr;
	}
	// Move phase
	m_ptr = other.m_ptr;

	// Reset phase
	other.m_ptr = nullptr;
	return *this;
}

template<typename T>
T& UniquePtr<T>::operator*() const {
	return *m_ptr;
}

template<typename T>
T* UniquePtr<T>::operator->() const {
	return m_ptr;
}