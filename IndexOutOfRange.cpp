#include "IndexOutOfRange.h"

IndexOutOfRange::IndexOutOfRange(size_t i, size_t j){
	s.append("Indexes should be between: ");
	s.append(std::to_string(i));
	s.append(", ");
	s.append(std::to_string(j));
	s.append("\n");
}

const char* IndexOutOfRange::what() const noexcept{
	return s.c_str();
}
