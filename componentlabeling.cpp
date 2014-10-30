#include "componentlabeling.h"
#include <sstream>

ComponentLabeling::ComponentLabeling()
{
    image = NULL;
}

void ComponentLabeling::ProcessImage(int componentLayer, std::vector< std::vector < Point > > * _image)
{
    if (_image) {
        image = _image;
    }
    else {
        throw;
    }
    AssigningLabels(componentLayer);
    AggregationLables(componentLayer);
}

void ComponentLabeling::Clear()
{
    ds.Clear();
}

//8 connectivity
std::vector< int > ComponentLabeling::GetAllNeighbors(int x, int y, int componentLayer)
{
    std::vector< int > neighbors;

    for (int i = x - 1; i <= x + 1; ++i)
    {
        for (int j = y - 1; j <= y + 1; ++j)
        {
            bool isLayer = (*image)[i][j].Layer() == componentLayer;

            if (isLayer && (*image)[i][j].isLabeled())
            {
                neighbors.push_back((*image)[i][j].GetLabel());
            }
            else
            {
                continue;
            }
        }
    }

    return neighbors;
}

//Just forward scan
std::vector< int > ComponentLabeling::GetFastAllNeighbors(int x, int y, int componentLayer)
{
    std::vector< int > neighbors;
    
    for (int i = x - 1; i <= x; ++i)
    {
        for (int j = y - 1; j <= y + 1; ++j)
        {
            bool isLayer = (*image)[i][j].Layer() == componentLayer;

            if (i == x - 1)
            {
                if (isLayer)
                {
                    neighbors.push_back((*image)[i][j].GetLabel());
                }
                else {
                    continue;
                }
            }
            else
            {
                if (j == y - 1)
                {
                    if (isLayer)
                    {
                        neighbors.push_back((*image)[i][j].GetLabel());
                    }
                    else {
                        break;
                    }
                }
                break;
            }
        }
    }

    return neighbors;
}

void ComponentLabeling::AssigningLabels(int componentLayer)
{
    int nextLabel = 1;

    for (unsigned int i = 1; i < image->size() - 1; ++i)
    {
        for (unsigned int j = 1; j < (*image)[i].size() - 1; ++j)
        {

            int dataLayer = (*image)[i][j].Layer();

            if (dataLayer == componentLayer) {
                std::vector< int > neighbors = GetFastAllNeighbors(i, j, componentLayer);            

                if (neighbors.empty()) {

                    (*image)[i][j].SetLabel(nextLabel);
                    ds.MakeSet(nextLabel);

                    nextLabel++;
                } else {

                    if ( neighbors.size() == 1 )
                    {
                        (*image)[i][j].SetLabel(neighbors[0]);
                    }
                    else
                    {
                        std::sort(neighbors.begin(), neighbors.end());
                        neighbors.erase(std::unique(neighbors.begin(), neighbors.end()), neighbors.end());

                        if (neighbors.size() == 1)
                        {
                            (*image)[i][j].SetLabel(neighbors[0]);
                        }
                        else if(neighbors.size() > 1)
                        {
                            (*image)[i][j].SetLabel(neighbors[0]);

                            for (unsigned int it = 1; it < neighbors.size(); ++it)
                            {
                                ds.Union(ds.Find(neighbors[it]), ds.Find(neighbors[0]));
                            }
                        }
                    }
                }
            }            
        }
    }
}

void ComponentLabeling::AggregationLables(int componentLayer)
{
    for (unsigned int i = 1; i < image->size() - 1; ++i)
    {
        for (unsigned int j = 1; j < (*image)[i].size() - 1; ++j)
        {
            int layer = (*image)[i][j].Layer();

            if (layer == componentLayer)
            {
                int parentLabel = ds.Find((*image)[i][j].GetLabel())->index;

                (*image)[i][j].SetLabel(parentLabel);
            }
        }
    }
}
