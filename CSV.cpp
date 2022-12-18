#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <string>
#include <algorithm>

class CSVWriter
{
    std::string fileName;
    std::string delimeter;
    int linesCount;
public:
    CSVWriter(std::string filename, std::string delm = ";") :
        fileName(filename), delimeter(delm), linesCount(0)
    {}
    template<typename T>
    void addDatainRow(T first, T last);
};

template<typename T>
void CSVWriter::addDatainRow(T first, T last)
{
    std::fstream file;
    file.open(fileName, std::ios::out | (linesCount ? std::ios::app : std::ios::trunc));
    for (; first != last; )
    {
        file << *first;
        if (++first != last)
            file << delimeter;
    }
    file << "\n";
    linesCount++;
    file.close();
}
void CSWwrite()
{
    CSVWriter writer("example.csv");
    std::vector<std::string> dataList_1 = { "20", "hi", "99" };
    writer.addDatainRow(dataList_1.begin(), dataList_1.end());
    std::set<int> dataList_2 = { 3, 4, 5 };
    writer.addDatainRow(dataList_2.begin(), dataList_2.end());
    std::string str = "abc";
    writer.addDatainRow(str.begin(), str.end());
    int arr[] = { 3,4,1 };
    writer.addDatainRow(arr, arr + sizeof(arr) / sizeof(int));
    return 0;
}

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream;

string readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

void ReadCSV(string filename)
{
    string file_contents;
    std::map<int, std::vector<string>> csv_contents;
    char delimiter = ',';

    file_contents = readFileIntoString(filename);

    istringstream sstream(file_contents);
    std::vector<string> items;
    extern string record;

    int counter = 0;
    while (std::getline(sstream, record)) {
        istringstream line(record);
        while (std::getline(line, record, delimiter)) {
            items.push_back(record);
        }

        csv_contents[counter] = items;
        std::cout << record << endl;
        items.clear();
        counter += 1;
    }

    exit(EXIT_SUCCESS);
}