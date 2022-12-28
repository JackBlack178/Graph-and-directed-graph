//
// Created by Ilyas on 20.12.2021.
//

#ifndef INC_3LABA_PRINTMENU_H
#define INC_3LABA_PRINTMENU_H
#include "arraySequence.h"

template <typename N>
void printAdjacencyMatrix(arraySequence<arraySequence<int>>arrayOfMatrix, arraySequence<N>valuesOfNodes){


    for(int i = 0; i < valuesOfNodes.getLength(); i++){
        std::cout << valuesOfNodes.get(i) << "  ";
    }
    std::cout<<std::endl;
    for(int i = 0; i < arrayOfMatrix.getLength(); i++){
        for(int j = 0; j < arrayOfMatrix.get(i).getLength();j++){
            std::cout << arrayOfMatrix.get(i).get(j) << "  ";
        }
        std::cout<<std::endl;
    }
}

template <typename T>
void printMatrix(arraySequence<arraySequence<T>>arrayOfMatrix){
    for(int i = 0; i < arrayOfMatrix.getLength(); i++){
        for(int j = 0; j < arrayOfMatrix.get(i).getLength();j++){
            std::cout << arrayOfMatrix.get(i).get(j) << "  ";
        }
        std::cout<<std::endl;
    }
}

void printMenuActionGraph(){
    std::cout << "To add nodes and add edges - 1" << std::endl;
    std::cout << "To delete nodes - 2" << std::endl;
    std::cout << "To print adjacency matrix -3"<< std::endl;
    std::cout << "To print reachable matrix - 4"<< std::endl;
    std::cout << "To quit - 5"<< std::endl;
}


#endif //INC_3LABA_PRINTMENU_H
