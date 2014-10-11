#include "disjointset.h"

//contructor
DisJointSet::DisJointSet()
{
    countElements = 0;
    countSets = 0;
}

//destructor
DisJointSet::~DisJointSet()
{
    for(int i = 0; i < countElements; ++i)
    {
        delete points[i];
    }

    points.clear();
    countElements = 0;
    countSets = 0;
}

//methods
Node * DisJointSet::MakeSet(int i)
{
    if ((unsigned)countElements + 1 > points.size()) {
        points.push_back(new Node);
    }

    points[countElements]->parent = points[countElements];
    points[countElements]->index = i;
    points[countElements]->rank = 0;
    points[countElements]->treeSize = 1;
    countElements++;
    countSets++;

    return points[countElements - 1];
}

Node * DisJointSet::Find(int i)
{
    return Find(points[i - 1]);
}

//Find with path compression
Node * DisJointSet::Find(Node * node1)
{
    if (node1->parent == node1) {
        return node1;
    }
    else {
        node1->parent = Find(node1->parent);
        return node1->parent;
    }
}

//Union with Union-by-rank heuristic
void DisJointSet::Union(Node * node1, Node * node2)
{
    if (node1 == node2) {
        return;
    }

    if (node1->rank < node2->rank)
    {
        node1->parent = node2;
        node2->treeSize += node1->treeSize;
    }
    else if(node1->rank > node2->rank)
    {
        node2->parent = node1;
        node1->treeSize += node2->treeSize;
    }
    else {
        node1->parent = node2;
        node2->treeSize += node1->treeSize;
        node2->rank++;
    }

    countSets--;
}

void DisJointSet::Clear()
{
    points.clear();
    countElements = 0;
    countSets = 0;
}
