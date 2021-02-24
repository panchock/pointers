#pragma once
#include <cstdint>
class Rectangle {
public:
	Rectangle(uint32_t width, uint32_t height) :
		m_width(width),
		m_height(height) {
	}
	uint32_t getWidth() const {
		return m_width;
	}
	uint32_t getHeight() const {
		return m_height;
	}
	uint32_t getArea() const {
		return m_width * m_height;
	}
private:
	uint32_t m_width;
	uint32_t m_height;
};