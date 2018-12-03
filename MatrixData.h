#pragma once
#include <cstddef>

struct MatrixData
{
	size_t columns, rows;
	double ** m;
	MatrixData(size_t rows, size_t columns);
	MatrixData(size_t rows, size_t columns, double ** a);
	~MatrixData();
	size_t references;
	MatrixData* detach();
};
