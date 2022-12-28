//
// Created by Ilyas on 10.12.2021.
//

#ifndef INC_3LABA_ARRAYSEQUENCE_H
#define INC_3LABA_ARRAYSEQUENCE_H

//
// Created by Ilyas on 13.11.2021.
//

#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "dynamicArray.h"
#include "indexOutOfRangeClass.h"
#include "sequence.h"
template<class T>
class arraySequence : public sequence<T> {
private:
    dynamicArray<T> array;

public:

    arraySequence(T* items, int count) {
        array = dynamicArray<T> (items, count);
    }

    arraySequence() {
        array = dynamicArray<T>();

    }

    explicit arraySequence(T item) {
        array = dynamicArray<T>(&item, 1);
    }

    arraySequence(const arraySequence<T> &newArray) {
        array = newArray.array;
    }

    explicit arraySequence(const dynamicArray<T> &newArray) {
        array = newArray;
    }

    explicit arraySequence(sequence<T>* newSequence) {
        for (int i = 0; i < newSequence->getLength(); i++) {
            append(newSequence->get(i));
        }
    }

    T getFirst() {
        if (getLength() == 0)
            throw IndexOutOfRange();
        return array[0];
    }

    T getLast() {
        if (getLength() == 0)
            throw IndexOutOfRange();
        return array[array.getLength() - 1];
    }

    T& get(int index) {
        if (index < 0 || index >= getLength())
            throw IndexOutOfRange();
        return array.get(index);
    }

    void set(T item, int index) {
        if (index < 0 || index >= getLength())
            throw IndexOutOfRange();
        array.set(item, index);
    }

    T pop() {
        if (array.getLength() == 0)
            throw IndexOutOfRange();


        T item = array[array.getLength() - 1];
        array.resize(array.getLength() - 1);

        return item;
    }

    void swap(int index1, int index2){
        if (index1 >= getLength() || index2 >= getLength() || index1 < 0 || index2 < 0){
            throw IndexOutOfRange();
        }

        if (index1 == index2)
            return;

        array.swap(index1, index2);
    }

    T pop(int index) {
        if (index < 0 || index >= array.getLength())
            throw IndexOutOfRange();

        T item = array[index];
        for (int i = index; i < array.getLength() - 1; i++) {
            array[i] = array[i + 1];
        }
        array.resize(array.getLength() - 1);
        return item;
    }


    T &operator [] (int index) {
        if (index < 0 || index >= getLength())
            throw IndexOutOfRange();
        return array[index];
    }

    T *begin() const {
        return array.begin();
    }

    T *end() const {
        return array.end();
    }

    arraySequence<T> &operator = (arraySequence<T> arraySequence) {
        array = arraySequence.array;
        return *this;
    }

    arraySequence<T> *operator*() {
        return this;
    }

    int operator == (arraySequence<T> arraySequence) {
        return array == arraySequence.array;
    }

    sequence<T>* copySequence(){
        return (new arraySequence<T>(*this));
    }


    int getLength() {
        return array.getLength();
    }

    void append(T item) {
        array.resize(array.getLength() + 1);
        array[getLength() - 1] = item;
    }

    void append(T *item) {
        append(*item);
    }

    void prepend(T item) {
        array.resize(array.getLength() + 1);
        for (int i = array.getLength() - 2; i >= 0; i--) {
            array[i + 1] = array[i];
        }
        array[0] = item;
    }

    void prepend(T *item) {
        prepend(*item);
    }

    void remove() {
        array.resize(0);
    }


    void insert(T item, int index) {
        if (index < 0 || index >= array.getLength())
            throw IndexOutOfRange();
        array.resize(array.getLength() + 1);
        for (int i = array.getLength() - 2; i >= index; i--) {
            array[i + 1] = array[i];
        }
        array[index] = item;
    }

    void insert(T *item, int index) {
        insert(*item, index);
    }

};

template <typename T>
std::ostream& operator << (std::ostream &print, arraySequence<T> &array){
    for (int i = 0; i < array.getLength(); i++){
        std::cout << array.get(i) << std::endl;
    }
}


#endif //LAB2_ARRAYSEQUENCE_H



#endif //INC_3LABA_ARRAYSEQUENCE_H
