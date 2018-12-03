
#include "WrongDimensions.h"

WrongDimensions::WrongDimensions(size_t m1i, size_t m1j, size_t m2i, size_t m2j){
	s.append("The dimensions of matrixes are wrong:\n");
	s.append(std::to_string(m1i)).append(" x ").append(std::to_string(m1j));
	s.append(" and ");
	s.append(std::to_string(m2i)).append(" x ").append(std::to_string(m2j));
	s.append("\n");
}

const char * WrongDimensions::what() const noexcept
{
	return s.c_str();
}

