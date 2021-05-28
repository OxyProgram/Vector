#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "stdlib.h"
#include <fstream>
#include <sstream>
#include <list>
#include <deque>
#include <iterator>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;
using std::deque;

struct out_of_range
{

};

template<class T>
class Vector
{
public:

    using value_type = T;
	using size_type = size_t;
	
	Vector();
	explicit Vector(int s);
	Vector(int n, int val);
	Vector(const Vector& arg);
	Vector<T>& operator=(const Vector<T>& arg);
	Vector(const std::initializer_list<T>& vec);
	template<class InputIterator>
	Vector(InputIterator first, InputIterator last);
	~Vector();
	// ITERATORS
	class iterator;
	const iterator cbegin() const;
	const iterator cend() const;
	T* begin();
	T* end();
	const T* begin() const;
	const T* end() const;
	iterator rbegin();
    iterator rend();
    iterator rbegin() const;
    iterator rend() const;
	iterator crbegin() const;
    iterator crend() const;
	// CAPACITY
	bool empty() const;
	size_type capacity() const;
	void reserve(int newmalloc);
	void resize(int newsize, T val = T());
	size_type size() const;
	size_type max_size() const;
	void shrink_to_fit();
	// MODIFIERS
	void clear();
	void push_back(const T& d);
	void pop_back();
	iterator insert(iterator k, const T& val);
	void swap(Vector &v);
	iterator erase(iterator n);
	iterator erase(iterator first, iterator last);
	void move_elem(T* dest, T* from, size_type n);
	// ELEMENT ACCESS
	T& at(int n);
	const T& at(int n) const;
	T& operator[](int i);
	const T& operator[](int i) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T* data();
	const T* data() const;
	void sortVector();

	// **************************



private:
	size_type	_size;		
	T*		_array;	
	size_type	_capacity;
						
};



template<class T> class Vector<T>::iterator {
public:
	iterator(T* p)
		:_curr(p)
	{}

    iterator& operator-(const iterator& b) {
		*_curr = *_curr - *b._curr;
		return *this;
	}

    iterator& operator+(const iterator& b) {
		*_curr = *_curr + *b._curr;
		return *this;
	}

	iterator& operator++() {
		_curr++;
		return *this;
	}

	iterator& operator--() {
		_curr--;
		return *this;
	}

	T& operator*() {
		return *_curr;
	}

	bool operator==(const iterator& b) const {
		return *_curr == *b._curr;
	}

	bool operator!=(const iterator& b) const {
		return *_curr != *b._curr;
	}

private:
	T* _curr;
};


// Constructors/Destructor
template<class T>
Vector<T>::Vector()
	:_size(0), _array(0), _capacity(0)
{}

template<class T>
inline Vector<T>::Vector(int s) {
    _size = s;
    _array = new T[s];
    _capacity = s;
	for (int i = 0; i < _size; ++i)
		_array[i] = T();
}

template<class T >
Vector<T>::Vector(int n, int val) : _size(n), _capacity(n)  {
    _array = new T[_size];

    for (int i = 0; i < _size; i++)
        _array[i] = val;
}

template<class T>
inline Vector<T>::Vector(const Vector & arg)
	:_size(arg._size), _array(new T[arg._size]) {
	for (int i = 0; i < arg._size; ++i)
		_array[i] = arg._array[i];
}

template<class T>
Vector<T>::Vector(const std::initializer_list<T>& vect) : _size(vect.size()), _capacity(vect.size())  {
    _array = new T[vect.size()];

    for (int i = 0; i < vect.size(); i++)
        _array[i] = *(vect.begin() + i);
}

