#include <QMessageBox>

#include "ionogram.h"
#include <sstream>
#include <typeinfo>

Ionogram::Ionogram()
{
}

Ionogram::Ionogram(std::string path)
{
    ImportIonogram(path);
    componentLabeling = ComponentLabeling();
    ordComp = false;
    exordComp = false;
}

void Ionogram::Clear()
{
    ionogram.clear();
    componentLabeling.Clear();
}

void Ionogram::ImportIonogram(std::string path)
{
    std::vector< std::vector< int > > matrix = CsvParser::ReadCSV(path, ' ');
    std::vector< Point > row;

    //first and last rows and columns get null value, because of the neighbors search
    Point vergePoint(0,0,0);

    this->ionogram.push_back(GetNullRow(matrix[0].size()));

    for (unsigned int i = 0; i < matrix.size(); ++i) {
        row.clear();
        int mhz = matrix[0][0];

        row.push_back(vergePoint);
        for (unsigned int j = 1; j < matrix[i].size(); ++j) {
            Point xy(mhz, j, matrix[i][j]);
            row.push_back(xy);
        }
        row.push_back(vergePoint);

        this->ionogram.push_back(row);
    }
    this->ionogram.push_back(GetNullRow(matrix[0].size()));
}

QVector< double > Ionogram::GetX(int layer)
{
    QVector< double > x;

    for (unsigned int i = 1; i < ionogram.size() - 1; ++i) {
        for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j) {
            if (ionogram[i][j].Layer() == layer) {
                //x.push_back(GetVirtualHeight(i));
                x.push_back(i);
            }
            }
    }

    return x;
}

QVector< double > Ionogram::GetY(int layer)
{
    QVector< double > y;

    for (unsigned int i = 1; i < ionogram.size() - 1; ++i) {
        for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j) {
            if (ionogram[i][j].Layer() == layer) {
                //y.push_back(1000 + (j-1) * 25);
                y.push_back(j);
            }
            }
    }

    return y;
}

int Ionogram::GetVirtualHeight(int h)
{
    double height = ((double)h * CC * deltaT)/2.0;

    if (height < 0) {
        qDebug( )<< "h param, height: " << h << height;
    }

    return round(height);
}

QVector< double > Ionogram::GetXTickLabels()
{
    QVector< double > x;
    for (unsigned int j = 1; j < ionogram.size() - 1; ++j)
    {
        x.push_back(1000 + (j - 1) * 25);
    }
    return x;
}

QVector< double > Ionogram::GetYTickLabels()
{
    QVector< double > y;
    for (unsigned int i = 1; i < ionogram[1].size() - 1; ++i)
    {
        y.push_back(GetVirtualHeight(i)/1000);
    }
    return y;
}

void Ionogram::ComponentLabelingFor(int layer)
{
    if (!IsLabeled(layer)) {
        componentLabeling.ProcessImage(layer, & ionogram);
        SetIsLabeled(layer);
        SetLabelsCount(layer);
    } else {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Information);
        msg.setText("Every layer are filtered");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}

std::vector < Point > Ionogram::GetNullRow(int column)
{
    std::vector< Point > row;
    Point vergePoint(0,0,0);

    for (int i = 0; i < column + 1; ++i) {
        row.push_back(vergePoint);
    }

    return row;
}

/*test version method
void Ionogram::GetLabelsCount(int layer, std::vector< int > &labels)
{
    const int size = componentLabeling.ds.CountSets();
    int * labelsSize(new int[size]);

    unsigned int column = ionogram.size() - 1;
    unsigned int row = ionogram[0].size() - 1;

    for (unsigned int i = 1; i < column; ++i) {
        for (unsigned int j = 1; j < row; ++j)
        { 
            if (ionogram[i][j].Layer() == layer)
            {
                int current = ionogram[i][j].GetLabel();
                labelsSize[current] += 1;
            }
        }
    }

    //CsvParser::VectorToCSV(ret, "labels");
    //std::vector< int > ret(labelsSize, labelsSize + size);
    //labels.swap(ret);

    labels.resize(size);
    std::copy(labelsSize, labelsSize + size, labels.begin());
    delete labelsSize;
}*/

void Ionogram::SetLabelsCount(int layer)
{
    int size = componentLabeling.ds.CountSets();
    std::vector< int > * labels;

    if (layer == 1) {
        labels = & labelsCountOrd;
    } else if (layer == 2) {
        labels = & labelsCountXOrd;
    }

    for (int var = 0; var < size; ++var) {
        labels->push_back(0);
    }

    for (unsigned int i = 1; i < ionogram.size() - 1; ++i) {
        for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
        {
            if (ionogram[i][j].Layer() == layer)
            {
                labels->operator [](ionogram[i][j].GetLabel()) += 1;
                //labels[ionogram[i][j].GetLabel()] += 1;
            }
        }
    }

    //for (int var = 0; var < size; ++var) {
    //    qDebug( )<< var << ". " << labels->operator [](var);
    //}
}

std::vector< int > Ionogram::GetLabelsCount(int layer)
{
    int size = componentLabeling.ds.CountSets();
    std::vector< int > labels(size, 0);

    for (unsigned int i = 1; i < ionogram.size() - 1; ++i) {
        for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
        {
            if (ionogram[i][j].Layer() == layer)
            {
                labels[ionogram[i][j].GetLabel()] += 1;
            }
        }
    }

    return labels;
}

QVector< double > Ionogram::GetLabeledX(int layer, int treshold)
{
    QVector< double > x;
    std::vector< int > * labels;

    if (layer == 1) {
        labels = & labelsCountOrd;
    } else if (layer == 2) {
        labels = & labelsCountXOrd;
    }

    for (unsigned int k = 0; k < labels->size(); ++k) {
        if (labels->operator [](k) >= treshold) {
            for (unsigned int i = 1; i < ionogram.size() - 1; ++i)
            {
                for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
                {
                    if (ionogram[i][j].Layer() == layer && ionogram[i][j].GetLabel() == k)
                    {

                        x.push_back(i);
                    }
                }
            }
        }
    }

    return x;
}

QVector< double > Ionogram::GetLabeledY(int layer, int treshold)
{
    QVector< double > y;
    std::vector< int > * labels;

    if (layer == 1) {
        labels = & labelsCountOrd;
    } else if (layer == 2) {
        labels = & labelsCountXOrd;
    }

    for (unsigned int k = 0; k < labels->size(); ++k) {
        if (labels->operator [](k) >= treshold) {
            for (unsigned int i = 1; i < ionogram.size() - 1; ++i)
            {
                for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
                {
                    if (ionogram[i][j].Layer() == layer && ionogram[i][j].GetLabel() == k)
                    {                       
                        y.push_back(j);
                    }
                }
            }
        }
    }

    return y;
}

bool Ionogram::IsLabeled(int layer)
{
    if (layer == 1) {
        return ordComp;
    } else {
        return exordComp;
    }
}

void Ionogram::SetIsLabeled(int layer)
{
    if (layer == 1) {
        ordComp = true;
    } else {
        exordComp = true;
    }
}
