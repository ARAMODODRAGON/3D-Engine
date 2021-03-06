#ifndef CONTAINERS_ARRAY_HPP
#define CONTAINERS_ARRAY_HPP
#pragma warning(push)
#pragma warning(disable : 6386)
#include <initializer_list>

// a class used to create fixed width 1d arrays
// @templ typename T: the type that the array will store
template<class T>
class Array {

	/// array and size
	T* arr;
	size_t sz;

public:

	/// default constructor
	explicit Array() : arr(nullptr), sz(0) { }

	/// constructors

	explicit Array(size_t size_) : sz(size_), arr(nullptr) {
		// make array of size
		arr = new T[sz];
	}

	Array(size_t size_, const T& fill) : sz(size_), arr(nullptr) {
		// make array of size
		arr = new T[sz];

		// fill array
		for (size_t i = 0; i < sz; ++i)
			arr[i] = fill;
	}

	Array(std::initializer_list<T> list) : sz(list.size()), arr(nullptr) {
		// create array
		arr = new T[sz];

		size_t i = 0;
		// fill array
		for (T item : list) {
			arr[i] = item;
			++i;
		}
	}


	/// copy constructor & operator

	Array(const Array& other) : sz(other.sz), arr(nullptr) {
		// create array
		arr = new T[sz];

		// copy the values in the array
		for (size_t i = 0; i < sz; ++i)
			arr[i] = other.arr[i];
	}

	Array& operator=(const Array& other) {
		if (arr) delete[] arr; arr = nullptr;

		// create new array
		sz = other.sz;
		arr = new T[sz];

		// copy array
		for (size_t i = 0; i < sz; ++i)
			arr[i] = other.arr[i];

		return *this;
	}


	/// move constructor & operator

	Array(Array&& other) noexcept : sz(other.sz), arr(other.arr) {
		// free the other array
		other.sz = 0;
		other.arr = nullptr;
	}

	Array& operator=(Array&& other) noexcept {
		if (arr) delete[] arr; arr = nullptr;

		// copy array
		sz = other.sz;
		arr = other.arr;

		// free other array
		other.sz = 0;
		other.arr = nullptr;

		return *this;
	}


	/// destructor
	~Array() {
		// delete array
		if (arr) delete[] arr;
		arr = nullptr;
		sz = 0;
	}


	/// iteration

	T* begin() noexcept {
		return arr;
	}

	T* end() noexcept {
		return &arr[sz];
	}


	/// operators

	T& operator[](size_t index) {
		return arr[index];
	}

	T* operator*() {
		return arr;
	}

	bool operator==(const Array& other) {
		if (sz != other.sz) return false;

		for (size_t i = 0; i < sz; ++i)
			if (arr[i] != other.arr[i])
				return false;

		return true;
	}

	bool operator!=(const Array& other) {
		if (sz != other.sz) return true;

		for (size_t i = 0; i < sz; ++i)
			if (arr[i] != other.arr[i])
				return true;

		return false;
	}


	/// functions

	size_t size() {
		return sz;
	}

	void fill(const T& value) {
		for (size_t i = 0; i < sz; ++i)
			arr[i] = value;
	}

	void Resize(const size_t& new_size) {
		T* new_arr = new T[new_size];

		size_t max = (new_size < sz ? new_size : sz);

		// copy the values over while leaving any remaining
		for (size_t i = 0; i < max; ++i)
			new_arr[i] = arr[i];

		// delete the old array
		delete[] arr;

		// copy the new array
		arr = new_arr;
		sz = new_size;
	}
};

#pragma warning(pop)
#endif // !CONTAINERS_ARRAY_HPP