template<class T>
template<class InputIterator>
Vector<T>::Vector(InputIterator first, InputIterator last) {
    size_type count = 0;
    for (InputIterator curr = first; curr != last; ++curr) ++count;
    _size = count;
    _capacity = count + count / 2 + 1;
    _array = new T[_capacity];
    for (size_type i = 0; i < count; i++)
        _array[i] = *first++;
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& a) {
	if (this == &a) return *this;	// Self-assingment not work needed

									// Current Vector has enough space, so there is no need for new allocation
	if (a._size <= _capacity) {
		for (int i = 0; i < a._size; ++i) {
			_array[i] = a._array[i];
			_size = a._size;
			return *this;
		}
	}

	T* p = new T[a._size];

	for (int i = 0; i < a._size; ++i)
		p[i] = a._array[i];

	delete[] _array;
	_size = a._size;
	_capacity = a._size;
	_array = p;
	return *this;
}



template<class T>
Vector<T>::~Vector() {
	delete[] _array;
}


template<class T>
inline const  typename Vector<T>::iterator Vector<T>::cbegin() const {
	return begin();
}

template<class T>
inline const typename Vector<T>::iterator Vector<T>::cend() const {
	return end();
}

template<class T>
T* Vector<T>::begin() {
	return &_array[0];
}

template<class T>
T* Vector<T>::end() {
	return &_array[_size];
}

template<class T>
const T* Vector<T>::begin() const {
	return &_array[0];
}

template<class T>
const T* Vector<T>::end() const {
	return &_array[_size];
}

template<class T>
typename Vector<T>::iterator Vector<T>::rbegin() 
{
    return iterator(_array + _size);
}

template<class T>
typename Vector<T>::iterator Vector<T>::rend() {
    return iterator(_array);
}

template<class T>
typename Vector<T>::iterator Vector<T>::rbegin() const {
    return iterator(_array + _size);
}

template<class T>
typename Vector<T>::iterator Vector<T>::rend() const {
    return iterator(_array);
}

template<class T>
typename Vector<T>::iterator Vector<T>::crbegin() const {
    return rbegin();
}

template<class T>
typename Vector<T>::iterator Vector<T>::crend() const {
    return rend();
}



// Capacity
template<class T>
inline void Vector<T>::shrink_to_fit() {
	T* temp = new T[_size];

    for (int i = 0; i < _size; i++)
        temp[i] = _array[i];

    delete[] _array;
    _array = temp;
    _capacity = _size;
}
}

template<class T>
inline bool Vector<T>::empty() const {
	return (_size == 0);
}

template<class T>
inline size_t Vector<T>::capacity() const {
	return _capacity;
}

template<class T>
inline void Vector<T>::reserve(int newalloc) {
	if (newalloc <= _capacity) return;

	T* p = new T[newalloc];

	for (int i = 0; i < _size; ++i)
		p[i] = _array[i];

	delete[] _array;

	_array = p;

	_capacity = newalloc;
}

template<class T>
inline void Vector<T>::resize(int newsize, T val) {
	reserve(newsize);

	for (int i = _size; i < newsize; ++i)
		_array[i] = T();

	_size = newsize;
}

template<class T>
inline size_t Vector<T>::size() const {
	return _size;
}



// Modifiers
template<class T>
inline void Vector<T>::push_back(const T& d) {
	if (_capacity == 0)
		reserve(8);
	else if (_size == _capacity)
		reserve(2 * _capacity);

	_array[_size] = d;

	++_size;
}

template<class T>
inline void Vector<T>::pop_back() {
	if (_size > 0)
        _size--;
}


template<class T>
inline void Vector<T>::clear() {
    delete[] _array;
    _array = new T[5];
    _capacity = 5;
    _size = 0;
}


template<class T>
typename Vector<T>::iterator Vector<T>::insert(iterator iter, const T& val) {
    int i = 0;

    if (_capacity > _size)  {
        for (iterator it(_array + _size); it != iter; it--, i++)
            _array[_size - i] = _array[_size - i - 1];
        *iter = val;
        _size++;
    }
    else {
        T* temp = new T[_size + 1];
        for (iterator it(_array); it != iter; it++, i++)
            temp[i] = _array[i];
        temp[i] = val;
        i++;

        for (iterator it(_array + i + 1); it != _array + _size + 2; it++, i++)
            temp[i] = _array[i - 1];
        delete[] _array;
        _array = temp;
        _size++;
        _capacity = _size;
    }
    return iter;
}

