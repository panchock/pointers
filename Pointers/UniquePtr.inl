#pragma once
#include "UniquePtr.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr) : m_ptr(ptr) {
	cout << "UniquePtr ctor" << endl;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
	try {
		cout << "UniquePtr dtor" << endl;
		destroy();
	} catch (...) {
		// ILB
	}
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) : m_ptr(other.m_ptr) {
	// Reset phase
	other.m_ptr = nullptr;
	cout << "move ctor" << endl;
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) {
	// Check if other is the same object instance. If yes, don't do anything
	if (this == &other) {
		cout << "self move assignment" << endl;
		return *this;
	}
	// Delete phase
	destroy();
	m_ptr = std::exchange(other.m_ptr, nullptr);
	cout << "move assignment" << endl;
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

template<typename T>
void UniquePtr<T>::destroy() {
	if (m_ptr) {
		cout << "destroying m_ptr of UniquePtr address: " << this << endl;
		delete m_ptr;
	}
}
