#pragma once
#include <iostream>

using std::cout;
using std::endl;

class Counter {
public:
	Counter(uint32_t startValue = 1) : m_counter(startValue) { cout << "Initialize refcount" << endl; printState(); }
	~Counter() { m_counter--; }
	void decrease() { printState(); m_counter--; printState(); }
	void increase() { printState(); m_counter++; printState(); }
	void printState() { cout << "Counter address: " << this << ", Counter value: " << m_counter << endl; }
	uint32_t getCounter() const { return m_counter; }
private:
	uint32_t m_counter;
};

template<typename T>
class SharedPtr {
public:
	SharedPtr(T* ptr);
	~SharedPtr();
	// Allow copy
	SharedPtr(const SharedPtr<T>& other);
	SharedPtr<T>& operator=(const SharedPtr<T>& other);
	// Allow move
	SharedPtr(SharedPtr<T>&& other) noexcept;
	SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;

	T& operator*() const;
	T* operator->() const;
private:
	T* m_ptr;
	Counter* m_refCount;
};

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr) : m_ptr(ptr), m_refCount(new Counter()) {
	cout << "SharedPtr ctor" << endl;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
	cout << "SharedPtr dtor" << endl;
	// Check that m_refCount isn't nullptr (in case of move operators for example)
	if (m_refCount != nullptr) {
		m_refCount->decrease();
		if (m_ptr != nullptr && m_refCount->getCounter() == 0) {
			cout << "delete SharedPtr m_ptr and m_refCount" << endl;
			delete m_ptr;
			delete m_refCount;
		}
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) :
	m_ptr(other.m_ptr),
	m_refCount(other.m_refCount)
{
	cout << "copy ctor" << endl;
	m_refCount->increase();
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	cout << "copy assignment" << endl;
	// delete phase. Before assign the new refCount of other we need to decrease current refCount 
	m_refCount->decrease();
	if (m_ptr != nullptr && m_refCount->getCounter() == 0) {
		delete m_ptr;
		delete m_refCount;
	}
	
	m_ptr = other.m_ptr;
	m_refCount = other.m_refCount;
	m_refCount->increase();
	return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept {
	// Check if other is the same object instance. If yes, don't do anything
	if (this == &other) {
		cout << "self move ctor" << endl;
		return;
	}
	cout << "move ctor" << endl;
	// Move phase
	m_ptr = other.m_ptr;
	m_refCount = other.m_refCount;

	// Reset phase
	other.m_ptr = nullptr;
	other.m_refCount = nullptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
	// Check if other is the same object instance. If yes, don't do anything
	if (this == &other) {
		cout << "self move assignment" << endl;
		return *this;
	}

	cout << "move assignment" << endl;
	// Delete phase
	m_refCount->decrease();
	if (m_ptr != nullptr && m_refCount->getCounter() == 0) {
		delete m_ptr;
		delete m_refCount;
	}
	// Move phase
	m_ptr = other.m_ptr;
	m_refCount = other.m_refCount;

	// Reset phase
	other.m_ptr = nullptr;
	other.m_refCount = nullptr;
}

template<typename T>
T& SharedPtr<T>::operator*() const {
	return *m_ptr;
}

template<typename T>
T* SharedPtr<T>::operator->() const {
	return m_ptr;
}