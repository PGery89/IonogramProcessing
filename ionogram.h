#ifndef IONOGRAM_H
#define IONOGRAM_H

#include <QVector>
#include <iostream>
#include <vector>

#include "point.h"
#include "csv.h"
#include "componentlabeling.h"

class Ionogram
{
public:
    Ionogram();
    Ionogram(std::string path);

    QVector< double > GetX(int layer);
    QVector< double > GetY(int layer);
    QVector< double > GetLabeledX(int layer, int treshold);
    QVector< double > GetLabeledY(int layer, int treshold);
    bool IsLabeled(int layer);
    void ComponentLabelingFor(int layer);
    void Clear();

    std::vector< std::vector < Point > > ionogram;
private:
    void ImportIonogram(std::string path);
    std::vector < Point > GetNullRow(int column);    
    void GetLabelsCount(int layer, std::vector< int > &labels);
    std::vector< int > GetLabelsCount(int layer);
    void SetIsLabeled(int layer);

    bool ordComp, exordComp;
    ComponentLabeling componentLabeling;
};

#endif // IONOGRAM_H
