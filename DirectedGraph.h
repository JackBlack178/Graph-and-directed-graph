//
// Created by Ilyas on 20.12.2021.
//

#ifndef INC_3LABA_DIRECTEDGRAPH_H
#define INC_3LABA_DIRECTEDGRAPH_H
#include "matrixFunction.h"


template <class E, class N>
class NodeOfDirectedGraph;


template <class A, class N>
class Arc{
private:
    A value;
    NodeOfDirectedGraph<A,N> *start = nullptr;
    NodeOfDirectedGraph<N,N> *end = nullptr;
public:
    Arc(NodeOfDirectedGraph<A,N>*startNode, NodeOfDirectedGraph<A,N>*endNode, A valueOfArc){
        value = valueOfArc;
        start = startNode;
        end = endNode;
    }

    Arc<A,N> &operator = (Arc<A,N> arc) {
        *start = *arc.start;
        *end = *arc.end;
        value = arc.value;
    }

    Arc<A,N>(const Arc<A,N> &arc) {
        *start = *arc.start;
        *end = *arc.end;
        value = arc.value;
    }

    int operator == (Arc<A,N> arc){
        return value == arc.value and arc.start == start and arc.end == end;
    }

    A getValueOfArc(){
        return value;
    }

    NodeOfDirectedGraph<A,N>* getStartNode(){
        if (start == nullptr)
            throw NodeIsNullptr();
        return start;
    }

    NodeOfDirectedGraph<A,N>* getEndNode(){
        if (end == nullptr)
            throw NodeIsNullptr();
        return end;
    }

};

template <class A, class N>
class NodeOfDirectedGraph{
private:
    int id;
    arraySequence<Arc<A,N>*> incomingArcs; //Входящие Дуги
    arraySequence<Arc<A,N>*> outComingArcs; //Исходящие Дуги
    N valueOfNode;  // Значение узла

public:
    NodeOfDirectedGraph(int newID, N value){
        id = newID;
        valueOfNode = value;
    }

    N getValue(){
        return valueOfNode;
    }

    int getId(){
        return id;
    }

    arraySequence<Arc<A,N>*> *getIncomingArcs(){
        return &incomingArcs;
    }

    arraySequence<Arc<A,N>*> *getOutComingArcs(){
        return &outComingArcs;
    }

    int isTheSameNode(NodeOfDirectedGraph<A,N>*node){
        return (this == node);
    }


    Arc<A,N>*getArcBetweenThisNodeAndOutComingNodeWithValue(N value){  //From this node to node with value value
        for(int i = 0; i < outComingArcs.getLength(); i++){ //Бежим по всем дугам
            if (outComingArcs.get(i)->getEndNode()->getValue() == value)
                return outComingArcs.get(i);
        }
        return nullptr;
    }

    Arc<A,N>*getArcBetweenThisNodeAndInComingNodeWithValue(N value){  //From node with value value to this node

        for(int i = 0; i < incomingArcs.getLength(); i++){ //Бежим по всем дугам

            if (incomingArcs.get(i)->getStartNode()->getValue() == value)
                return incomingArcs.get(i);
        }
        return nullptr;
    }


    void deleteOutComingArc(Arc<A,N>* arc){
        for (int i = 0; outComingArcs.getLength(); i++){
            if (outComingArcs.get(i) == arc){
                outComingArcs.pop(i);
                return;
            }
        }
    }

    void deleteInComingArc(Arc<A,N>* arc){
        for (int i = 0; incomingArcs.getLength(); i++){
            if (incomingArcs.get(i) == arc){
                incomingArcs.pop(i);
                return;
            }
        }
    }

    A getDistanceBetweenThisNodeAndOutComingNode(NodeOfDirectedGraph<A,N>*node){
        Arc<A,N>* arc = getArcBetweenThisNodeAndOutComingNodeWithValue(node->getValue());
        return arc->getValueOfArc();
    }

    A getDistanceBetweenThisNodeAndInComingNode(NodeOfDirectedGraph<A,N>*node){
        Arc<A,N>* arc = getArcBetweenThisNodeAndInComingNodeWithValue(node->getValue());
        return arc->getValueOfArc();
    }

    int isNodeGoTo(NodeOfDirectedGraph<A,N>*node){
        for(int i = 0; i < outComingArcs.getLength(); i++){
            if (node == outComingArcs.get(i)->getEndNode())
                return 1;
        }
        return 0;
    }

};


template <class A,class N>
class DirectedGraph{
private:
    arraySequence<NodeOfDirectedGraph<A,N>*> nodes; // Указатели на узлы
    int counter = 0; // ID


    void deleteNodePrivate(NodeOfDirectedGraph<A,N>*node){
        for (int i = 0; i < nodes.getLength(); i++){
            if (node->getValue() == nodes.get(i)->getValue()){
                nodes.pop(i);
                return;
            }
        }
    }

public:
    DirectedGraph() = default;


    int getNumberOfNodes(){
        return nodes.getLength();
    }

    void addNode(N valueOfNode){

        if (findIndex(valueOfNode) != -1)
            return;

        auto* node = new NodeOfDirectedGraph<A,N>(counter, valueOfNode);
        nodes.append(node);
        counter++;
    }

