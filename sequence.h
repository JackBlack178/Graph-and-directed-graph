//
// Created by Ilyas on 13.11.2021.
//

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

template<typename T>
class sequence {
public:
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T& get(int index) = 0;
    virtual T&  operator [] (int index) = 0;
    virtual void set(T value, int index) = 0;
    virtual void insert (T value, int index) = 0;
    virtual void swap(int index1, int index2) = 0;
    virtual int getLength() = 0;
    virtual void append (T value) = 0;
    virtual T pop() = 0;
    virtual T pop(int index) = 0;
    virtual sequence<T>* copySequence() = 0;

    sequence<T>& operator = (const sequence<T>& newSequence) {
        if (getLength() < newSequence.getLength()) {
            for (int i = 0; i < getLength(); i++)
                operator[](i) = newSequence[i];

            for (int i = getLength(); i < newSequence.getLength(); i++)
                append(newSequence[i]);
        }

        else {
            for (int i = 0; i < newSequence.getLength(); i++)
                operator[](i) = newSequence[i];


            for (int i = newSequence.getLength(); i < getLength(); i++)
                pop();
        }
        return *this;
    }

};

#endif //LAB2_SEQUENCE_H
