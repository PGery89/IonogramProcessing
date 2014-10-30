#include "csv.h"

using namespace std;

std::vector< std::vector< int > > CsvParser::ReadCSV(std::string path, char separator)
{
    std::vector< std::vector< int > > matrix;
    std::vector< int > row;
    std::string line;
    std::string cell;

    std::ifstream file (path.c_str());

    while( file )
    {
        std::getline(file,line);
        std::stringstream lineStream(line);
        row.clear();

        while( std::getline( lineStream, cell, separator ) )
        {
            //string to int
            int value;
            istringstream ( cell ) >> value;

            row.push_back( value );

        }

        if( !row.empty() )
            matrix.push_back( row );
    }

    file.close();

    return matrix;
}

void CsvParser::WriteCSV(std::vector< std::vector< Point > > ionogram, std::string name, char separator)
{
    std::string path = "d:\\" + name + ".csv";
    ofstream out(path.c_str());

    if (out.is_open()) {
        for (unsigned int i = 0; i < ionogram.size(); ++i)
        {
            for (unsigned int j = 0; j < ionogram[i].size(); ++j)
            {
                if (j != ionogram[i].size() - 1)
                {
                    out << ionogram[i][j].GetLabel() << separator;
                } else
                {
                    out << ionogram[i][j].GetLabel();
                }
            }
            out << '\n';
        }
    } else {
        std::cout << "Unable to open." << endl;
    }
    out.close();
}

void CsvParser::WriteCSV(std::map< int, std::vector< Point > > labels, std::string name, char separator)
{
    std::string path = "d:\\" + name + ".csv";
    ofstream out(path.c_str());

    if (out.is_open()) {
        for (std::map< int, std::vector< Point > >::iterator it=labels.begin(); it != labels.end(); ++it)
        {
            std::vector<Point> tempVec = (*it).second;
            int Key = (*it).first;
            out << Key << separator;
            for (unsigned i = 0; i < tempVec.size(); i++) {
              out << tempVec[i].GetLabel() << separator;
            }
            out << '\n';
        }
    } else {
        std::cout << "Unable to open." << endl;
    }
    out.close();
}

void CsvParser::LogCSV(std::string var_name, std::string var_value, std::string var_address)
{
    ofstream log;

     log.open("d:\\log.txt", ios::app);

    if (log.is_open()) {
        log << "name: " << var_name << ", address: " << var_value << ", value: " << var_address << '\n';
    } else {
        std::cout << "Unable to open." << endl;
    }
    log.close();
}


void CsvParser::LogCSV(std::string _log)
{
    ofstream log;

    log.open("d:\\log.txt", ios::app);

    if (log.is_open()) {
        log << _log << '\n';
    } else {
        std::cout << "Unable to open." << endl;
    }
    log.close();
}

void CsvParser::StrToCsv(std::string _file, std::string st)
{
    std::string filename = "d:\\" + _file + ".txt";
    ofstream file;
    file.open(filename.c_str(), ios::app);

    if (file.is_open()) {
        file << st << '\n';
    } else {
        std::cout << "Unable to open." << endl;
    }
    file.close();
}

void CsvParser::VectorToCSV(std::vector<int> labels, string name)
{
    std::string path = "d:\\" + name + ".csv";
    ofstream out(path.c_str());

    if (out.is_open()) {
        for(std::vector< int >::const_iterator i = labels.begin(); i != labels.end(); ++i) {
            out << "label size: " << *i << '\n';
        }
        /*for (unsigned int i = 0; i < labels.size(); ++i)
        {
            out << i << ". label size: "<< labels[i] << '\n';
        }*/
    } else {
        std::cout << "Unable to open." << endl;
    }
    out.close();
}

void CsvParser::VectorToCSV(std::vector<int> *labels, string name)
{
    std::string path = "d:\\" + name + ".csv";
    ofstream out(path.c_str());

    if (out.is_open()) {
        /*for(std::vector< int >::const_iterator i = labels->begin(); i != labels->end(); ++i) {
            out << "label size: " << *i << '\n';
        }*/
        for (unsigned int i = 0; i < labels->size(); ++i)
        {
            out << i << ". label size: "<< labels->operator [](i) << '\n';
        }
    } else {
        std::cout << "Unable to open." << endl;
    }
    out.close();
}
