#pragma once
#include "SharedPtr.h"

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr) : m_ptr(ptr), m_refCount(new Counter) {
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
	try {
		destroy();
	} catch (...) {
		// IBL
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : m_ptr(other.m_ptr), m_refCount(other.m_refCount) {
	m_refCount++;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
	// Check if other is the same object instance.If yes, don't do anything
	if (this == &other) {
		return *this;
	}

	// delete phase. Before assign the new refCount of other we need to decrease current refCount 
	destroy();
	m_ptr = other.m_ptr;
	m_refCount = other.m_refCount;
	m_refCount++;
	return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) : m_ptr(other.m_ptr),	m_refCount(other.m_refCount) {
	// Reset phase
	other.m_ptr = nullptr;
	other.m_refCount = nullptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) {
	// Check if other is the same object instance. If yes, don't do anything
	if (this == &other) {
		return *this;
	}

	// Delete phase
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
	if (m_refCount != nullptr) {
		m_refCount--;
		if (m_refCount->getCounter() == 0) {
			delete m_refCount;
			m_refCount = nullptr;
			if (m_ptr != nullptr) {
				delete m_ptr;
				m_ptr = nullptr;
			}
		}
	}
}
