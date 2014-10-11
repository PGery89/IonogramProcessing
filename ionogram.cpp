#include <QMessageBox>

#include "ionogram.h"
#include <sstream>

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
                y.push_back(j);
            }
            }
    }

    return y;
}

void Ionogram::ComponentLabelingFor(int layer)
{
    if (layer == 0 || layer > 2) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("False attribute!");
        msg.setInformativeText("Layer 1 and 2 can be filtered!");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
        return;
    }
    if (!IsLabeled(layer)) {
        componentLabeling.ProcessImage(layer, & ionogram);
        SetIsLabeled(layer);
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

void Ionogram::GetLabelsCount(int layer, std::vector< int > &labels)
{
    int size = componentLabeling.ds.CountSets();
    int labelsSize[size];

    for (unsigned int i = 1; i < ionogram.size() - 1; ++i) {
        for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
        {
            if (ionogram[i][j].Layer() == layer)
            {
                int current = ionogram[i][j].GetLabel();
                labelsSize[current] += 1;
            }
        }
    }

    //CsvParser::VectorToCSV(ret, "labels");

    std::vector< int > ret(labelsSize, labelsSize + size);

    labels.swap(ret);    
}

std::vector< int > Ionogram::GetLabelsCount(int layer)
{
    int size = componentLabeling.ds.CountSets();
    std::vector< int > labels;

    for (int l = 0; l < size; ++l)
    {
        int increment = 0;
        for (unsigned int i = 1; i < ionogram.size() - 1; ++i) {
            for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
            {
                if (ionogram[i][j].Layer() == layer && ionogram[i][j].GetLabel() == l + 1)
                {
                    increment++;
                }
            }
        }
        labels.push_back(increment);
    }

    return labels;
}

QVector< double > Ionogram::GetLabeledX(int layer, int treshold)
{
    QVector< double > x;
    std::vector< int > labels = GetLabelsCount(layer);

    /*std::vector< int > labels;
    GetLabelsCount(layer, labels);*/

   // CsvParser::VectorToCSV(labels, "labels");

    for (unsigned int k = 0; k < labels.size(); ++k) {
        if (labels[k] >= treshold) {
            for (unsigned int i = 1; i < ionogram.size() - 1; ++i)
            {
                for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
                {
                    if (ionogram[i][j].Layer() == layer && ionogram[i][j].GetLabel() == k + 1)
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
    std::vector< int > labels = GetLabelsCount(layer);

    /*std::vector< int > labels;
    GetLabelsCount(layer, labels);*/

    for (unsigned int k = 0; k < labels.size(); ++k) {
        if (labels[k] >= treshold) {
            for (unsigned int i = 1; i < ionogram.size() - 1; ++i)
            {
                for (unsigned int j = 1; j < ionogram[i].size() - 1; ++j)
                {
                    if (ionogram[i][j].Layer() == layer && ionogram[i][j].GetLabel() == k + 1)
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
    if (layer < 1 || layer > 2) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("False attribute!");
        msg.setInformativeText("Layer 1 and 2 can be filtered!");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    } else if (layer == 1) {
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
