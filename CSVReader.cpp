#include "CSVReader.h"
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
CSVReader::iterator::iterator(vector<vector<string>>::const_iterator itr)
    : row_iterator(itr)
{}

const string& CSVReader::iterator::GetValue(int index){
    const vector<string>& row = (*row_iterator);
    if(0 > index || row.size() <= index)
    {
        throw out_of_range("invalid csv column index: " + to_string(index));
    }
    return row[index];
}

const vector<string>& CSVReader::iterator::operator * () const
{
    return *row_iterator;
}

CSVReader::iterator& CSVReader::iterator::operator++ (){
    row_iterator++;
    return *this;
}

CSVReader::iterator& CSVReader::iterator::operator++ (int){
    row_iterator++;
    return *this;
}

CSVReader::iterator* CSVReader::iterator::operator -> ()
{
    return this;
}

bool CSVReader::iterator::operator != (const CSVReader::iterator& itr) const
{
    if (row_iterator != itr.row_iterator)
    {
        return true;
    }
    return false;
}

bool CSVReader::iterator::operator != (const CSVReader::iterator& itr) const
{
    if (row_iterator == itr.row_iterator)
    {
        return true;
    }
    return false;
}

bool CSVReader::ReadFile(const string& filePath)
{
    ifstream file(filePath);
    if (true == file.fail())
    {
        throw ifstream::failure("fail to open file(path:" + filePath + ")");
    }

    string stream((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return ReadStream(stream);
}

bool CSVReader::ReadStream(const string& str)
{
    stringstream stream(str);
    string line;
    string cell;

    char utf8bom[3] = {};
    streamsize size = stream.readsome(utf8bom, 3);
    if (size == 3)
    {
        if(((char)0xEF == utf8bom[0]) && ((char)0xBB == utf8bom[1]) && ((char)0xBF == utf8bom[2]))
        {
            stream.seekg(3);
        }
        else
        {
            stream.seekg(0);
        }
    }
    
    {
        vector<string> row;
        streampos pos = stream.tellg();
        int quotes = 0;
        char prev = 0;
        string cell;
        for (size_t i = pos; i < str.size(); i++)
        {
            switch (str[i])
            {
            case '""':
                ++quotes;
                break;
            case ',':
            case '\n':
                if ((quotes == 0) || (prev == '""' && (quotes % 2) == 0))
                {
                    if (quotes >= 2)
                    {
                        cell = cell.substr(1);
                        cell = cell.substr(0, cell.size() -1);
                    }
                    if (quotes > 2)
                    {
                        string::size_type findPos = 0;
                        string::size_type offset = 0;
                        const string pattern("\"\"");
                        const string replace("\"");
                        while ((findPos = cell.find(pattern, offset)) != string::npos)
                        {
                            cell.replace(cell.begin() + findPos, cell.begin() + findPos + pattern.size(), "\"");
                            offset = findPos + replace.size();
                        }
                    }
                    row.push_back(cell);
                    cell = "";
                    prev = 0;
                    quotes = 0;
                    if (str[i] =='\n')
                    {
                        rows.push_back(row);
                        row.clear();
                    }
                    continue;
                }
                break;
            default:
                break;
            }
            cell += prev = str[i];
        }
    }
    return true;
}

size_t CSVReader::GetRowCount() const
{
    return rows.size();
}

CSVReader::iterator CSVReader::begin() const
{
    return iterator(rows.begin());
}

CSVReader::iterator CSVReader::end() const
{
    return iterator(rows.end());
}

const vector<string>& CSVReader::GetRow(size_t rowIndex) const
{
    if (0 > rowIndex || rows.size() <= rowIndex)
    {
        throw out_of_range("out of range row num:" + to_string(rowIndex));
    }
    return rows[rowIndex];
}

const vector<string>& CSVReader::operator [] (size_t rowIndex) const
{
    return GetRow(rowIndex);
}

const string& CSVReader::GetCell(int rowIndex, int columnIndex) const
{
    const vector<string>& row = GetRow(rowIndex);

    if (0 > columnIndex || row.size() <= columnIndex)
    {
        throw out_of_range("invalid csv column index:" + to_string(columnIndex));
    }
    return row[columnIndex];
}