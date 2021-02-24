#pragma once
/**
 * RAII pointer implementation.
 * UniquePtr can't be copied and destroy the inner pointer in scope exit or in operator= (move assignment)
 */
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
	void destroy();
	T* m_ptr;
};

#include "UniquePtr.inl"