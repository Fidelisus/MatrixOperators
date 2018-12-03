#include "Matrix.h"
#include "WrongInitializingArray.h"
#include "WrongDimensions.h"
#include "IndexOutOfRange.h"

// -------------------------constructors-----------------------------
Matrix::Matrix(size_t rows, size_t columns, double ** a)
{
	data = new MatrixData(rows, columns, a);
}

Matrix::Matrix(size_t rows, size_t columns)
{
	data = new MatrixData(rows, columns);
}

Matrix::Matrix(const Matrix & matrix) {
	matrix.data->references++;
	data = matrix.data;
}

Matrix::~Matrix() {
	if (--data->references == 0){
		delete data;
    }
}

void Matrix::wrongFile() const{
  		std::cout << "Wrong file";
		abort();
}

Matrix::Matrix(std::string fileName) {
		std::ifstream myFile(fileName);
		if (myFile.is_open())
		{
			size_t rows, columns;
			myFile >> rows;
			if (myFile.fail()) wrongFile();

			myFile >> columns;
			if (myFile.fail()) wrongFile();

			data = new MatrixData(rows, columns);

			while (!myFile.eof()) {
				size_t i;
				for (i = 0; i < data->rows; i++) {
					for (size_t j = 0; j < data->columns; j++) {
						myFile >> data->m[i][j];
						if (myFile.fail()) wrongFile();
					}
				}
			}
			myFile.close();
		}
		else {
			wrongFile();
		}
}

// --------------------------operators---------------------------------
std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
	out.precision(2);
		for (size_t i = 0; i < matrix.data->rows; i++) {
			for (size_t j = 0; j < matrix.data->columns; j++) {
				out << matrix.data->m[i][j] << ", ";
			}
			out << "\n";
		}
	return out;
}

std::istream& operator>>(std::istream& in, const Matrix& matrix) {
		for (size_t i = 0; i < matrix.data->rows; i++) {
			for (size_t j = 0; j < matrix.data->columns; j++) {
				std::cout << "Enter value for row " << i << " column " << j << " : ";
				in >> matrix.data->m[i][j];
				if (in.fail()) matrix.wrongFile();
			}
		}
	return in;
}

Matrix Matrix::operator+(const Matrix & m1) const {
	if (m1.data->columns != this->data->columns || m1.data->rows != this->data->rows)
		throw WrongDimensions(m1.data->rows, m1.data->columns, this->data->rows, this->data->columns);

	Matrix value = Matrix(m1.data->rows, m1.data->columns);
	
	size_t i;
	for (i = 0; i < m1.data->rows; i++) {
		for (size_t j = 0; j < m1.data->columns; j++) {
			value.data->m[i][j] = m1.data->m[i][j] + this->data->m[i][j];
		}
	}
	return value;
}

Matrix Matrix::operator-(const Matrix & m1) const {
	if (m1.data->columns != this->data->columns || m1.data->rows != this->data->rows)
		throw WrongDimensions(m1.data->rows, m1.data->columns, this->data->rows, this->data->columns);

	Matrix value = Matrix(m1.data->rows, m1.data->columns);
	
	size_t i;
	for (i = 0; i < m1.data->rows; i++) {
		for (size_t j = 0; j < m1.data->columns; j++) {
			value.data->m[i][j] = m1.data->m[i][j] - this->data->m[i][j];
		}
	}
	return value;
}

Matrix& Matrix::operator+=(const Matrix & m1) {
	*this = *this + m1;
	return *this;
}

Matrix& Matrix::operator-=(const Matrix & m1) {
	*this = *this - m1;
	return *this;
}

bool Matrix::operator==(const Matrix & m1) const {
	if (m1.data == this->data) return true;
	if (m1.data->columns != this->data->columns || m1.data->rows != this->data->rows) return false;

	size_t i;
	for (i = 0; i < m1.data->rows; i++) {
		for (size_t j = 0; j < m1.data->columns; j++) {
			if (m1.data->m[i][j] != this->data->m[i][j]) return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix & m1) const {
	if (m1.data == this->data) return false;
	if (m1.data->columns != this->data->columns || m1.data->rows != this->data->rows) return true;

	size_t i;
	for (i = 0; i < m1.data->rows; i++) {
		for (size_t j = 0; j < m1.data->columns; j++) {
			if (m1.data->m[i][j] != this->data->m[i][j]) return true;
		}
	}
	return false;
}

Matrix Matrix::operator* (const Matrix & m1) const {
	if (m1.data->columns != this->data->rows)
		throw WrongDimensions(m1.data->rows, m1.data->columns, this->data->rows, this->data->columns);

	Matrix value = Matrix(m1.data->rows, this->data->columns);
	size_t i;

	for (i = 0; i < m1.data->rows; i++) {
		for (size_t j = 0; j < this->data->columns; j++) {
			double cellSum = 0;
			for (size_t k = 0; k < m1.data->columns; k++)
				cellSum += m1.data->m[i][k] * this->data->m[k][j];
			value.data->m[i][j] = cellSum;
		}
	}
	return value;
}

Matrix& Matrix::operator*= (const Matrix & m1) {
	*this = *this*m1;
	return *this;
}

Matrix Matrix::operator*(double factor) const{
	Matrix multiplied(this->data->rows, this->data->columns, this->data->m);
	for (size_t i = 0; i < this->data->rows; i++) {
		for (size_t j = 0; j < this->data->columns; j++) {
			multiplied.data->m[i][j] *= factor;
		}
	}
	return multiplied;
}
//----------------------cref------------------------------ -

Matrix::Cref::operator double() const
{
	return matrix.read(i, j);
}

Matrix::Cref& Matrix::Cref::operator= (double set) {
	matrix.write(i, j, set);
	return *this;
}

double Matrix::read(size_t i, size_t j) const{
	return data->m[i][j];
}

void Matrix::write(size_t i, size_t j, double set) {
	data = data->detach();
	data->m[i][j] = set;
}

//--------------------- = and indexes---------------

void Matrix::checkDimesions(size_t i, size_t j) const{
	if (data->rows <= i || data->columns <= j)
		throw IndexOutOfRange(data->rows, data->columns);
}

Matrix& Matrix::operator=(const Matrix & m1) {
	m1.data->references++;
	this->data->references--;
	if (this->data->references == 0) {
		delete data;
	}
	this->data = m1.data;
	return *this;
}

double Matrix::operator()(size_t i, size_t j) const {
	checkDimesions(i, j);
	return data->m[i][j];
}

Matrix::Cref Matrix::operator()(size_t i, size_t j) {
	checkDimesions(i, j);
	return Matrix::Cref{ *this, i, j };
}
