//
// Created by Ilyas on 13.11.2021.
//

#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include <iostream>
#include "indexOutOfRangeClass.h"

template<class T>
void arrCopy(T *arr_in, T *arr_out, int count);

template <class T>
class dynamicArray {
private:
    T *array;
    int elementSize;
    int length;

public:

    dynamicArray(T *items, int count) {
        array = nullptr;
        elementSize = 0;
        length = 0;
        if (count < 0) {return;}
        resize(count);

        for (int i = 0; i < length; i++) {
            array[i] = items[i];
        }
    }

    explicit dynamicArray(int newSize) {
        elementSize = 0;
        array = nullptr;
        length = 0;
        if (newSize <= 0) { length = 0; return;}
        resize(newSize);
    }

    dynamicArray() {
        array = nullptr;
        length = 0;
        elementSize = 0;
    }

    dynamicArray(const dynamicArray<T> &dynamicArray) {
        array = nullptr;
        elementSize = 0;
        length = 0;
        if (dynamicArray.length == 0) {
            return;
        }
        resize(dynamicArray.length);

        for (int i = 0; i < length; i++) {
            array[i] = dynamicArray.array[i];
        }
    }


    ~dynamicArray() {
        delete[] array;
    }

    int getLength() {
        return length;
    }

    T& get(int index) {
        return (*this)[index];
    }

    int getSize() {
        return elementSize;
    }

    void reverse() {
        for (auto i = 0; i < length / 2; i++) {
            int index = length - 1 - i;
            T item = array[i];
            array[i] = array[index];
            array[index] = item;
        }
    }

    T &operator [] (int index) {
        if (index < 0 || index >= length)
            throw IndexOutOfRange();
        return array[index];
    }

    dynamicArray<T> &operator = (dynamicArray<T> dynamicArray) {
        resize(dynamicArray.length);
        for (int i = 0; i < length; i++) {
            array[i] = dynamicArray.array[i];
        }
        return *this;
    }

    dynamicArray<T> &operator* () {
        return *this;
    }

    int operator == (dynamicArray<T> dynamicArray) {
        if (length != dynamicArray.getLength())
            return 0;

        for (int i = 0; i < length; i++) {
            if (array[i] != dynamicArray.array[i])
                return 0;
        }
        return 1;
    }

    T *begin() const {
        return array;
    }

    T *end() const {
        return array ? array + length : nullptr;
    }

    void set(T item, int index) {
        if (index < 0 || index >= length)
            throw IndexOutOfRange();

        array[index] = item;
    }

    void swap(int index1, int index2){
        if (index1 >= length || index2 >= length)
            throw IndexOutOfRange();

        if (index1 == index2)
            return;

        T temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }

    void resize(int newSize) {
        if (newSize < 0)
            throw IndexOutOfRange();
        if (length == newSize) return;
        if (newSize == 0) {
            if (array != nullptr)
                delete[] array;
            length = 0;
            elementSize = 0;
            array = nullptr;
            return;
        }
        if (newSize > elementSize) {
            if (elementSize == 0) elementSize = 1;
            for (elementSize; elementSize <= newSize + 1; elementSize *= 2);
            int newSize2 = newSize;
            T *arrNew = new T[elementSize];
            if (array != nullptr) {
                arrCopy<T>(arrNew, array, length);
                delete[] array;
            }
            newSize = newSize2;
            array = arrNew;
        }
        else if (newSize < elementSize / 3) {
            for (elementSize; elementSize / 3 > newSize + 1; elementSize /= 2);
            T *arrNew = new T[elementSize];
            if (array != nullptr) {
                arrCopy<T>(arrNew, array, newSize);
                delete[] array;
            }
            array = arrNew;
        }
        length = newSize;
    }
};


template<class T>
void arrCopy(T *arr_in, T *arr_out, int count) {
    for (int i = 0; i < count; i++) {
        arr_in[i] = arr_out[i];
    }
}

#endif //LAB2_DYNAMICARRAY_H
