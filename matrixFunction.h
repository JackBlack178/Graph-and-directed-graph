//
// Created by Ilyas on 21.12.2021.
//

#ifndef INC_3LABA_MATRIXFUNCTION_H
#define INC_3LABA_MATRIXFUNCTION_H
#include "errors.h"

template <typename T>
void checkDoubleArrayIsSquaredMatrix(arraySequence<arraySequence<T>>matrix){
    int length = matrix.getLength();
    for(int i = 0; i < length; i++){
        if (matrix.get(i).getLength() != length)
            throw MatrixIsNotSquared();
    }
}


template <typename T>
arraySequence<arraySequence<T>> multiplySquaredMatrix(arraySequence<arraySequence<T>>A, arraySequence<arraySequence<T>>B){
    arraySequence<arraySequence<T>> resultMatrix; // Создаем матрицу

    checkDoubleArrayIsSquaredMatrix(A); //Проверяем что матрицы квадратные
    checkDoubleArrayIsSquaredMatrix(B);

    if (A.getLength() != B.getLength())
        throw MatricesHaveDifferentSize();

    for(int i = 0; i < A.getLength(); i++){
        arraySequence<T>array;
        for(int j = 0; j < A.getLength(); j++){
            array.append(0);
        }
        resultMatrix.append(array);
    }  //Создали двойной массив result matrix и заполнили 0

    for(int i=0; i < A.getLength(); i++)
        for(int j=0; j < A.getLength(); j++)
        {
            for(int k=0; k < A.getLength(); k++)
                resultMatrix[i][j]+=A[i][k]*B[k][j];
        }
    return resultMatrix;
}



template <typename T>  // T double,float or int
arraySequence<arraySequence<T>> matrixSquared(arraySequence<arraySequence<T>>matrix){
    return multiplySquaredMatrix(matrix, matrix);
}

template <typename T>
arraySequence<arraySequence<T>>matrixToPowerN(arraySequence<arraySequence<T>>matrix, int n){
    arraySequence<arraySequence<T>>resultMatrix = matrix; //Первая степень. Возводим в n степень, т.е. n-1 раз умножаем ее саму на себя
    for (int i = 0; i < n -1; i++){
        resultMatrix = multiplySquaredMatrix(resultMatrix,matrix);
    }
    return resultMatrix;
}




#endif //INC_3LABA_MATRIXFUNCTION_H
