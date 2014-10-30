#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "point.h"

class CsvParser
{
    public:
        static std::vector< std::vector< int > > ReadCSV(std::string path, char separator);
        static void WriteCSV(std::vector<std::vector<Point> > ionogram, std::string name, char separator);
        static void WriteCSV(std::map< int, std::vector< Point > > labels, std::string name, char separator);
        static void LogCSV(std::string var_name, std::string var_value, std::string var_address);
        static void LogCSV(std::string log);
        static void StrToCsv(std::string _file, std::string st);
        static void VectorToCSV(std::vector< int > labels, std::string name);
        static void VectorToCSV(std::vector< int > * labels, std::string name);
};

#endif // CSV_H
