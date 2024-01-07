#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <windows.h>

// Struct that represents information about a street
struct Street
{
    char streetName[50];
    char streetType[20];
    char schemeLeft;
    int fromLeft;
    int toLeft;
    char schemeRight;
    int fromRight;
    int toRight;
};

// Struct that represents information about the house numbering of a segment of a street
struct HouseNumberRange
{
    char scheme;
    int numFrom;
    int numTo;
};

// Makes a Street object from the line parameter
Street processLine(std::string &line)
{
    line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());

    std::vector<std::string> strings;
    std::string word;
    std::stringstream ss(line);

    while (!ss.eof())
    {
        std::getline(ss, word, ',');
        strings.push_back(word);
    }

    Street st;
    strcpy(st.streetName, strings[16].c_str());
    strcpy(st.streetType, strings[17].c_str());
    st.schemeLeft = strings[20][0];
    st.fromLeft = stoi(strings[21]);
    st.toLeft = stoi(strings[22]);
    st.schemeRight = strings[23][0];
    st.fromRight = stoi(strings[24]);
    st.toRight = stoi(strings[25]);

    return st;
}

// Reads the file given in the parameter into a vector of Streets
std::vector<Street> readFile(const std::string &filename)
{
    std::vector<Street> streets;
    std::string line;
    std::ifstream file(filename);

    if (!file)
    {
        std::cerr << "Error opening the file." << std::endl;
    }

    while (std::getline(file, line, '\n'))
    {
        Street st = processLine(line);
        streets.push_back(st);
    }
    file.close();

    return streets;
}

// Generates a map with the street name as key and a vector of house number ranges as value
std::unordered_map<std::string, std::vector<HouseNumberRange>> generateStreetNumbersMap(const std::vector<Street> &streets)
{
    std::unordered_map<std::string, std::vector<HouseNumberRange>> streetNumbers;

    for (int i = 0; i < streets.size(); i++)
    {
        if (*streets[i].streetName == 0)
            continue;

        if (streets[i].schemeLeft != '\0')
        {
            streetNumbers[(std::string)streets[i].streetName + " " + streets[i].streetType].push_back((HouseNumberRange){streets[i].schemeLeft, streets[i].fromLeft, streets[i].toLeft});
        }
        if (streets[i].schemeRight != '\0')
        {
            streetNumbers[(std::string)streets[i].streetName + " " + streets[i].streetType].push_back((HouseNumberRange){streets[i].schemeRight, streets[i].fromRight, streets[i].toRight});
        }
    }
    return streetNumbers;
}

// Finds the house numbers that appear more than once
std::set<int> findDoubleHouseNumbers(std::vector<HouseNumberRange> &houseNumberRanges)
{
    std::set<int> doubleHouseNumbers;
    for (int i = 0; i < houseNumberRanges.size(); i++)
    {
        for (int j = 0; j < houseNumberRanges.size(); j++)
        {
            if (i == j)
                continue;

            if (houseNumberRanges[i].scheme == houseNumberRanges[j].scheme || houseNumberRanges[j].scheme == 'M')
            {
                for (int houseNumber = houseNumberRanges[i].numFrom; houseNumber <= houseNumberRanges[i].numTo; houseNumber += 2)
                {
                    if (houseNumber >= houseNumberRanges[j].numFrom && houseNumber <= houseNumberRanges[j].numTo)
                    {
                        doubleHouseNumbers.insert(houseNumber);
                    }
                }
            }
        }
    }
    return doubleHouseNumbers;
}

void processDoubleHouseNumbersScheme(std::vector<int> &doubleNumVec, const std::string &streetName, bool isEven)
{
    int left = 0;
    int right = 0;
    while (right + 2 < doubleNumVec.size())
    {
        // Find the first odd/even number starting with the left index
        for (int i = left; i < doubleNumVec.size(); i++)
        {
            if (doubleNumVec[i] % 2 == (isEven ? 0 : 1))
            {
                left = i;
                break;
            }
        }
        // if no odd/even num found break loop
        if (doubleNumVec[left] % 2 != (isEven ? 0 : 1))
            break;

        right = left;

        // Find last consequtive odd/even number
        while (right + 2 < doubleNumVec.size())
        {
            if (doubleNumVec[right + 1] % 2 == (isEven ? 0 : 1))
            {
                if (doubleNumVec[right + 1] == doubleNumVec[right] + 2)
                {
                    right++;
                }
                else
                {
                    break;
                }
            }
            else if (doubleNumVec[right + 2] % 2 == (isEven ? 0 : 1))
            {
                if (doubleNumVec[right + 2] == doubleNumVec[right] + 2)
                {
                    right += 2;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        std::cout << streetName << ": E " << doubleNumVec[left] << " " << doubleNumVec[right] << std::endl;
        left = right + 1;
        right = left;
    }
}
int main()
{
    SetConsoleOutputCP(28592);

    std::vector<Street> streets = readFile("network.mid");
    std::unordered_map<std::string, std::vector<HouseNumberRange>> streetNumbers = generateStreetNumbersMap(streets);

    for (auto it : streetNumbers)
    {
        std::set<int> doubleHouseNumbers = findDoubleHouseNumbers(it.second);

        if (!doubleHouseNumbers.empty())
        {
            std::vector<int> doubleNumVec(doubleHouseNumbers.begin(), doubleHouseNumbers.end());
            processDoubleHouseNumbersScheme(doubleNumVec, it.first, true);
            processDoubleHouseNumbersScheme(doubleNumVec, it.first, false);
        }
    }

    return 0;
}
