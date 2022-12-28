//
// Created by Ilyas on 10.12.2021.
//

#ifndef INC_3LABA_GRAPH_H
#define INC_3LABA_GRAPH_H
#include "arraySequence.h"
#include "errors.h"
#include "matrixFunction.h"
template <class A, class N>
class Node;


template <class E, class N>
class Edge{
private:
    E value;
    Node<E,N> *node1 = nullptr;
    Node<E,N> *node2 = nullptr;
public:
    Edge(Node<E,N>*start, Node<E,N>*end, E valueOfEdge){
        value = valueOfEdge;
        node1 = start;
        node2 = end;
    }


    Edge<E,N> &operator = (Edge<E,N> edge) {
        *node1 = *edge.node1;
        *node2 = *edge.node2;
        value = edge.value;
    }

    Edge<E,N>(const Edge<E,N> &edge) {
        *node1 = *edge.node1;
        *node2 = *edge.node2;
        value = edge.value;
    }

    ~Edge() = default;

    int operator == (Edge<E,N> edge){
        return value == edge.value and (edge.node1 == node1 and edge.node2 == node2 or edge.node1 == node2 and edge.node2 == node1);
    }

    E getValueOfEdge(){
        return value;
    }

    Node<E,N>* getNode1(){
        if (node1 == nullptr)
            throw NodeIsNullptr();
        return node1;
    }

    Node<E,N>* getNode2(){
        if (node2 == nullptr)
            throw NodeIsNullptr();
        return node2;
    }

};



template <class E, class N>
class Node{
private:
    int id;
    arraySequence<Edge<E,N>*> edges;
    N valueOfNode;


public:
    Node(int newID, N value){
        id = newID;
        valueOfNode = value;
    }

    N getValue(){
        return valueOfNode;
    }

    int getId(){
        return id;
    }

    arraySequence<Edge<E,N>*> *getEdges(){
        return &edges;
    }

    int isTheSameNode(Node<E,N>*node){
        return (this == node);
    }

    int isNodesConnected(Node<E,N>*node){
        for(int i = 0; i < edges.getLength();i++) {
            if (edges.get(i)->getNode1() == node and not isTheSameNode(node))
                return 1;

            if (edges.get(i)->getNode2() == node and not isTheSameNode(node))
                return 1;
        }

        return 0;
    }

    Edge<E,N>*getEdgeBetweenThisNodeAndNodeWithValue(N value){
        for(int i = 0; i < edges.getLength(); i++){ //Бежим по всем дугам
            if (edges.get(i)->getNode1()->getValue() == value and not isTheSameNode(edges.get(i)->getNode1()))
                return edges.get(i);

            if (edges.get(i)->getNode2()->getValue() == value and not isTheSameNode(edges.get(i)->getNode2()))
                return edges.get(i);
        }
        return nullptr;
    }

    void deleteEdge(Edge<E,N>* edge){
        for (int i = 0; edges.getLength(); i++){
            if (edges.get(i) == edge){
                edges.pop(i);
                return;
            }
        }
    }

    E getDistanceBetweenThisNodeAndNode(Node<E,N>*node){
        Edge<E,N>* edge = getEdgeBetweenThisNodeAndNodeWithValue(node->getValue());
        return edge->getValueOfEdge();
    }
};


template <class E,class N>
class Graph{
private:
    arraySequence<Node<E,N>*> nodes; // Указатели на узлы
    int counter = 0; // ID


    void deleteNodePrivate(Node<E,N>*node){
        for (int i = 0; i < nodes.getLength(); i++){
            if (node->getValue() == nodes.get(i)->getValue()){
                nodes.pop(i);
                return;
            }
        }
    }

public:
    Graph() = default;


    int getNumberOfNodes(){
        return nodes.getLength();
    }

    void addNode(N valueOfNode){

        if (findIndex(valueOfNode) != -1)
            return;

        auto* node = new Node<E,N>(counter, valueOfNode);
        nodes.append(node);
        counter++;
    }

    void addEdge(N value1, N value2, E valueOfEdge){
        Node<E,N>*startNode;
        Node<E,N>*endNode;

        int res = 0;
        for(int i = 0; i < nodes.getLength(); i++){
            if(value1 == nodes.get(i)->getValue()){
                startNode = nodes.get(i);
                res++;
            }

            if(value2 == nodes.get(i)->getValue()){
                endNode = nodes.get(i);
                res++;
            }
            if (res == 2)
                break;
        }

        if(res != 2){
            throw ThereIsNoNodesWithTheseValues();
            return;
        }

        auto* edge = new Edge<E,N>(startNode, endNode, valueOfEdge);
        startNode->getEdges()->append(edge);
        endNode->getEdges()->append(edge);
    }

