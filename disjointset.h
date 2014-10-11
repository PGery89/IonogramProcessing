#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

#include "csv.h"

struct Node
{
    int rank; // This roughly represent the max height of the node in its subtree
    int index; // The index of the element the node represents
    Node * parent; // The parent node of the node
    int treeSize; //Number of elements in tree
};

class DisJointSet
{
public:
    //constructors
    DisJointSet();
    //destructor
    ~DisJointSet();

    //methods
    Node * MakeSet(int i);
    Node * Find(int i);
    Node * Find(Node * node1);
    void Union(Node * node1, Node * node2);
    void Clear();

    //getter
    int CountElements(){ return countElements; }
    int CountSets(){ return countSets; }

private:
    int countElements;
    int countSets;
    std::vector< Node * > points;

};

#endif // DISJOINTSET_H
