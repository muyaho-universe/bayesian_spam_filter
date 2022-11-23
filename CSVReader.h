#ifndef _CSV_READER_H_
#define _CSV_READER_H_

#include <map>
#include <vector>
#include <string>

using namespace std;

class CSVReader
{
private:
    vector<vector<string>> rows;
public:
    class iterator
    {
    private:
       vector<vector<string>> row_iterator;
    public:
        iterator(vector<vector<string>> itr);

        const vector<string>& operator * () const;
        iterator& operator ++ ();
        iterator& operator ++ (int);
        iterator* operator -> ();
        bool operator != (const iterator& itr) const;
        bool operator == (const iterator& itr) const;
        const string& GetValue(int index);
    };
    typedef iterator Row;
public:
    bool ReadFile(const string& filePath);
    bool ReadStream(const string& steam);

    size_t GetRowCount() const;
    const vector<string>& GetRow(size_t rowIndex) const;
    const string& GetCall(int rowIndex, int columnIndex) const;
    const vector<string>& operator [](size_t rowInex) const;
    
   	iterator begin() const;
	iterator end() const;
};

#endif