    int findIndex(N value) {
        int index = -1;
        for (int i = 0; i < nodes.getLength(); i++) {
            if (nodes.get(i)->getValue() == value) {
                index = i;
                return index;
            }
        }
        return index;
    }

    void deleteNode(N value){
        int index = findIndex(value);
        if (index == -1)
            return;

        Node<E,N>*node = nodes.get(index);  // Указатель на узел который собираемся удалить
        Node<E,N>*otherNode = nullptr;

        for(int i = 0; i < node->getEdges()->getLength(); i++){

            if (node->getEdges()->get(i)->getNode1() != node)   // Получаем ноду, соединенную с нодой, которую собираемся удалить
                otherNode = node->getEdges()->get(i)->getNode1(); // Проверяем, что это именна соединеная нода, а не таже самая.
            if (node->getEdges()->get(i)->getNode2() != node)
                otherNode = node->getEdges()->get(i)->getNode2();
            if (otherNode == nullptr)
                throw NodeIsEmpty();

            Edge<E,N>*edge = otherNode->getEdgeBetweenThisNodeAndNodeWithValue(node->getValue()); //Получили указатель дуги между другой нодой и нодой, которая будет удалена
            if (edge == nullptr)
                throw EdgeIsEmpty();


            otherNode->deleteEdge(edge);
            delete edge;
            edge = nullptr; // Удалили эту дугу и занулили указатель
        }
        deleteNodePrivate(node);  // Удалили ноду из массива
        delete node;  // Удалили ноду и занулили указатель
        node = nullptr;
    }


    int getNodeDegree(N value){
        int index = findIndex(value);
        if (index == -1)
            return -1;
        return nodes.get(index)->getEdges()->getLength();
    }


    arraySequence<arraySequence<int>> getAdjacencyMatrix(){
        arraySequence<arraySequence<int>>arrayOfMatrix;

        if (getNumberOfNodes() == 0)
            throw GraphIsEmpty();

        for(int i = 0; i< nodes.getLength();i++){
            Node<E,N>*node = nodes.get(i);
            arraySequence<int>array;
            for(int j = 0; j < nodes.getLength();j++){
                if (node->isNodesConnected(nodes.get(j)))
                    array.append(1);
                else
                    array.append(0);
            }
            arrayOfMatrix.append(array);
        }

        return arrayOfMatrix;
    }

    arraySequence<arraySequence<E>> getAdjacencyMatrixWithWeights(){
        arraySequence<arraySequence<E>>arrayOfMatrix;

        if (getNumberOfNodes() == 0)
            throw GraphIsEmpty();

        for(int i = 0; i< nodes.getLength();i++){
            Node<E,N>*node = nodes.get(i);
            arraySequence<int>array;
            for(int j = 0; j < nodes.getLength();j++){
                if (node->isNodesConnected(nodes.get(j)))
                    array.append(node->getDistanceBetweenThisNodeAndNode(nodes.get(j)));
                else
                    array.append(0);
            }
            arrayOfMatrix.append(array);
        }

        return arrayOfMatrix;
    }


    arraySequence<N>getValuesOfNodesInARow(){

        if (getNumberOfNodes() == 0)
            throw GraphIsEmpty();

        arraySequence<N>array;
        for(int i = 0; i < nodes.getLength();i++){
            array.append(nodes.get(i)->getValue());
        }
        return array;
    }


    arraySequence<arraySequence<int>>getAccessibleMatrix(){  // Матрица достижимости
        if (getNumberOfNodes() == 0)
            throw GraphIsEmpty();

        arraySequence<arraySequence<int>>resultMatrix;  //Конечная матрица достижимости
        arraySequence<arraySequence<int>>matrix = getAdjacencyMatrix(); // Матрица смежности
        arraySequence<arraySequence<int>>intermediateMatrix = matrix; //Промежуточная матрица


        for(int i = 0; i < matrix.getLength(); i++){
            arraySequence<int>array;
            for(int j = 0; j < matrix.getLength(); j++){
                array.append(0);
            }
            resultMatrix.append(array);
        }

        for(int i = 0; i < matrix.getLength(); i++){
            intermediateMatrix = multiplySquaredMatrix(intermediateMatrix,matrix); // Возвели матрицу в i степень.

            for(int j = 0; j < intermediateMatrix.getLength(); j++){
                for(int k = 0; k < intermediateMatrix.getLength(); k++){   //Выполняем здесь дизъюнктивное сложение для каждой компоненты
                    int number = 0;
                    if (intermediateMatrix[j][k] >0){
                        number = 1;
                        resultMatrix[j][k] = 1;
                        continue;
                    }
                }
            }
        }

        for(int i = 0; i < resultMatrix.getLength(); i++){  // Складываем единичную матрицу размера resultMatrix.getLength() X resultMatrix.getLength()
            resultMatrix[i][i] = 1;
        }
        return resultMatrix;
    };
};








#endif //INC_3LABA_GRAPH_H
