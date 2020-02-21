#ifndef CONTAINERS_ARRAY2D_HPP
#define CONTAINERS_ARRAY2D_HPP
#pragma warning(push)
#pragma warning(disable : 6386)
#include "Array.hpp"

// a class used to create fixed width/height 2d arrays
// @templ typename T: the type that the array will store
template<typename T>
class Array2D {

	T* arr;
	size_t w;
	size_t h;

public:

	/// constructors

	Array2D(size_t width, size_t height) : w(width), h(height) {
		// create array
		arr = new T[w * h];
	}

	Array2D(size_t width, size_t height, const T& fill) : w(width), h(height) {
		// create array
		arr = new T[w * h];

		// fill array
		for (size_t i = 0; i < w * h; ++i)
			arr[i] = fill;
	}


	/// copy constructor & operator

	Array2D(const Array2D& other) : w(other.w), h(other.h), arr(nullptr) {
		// create array
		arr = new T[w * h];

		// copy the values in the array
		for (size_t i = 0; i < w * h; ++i)
			arr[i] = other.arr[i];
	}

	Array2D& operator=(const Array2D& other) {
		if (arr) delete[] arr; arr = nullptr;

		// create new array
		w = other.w;
		h = other.h;
		arr = new T[w * h];

		// copy array
		for (size_t i = 0; i < w * h; ++i)
			arr[i] = other.arr[i];

		return *this;
	}


	/// move constructor & operator

	Array2D(Array2D&& other) noexcept : w(other.w), h(other.h), arr(other.arr) {
		// free the other array
		other.w = 0;
		other.h = 0;
		other.arr = nullptr;
	}

	Array2D& operator=(Array2D&& other) noexcept {
		if (arr) delete[] arr; arr = nullptr;

		// copy array
		w = other.w;
		h = other.h;
		arr = other.arr;

		// free other array
		other.w = 0;
		other.h = 0;
		other.arr = nullptr;

		return *this;
	}


	/// destructor
	~Array2D() {
		// delete the array
		if (arr) delete arr;
		arr = nullptr;
		w = 0; h = 0;
	}


	/// iteration

	T* begin() {
		return arr;
	}

	T* end() {
		return &arr[w * h];
	}


	/// operators

	T* operator[](size_t row) {
		return &arr[row * w];
	}

	T* operator*() {
		return arr;
	}

	bool operator==(const Array2D& other) {
		if (w != other.w || h != other.h)
			return false;

		for (size_t i = 0; i < w * h; i++)
			if (arr[i] != other.arr[i])
				return false;

		return true;
	}

	bool operator!=(const Array2D& other) {
		if (w != other.w || h != other.h)
			return true;

		for (size_t i = 0; i < w * h; i++)
			if (arr[i] != other.arr[i])
				return true;

		return false;
	}


	/// functions

	size_t width() {
		return w;
	}

	size_t height() {
		return h;
	}

	void fill(const T& value) {
		for (size_t i = 0; i < w * h; i++)
			arr[i] = value;
	}

};

#pragma warning(pop)
#endif // !CONTAINERS_ARRAY2D_HPP