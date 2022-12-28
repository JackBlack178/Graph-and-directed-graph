//
// Created by Ilyas on 21.12.2021.
//

#ifndef INC_3LABA_MENUGRAPH_H
#define INC_3LABA_MENUGRAPH_H
#include "Graph.h"
#include "DirectedGraph.h"
#include "menuFunc.h"
#define maxGraphNumberOfNodes 100
#define maxIntWeightOfEdge 100
#define maxIntValueOfNode 1000
#define maxNumberOfEdges 1000
#include "printMenu.h"

using std::cout;
using std::endl;

void createGraph(Graph<int,int>&graph){
    int number;
    cout << "Enter the number of nodes you want to add to graph from 1 to " << maxGraphNumberOfNodes << endl;
    number = getNumberInRange(1,maxGraphNumberOfNodes);
    for (int i = 0; i < number; i++){
        int valueOfNode;
        cout << "Enter value of node from 1 to " << maxIntValueOfNode << endl;
        valueOfNode = getNumberInRange(1,maxIntValueOfNode);
        graph.addNode(valueOfNode);
    }
    cout << "Enter the number of edges you want to add to graph from 0 to " << min(maxNumberOfEdges, ((graph.getNumberOfNodes() - 1) * graph.getNumberOfNodes()/2)) << endl;
    number = getNumberInRange(0, min(maxNumberOfEdges, (graph.getNumberOfNodes() - 1) * graph.getNumberOfNodes()/2));
    if(not number){
        return;
    }

    cout << "Values of nodes" << endl;

    for(int i = 0; i < graph.getValuesOfNodesInARow().getLength(); i++){
        cout << graph.getValuesOfNodesInARow().get(i) << " ";
    }
    cout << endl;

    for(int i = 0; i < number; i++){
        int value1;
        int value2;
        int valueOfEdge;
        cout << "Enter the value of first node you want to connect"<< endl;
        value1 = getNumberInRange(1,maxIntValueOfNode);
        cout << "Enter the value of second node you want to connect" << endl;
        value2 = getNumberInRange(1,maxIntValueOfNode);
        cout << "Enter the value of arc from 1 to " << maxIntWeightOfEdge << endl;
        valueOfEdge = getNumberInRange(1,maxIntWeightOfEdge);
        graph.addEdge(value1,value2,valueOfEdge);
    }
}

void deleteNode(Graph<int,int>&graph){

    if (graph.getNumberOfNodes() == 0){
        cout << "Graph is empty" << endl;
        return;
    }

    cout << "Values of nodes" << endl;

    for(int i = 0; i < graph.getValuesOfNodesInARow().getLength(); i++){
        cout << graph.getValuesOfNodesInARow().get(i) << " ";
    }
    cout << endl;

    cout << "Enter the value of node you want to delete or 0 to cancel" << endl;
    int value = getNumberInRange(0,maxIntValueOfNode);
    if (value == 0){
        return;
    }

    graph.deleteNode(value);
}


void menuGraph(){
    Graph<int,int>graph;
    while(true){
    int manageNumber;
    printMenuActionGraph();
    manageNumber = getNumberInRange(1,5);
        switch(manageNumber){
            case 1:createGraph(graph);break;
            case 2:deleteNode(graph);break;
            case 3:printAdjacencyMatrix(graph.getAdjacencyMatrix(),graph.getValuesOfNodesInARow());break;
            case 4:printAdjacencyMatrix(graph.getAccessibleMatrix(),graph.getValuesOfNodesInARow());break;
            case 5: return;
        }
    }
}




void createDirectedGraph(DirectedGraph<int,int>&graph){
    int number;
    cout << "Enter the number of nodes you want to add to graph from 1 to " << maxGraphNumberOfNodes << endl;
    number = getNumberInRange(1,maxGraphNumberOfNodes);
    for (int i = 0; i < number; i++){
        int valueOfNode;
        cout << "Enter value of node from 1 to " << maxIntValueOfNode << endl;
        valueOfNode = getNumberInRange(1,maxIntValueOfNode);
        graph.addNode(valueOfNode);
    }
    cout << "Enter the number of edges you want to add to graph from 0 to " << min(maxNumberOfEdges, ((graph.getNumberOfNodes() - 1) * graph.getNumberOfNodes()/2)) << endl;
    number = getNumberInRange(0, min(maxNumberOfEdges, (graph.getNumberOfNodes() - 1) * graph.getNumberOfNodes()/2));
    if(not number){
        return;
    }

    cout << "Values of nodes" << endl;

    for(int i = 0; i < graph.getValuesOfNodesInARow().getLength(); i++){
        cout << graph.getValuesOfNodesInARow().get(i) << " ";
    }
    cout << endl;

    for(int i = 0; i < number; i++){
        int value1;
        int value2;
        int valueOfEdge;
        cout << "Enter the value of first node you want to connect"<< endl;
        value1 = getNumberInRange(1,maxIntValueOfNode);
        cout << "Enter the value of second node you want to connect" << endl;
        value2 = getNumberInRange(1,maxIntValueOfNode);
        cout << "Enter the value of arc from 1 to " << maxIntWeightOfEdge << endl;
        valueOfEdge = getNumberInRange(1,maxIntWeightOfEdge);
        graph.addArc(value1,value2,valueOfEdge);
    }
}

void deleteNodeInTheDirectedGraph(DirectedGraph<int,int>&graph){

    if (graph.getNumberOfNodes() == 0){
        cout << "Graph is empty" << endl;
        return;
    }

    cout << "Values of nodes" << endl;

    for(int i = 0; i < graph.getValuesOfNodesInARow().getLength(); i++){
        cout << graph.getValuesOfNodesInARow().get(i) << " ";
    }
    cout << endl;

    cout << "Enter the value of node you want to delete or 0 to cancel" << endl;
    int value = getNumberInRange(0,maxIntValueOfNode);
    if (value == 0){
        return;
    }
    graph.deleteNode(value);
}



void menuDirectedGraph(){
    DirectedGraph<int,int>graph;
    while(true){
        int manageNumber;
        printMenuActionGraph();
        manageNumber = getNumberInRange(1,5);
        switch(manageNumber){
            case 1:createDirectedGraph(graph);break;
            case 2:deleteNodeInTheDirectedGraph(graph);break;
            case 3:printAdjacencyMatrix(graph.getAdjacencyMatrix(),graph.getValuesOfNodesInARow());break;
            case 4:printAdjacencyMatrix(graph.getAccessibleMatrix(),graph.getValuesOfNodesInARow());break;
            case 5: return;
        }
    }
}



#endif //INC_3LABA_MENUGRAPH_H