template<class T>
inline void Vector<T>::sortVector() {
	std::sort(_array, _array + _size);
}

template<typename T>
void Vector<T>::move_elem(T* dest, T* from, size_type n) {
    if (dest < from) {
        T* _dest = dest, * _from = from;
        for (size_t i = 0; i < n; i++)
            *_dest++ = std::move(*_from++);
    }
    else if (dest > from) {
        T* _dest = dest + n - 1, * _from = from + n - 1;
        for (size_t i = n; i > 0; i--)
            *_dest-- = std::move(*_from--);
    }
    else
        return;
}




// Accessors
template<class T>
inline T & Vector<T>::at(int n) {
	if (n < 0 || _size <= n) throw out_of_range();
	return _array[n];
}

template<class T>
inline const T & Vector<T>::at(int n) const {
	if (n < 0 || _size <= n) throw out_of_range();
	return _array[n];
}

template<class T>
inline T & Vector<T>::operator[](int i) {
	return _array[i];
}

template<class T>
inline const T & Vector<T>::operator[](int i) const {
	return _array[i];
}

template<class T>
inline T& Vector<T>::front() {
	return _array[0];
}

template<class T>
inline const T& Vector<T>::front() const {
	return _array[0];
}

template<class T>
inline T& Vector<T>::back() {
	return _array[_size - 1];
}

template<class T>
inline const T& Vector<T>::back() const {
	return _array[_size - 1];
}

template<class T>
inline T* Vector<T>::data() {
	return _array;
}

template<class T>
inline const T* Vector<T>::data() const {
	return _array;
}

class Person {
    public:
        virtual void setVardas(string vardas) = 0;
        virtual void setPavarde(string pavarde) = 0;
        virtual string getVardas() const = 0;
        virtual string getPavarde() const = 0;
    protected:
        string vardas;
        string pavarde;

};

class student: public Person {
    private:
        double vid = 0.0;
    public:
        student();
        student(const student &s);
        bool operator <(const student& s) {
            return vid < s.vid;
        }
        student& operator =(const student &s) {
            setVardas(s.getVardas());
            setPavarde(s.getPavarde());
            setVid(s.getVid());
            return *this;
        }
        ~student();
        void setVardas(string vardas);
        void setPavarde(string pavarde);
        void setVid(double vid);
        string getVardas() const;
        string getPavarde() const;
        double getVid() const;
};

void nuskaitytiDuomenis(Vector<student> &studentai, int n);
//void rusiuotiSarasa(Vector<student> &studentai);
void rusiuotiStudentus(Vector<student> &studentai, Vector<student> &blogi);
void isvestiSarasa(Vector<student> &studentai, string name);
void generuotiSarasa(int n);
void matuotiLaikaVector(Vector<student> &studentai, int n);
// List functions
void nuskaitytiDuomenis(list<student> &studentai, int n);
void rusiuotiSarasa(list<student> &studentai);
void rusiuotiStudentus(list<student> &studentai, list<student> &blogi);
void isvestiSarasa(list<student> &studentai, string name);
void matuotiLaikaList(list<student> &studentai, int n);
// Deque functions
void nuskaitytiDuomenis(deque<student> &studentai, int n);
void rusiuotiSarasa(deque<student> &studentai);
void rusiuotiStudentus(deque<student> &studentai, deque<student> &blogi);
void isvestiSarasa(deque<student> &studentai, string name);
void matuotiLaikaDeque(deque<student> &studentai, int n);
// Testing functions
void rusiuotiStudentusVector(Vector<student> &studentai, Vector<student> &blogi);
bool isBlogas(student &s);




#endif /* HEADER_H */
