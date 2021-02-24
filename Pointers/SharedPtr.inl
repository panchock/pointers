#pragma once
#include "SharedPtr.h"

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr) : m_ptr(ptr), m_refCount(new Counter) {
	cout << "SharedPtr ctor" << endl;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
	try {
		cout << "SharedPtr dtor" << endl;
		// Check that m_refCount isn't nullptr (in case of move operators for example)
		if (m_refCount != nullptr) {
			m_refCount->decrease();
			destroy();
		}
	} catch (...) {
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : m_ptr(other.m_ptr), m_refCount(other.m_refCount) {
	cout << "copy ctor" << endl;
	m_refCount->increase();
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
	cout << "copy assignment" << endl;
	// delete phase. Before assign the new refCount of other we need to decrease current refCount 
	m_refCount->decrease();
	destroy();
	m_ptr = other.m_ptr;
	m_refCount = other.m_refCount;
	m_refCount->increase();
	return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) : m_ptr(other.m_ptr),	m_refCount(other.m_refCount) {
	cout << "move ctor" << endl;
	// Reset phase
	other.m_ptr = nullptr;
	other.m_refCount = nullptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) {
	// Check if other is the same object instance. If yes, don't do anything
	if (this == &other) {
		cout << "self move assignment" << endl;
		return *this;
	}

	cout << "move assignment" << endl;
	// Delete phase
	m_refCount->decrease();
	destroy();
	// Move and Reset phase
	m_ptr = std::exchange(other.m_ptr, nullptr);
	m_refCount = std::exchange(other.m_refCount, nullptr);
	return *this;
}

template<typename T>
T& SharedPtr<T>::operator*() const {
	return *m_ptr;
}

template<typename T>
T* SharedPtr<T>::operator->() const {
	return m_ptr;
}

template<typename T>
void SharedPtr<T>::destroy() {
	if (m_ptr != nullptr && m_refCount->getCounter() == 0) {
		cout << "delete SharedPtr m_ptr and m_refCount" << endl;
		delete m_ptr;
		delete m_refCount;
	}
}