#include "SharedPtr.h"
#include "UniquePtr.h"

template<typename T, class... Args>
SharedPtr<T> make_shared(Args&&... args) {
	return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T, class... Args>
UniquePtr<T> make_unique(Args&&... args) {
	return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
