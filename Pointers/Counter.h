#pragma once
#include <cstdint>
class Counter {
public:
	Counter(uint32_t startValue);
	~Counter();
	void decrease();
	void increase();
	void printState();
	uint32_t getCounter() const;
private:
	uint32_t m_counter;
};