#ifndef IONOGRAM_H
#define IONOGRAM_H

#include <QtCore>
#include <QVector>
#include <iostream>
#include <vector>
#include <math.h>

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
    QVector< double > GetXTickLabels();
    QVector< double > GetYTickLabels();
    QVector< double > GetLabeledX(int layer, int treshold);
    QVector< double > GetLabeledY(int layer, int treshold);
    bool IsLabeled(int layer);
    void ComponentLabelingFor(int layer);
    void Clear();

    std::vector< std::vector < Point > > ionogram;

private:
    void ImportIonogram(std::string path);
    std::vector < Point > GetNullRow(int column);    
    void SetLabelsCount(int layer);
    void SetIsLabeled(int layer);

    //test
    std::vector< int > GetLabelsCount(int layer);

    int GetVirtualHeight(int h);

    bool ordComp, exordComp;
    ComponentLabeling componentLabeling;
    std::vector< int > labelsCountOrd;
    std::vector< int > labelsCountXOrd;

    static const int CC = 299792458;
    static const double deltaT = 0.000005;
};

#endif // IONOGRAM_H