    void addArc(N startValue, N endValue, A valueOfArc){
        NodeOfDirectedGraph<A,N>*startNode;
        NodeOfDirectedGraph<A,N>*endNode;

        int res = 0;
        for(int i = 0; i < nodes.getLength(); i++){
            if(startValue == nodes.get(i)->getValue()){
                startNode = nodes.get(i);   // Начальные узел
                res++;
            }

            if(endValue == nodes.get(i)->getValue()){
                endNode = nodes.get(i);  // Конечный узел
                res++;
            }
            if (res == 2)
                break;
        }

        if(res != 2){
            throw ThereIsNoNodesWithTheseValues();
        }

        auto* arc = new Arc<A,N>(startNode, endNode, valueOfArc); // Создали дугу
        startNode->getOutComingArcs()->append(arc);// Добавили в startNode Arc to endNode
        endNode->getIncomingArcs()->append(arc);

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

    int getInComeNodeDegree(N value){
        int index = findIndex(value);
        if (index == -1)
            return -1;
        return nodes.get(index)->getIncomingArcs()->getLength();
    }

    int getOutComeNodeDegree(N value){
        int index = findIndex(value);
        if (index == -1)
            return -1;
        return nodes.get(index)->getOutcomingArcs()->getLength();
    }


    void deleteNode(N value){
        int index = findIndex(value);
        if (index == -1)
            return;

        NodeOfDirectedGraph<A,N>*node = nodes.get(index);  // Указатель на узел который собираемся удалить
        NodeOfDirectedGraph<A,N>*outComingNode = nullptr;
        NodeOfDirectedGraph<A,N>*InComingNode = nullptr;

        for(int i = 0; i < node->getOutComingArcs()->getLength(); i++){  // Удаление всех дуг выходящий из ноды
            outComingNode = node->getOutComingArcs()->get(i)->getEndNode(); // Указатель на ноду исходящую из ноды, которая будет удалена

            if (outComingNode == nullptr){  // Проверка ее на сущестовование, иначе ошибка
                throw DirectedNodeIsEmpty();
            }

            Arc<A,N>*arc = outComingNode->getArcBetweenThisNodeAndInComingNodeWithValue(node->getValue()); //Получили указатель дуги идущей от ноды (1), которая будет удалена, до любой ноды, соединенной с нодой (1)
            if (arc == nullptr) // Проверка на сущестование дуги
                throw ArcIsEmpty();


            outComingNode->deleteInComingArc(arc);
            delete arc;
            arc = nullptr; // Удалили эту дугу и занулили указатель
        }


        for(int i = 0; i < node->getIncomingArcs()->getLength(); i++){ // Удаление всех дуг входящих в ноду

            InComingNode = node->getIncomingArcs()->get(i)->getStartNode(); // Нашли ноду из который мы приходим в ноду (1), которую будем удалять

            if (InComingNode == nullptr){  // Проверка ее на сущестовование, иначе ошибка
                throw DirectedNodeIsEmpty();
            }

            Arc<A,N>*arc = InComingNode->getArcBetweenThisNodeAndOutComingNodeWithValue(node->getValue()); // Нашли дугу между нодой и нодой (1)
            if (arc == nullptr) // Проверка на сущестование дуги
                throw ArcIsEmpty();


            InComingNode->deleteOutComingArc(arc); // Удалили ноду (1) из массива ноды
            delete arc;
            arc = nullptr; // Удалили эту дугу и занулили указатель
        }


        deleteNodePrivate(node); // Удаляем ноду (1) из графа
        delete node;
        node = nullptr;

    }

    arraySequence<arraySequence<int>> getAdjacencyMatrix(){
        arraySequence<arraySequence<int>>arrayOfMatrix;

        for(int i = 0; i< nodes.getLength();i++){
            NodeOfDirectedGraph<A,N>*node = nodes.get(i);
            arraySequence<int>array;
            for(int j = 0; j < nodes.getLength();j++){
                if (node->isNodeGoTo(nodes.get(j)))
                    array.append(1);
                else
                    array.append(0);
            }
            arrayOfMatrix.append(array);
        }

        return arrayOfMatrix;
    }

    arraySequence<arraySequence<A>> getAdjacencyMatrixWithWeights(){
        arraySequence<arraySequence<A>>arrayOfMatrix;

        for(int i = 0; i< nodes.getLength();i++){
            NodeOfDirectedGraph<A,N>*node = nodes.get(i);
            arraySequence<int>array;
            for(int j = 0; j < nodes.getLength();j++){
                if (node->isNodeGoTo(nodes.get(j)))
                    array.append(node->getDistanceBetweenThisNodeAndOutComingNode(nodes.get(j)));
                else
                    array.append(0);
            }
            arrayOfMatrix.append(array);
        }

        return arrayOfMatrix;
    }


    arraySequence<N>getValuesOfNodesInARow(){
        arraySequence<N>array;
        for(int i = 0; i < nodes.getLength();i++){
            array.append(nodes.get(i)->getValue());
        }
        return array;
    }

    arraySequence<arraySequence<int>>getAccessibleMatrix(){
            arraySequence<arraySequence<int>>resultMatrix;
            arraySequence<arraySequence<int>>matrix = getAdjacencyMatrix();
            arraySequence<arraySequence<int>>intermediateMatrix = matrix;


        for(int i = 0; i < matrix.getLength(); i++){
            arraySequence<int>array;
            for(int j = 0; j < matrix.getLength(); j++){
                array.append(0);
            }
            resultMatrix.append(array);
        }

        for(int i = 0; i < matrix.getLength(); i++){
            intermediateMatrix = multiplySquaredMatrix(intermediateMatrix,matrix);

            for(int j = 0; j < intermediateMatrix.getLength(); j++){
                for(int k = 0; k < intermediateMatrix.getLength(); k++){
                    int number = 0;
                    if (intermediateMatrix[j][k] >0){
                        number = 1;
                        resultMatrix[j][k] = 1;
                        continue;
                    }
                }
            }
        }

        for(int i = 0; i < resultMatrix.getLength(); i++){
            resultMatrix[i][i] = 1;
        }

        return resultMatrix;
    };

};



#endif //INC_3LABA_DIRECTEDGRAPH_H
