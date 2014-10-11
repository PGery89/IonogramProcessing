#ifndef COMPONENTLABELING_H
#define COMPONENTLABELING_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "point.h"
#include "csv.h"
#include "disjointset.h"


class ComponentLabeling
{
public:
    ComponentLabeling();

    DisJointSet ds;

    void ProcessImage(int componentLayer, std::vector< std::vector < Point > > * _image);
    void Clear();

private:
    std::vector< std::vector < Point > > * image;

    void AssigningLabels(int componentLayer);
    void AggregationLables(int componentLayer);

    std::vector< int > GetFastAllNeighbors(int i, int j, int layer);
    std::vector< int > GetAllNeighbors(int i, int j, int layer);
};

#endif // COMPONENTLABELING_H
