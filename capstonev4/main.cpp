// Instructions:

// There are specific inputs I request you test:

// The program will ask for the name of the .csv twice. This is to get a .csv for both the ID and category to filter by. 

// Usually, you can just use the same input. But to test the exception, I suggest you input a random string that does not end with .csv. 

// Then to test the correct dataset, enter "dataCorrect.csv" twice

// The program will then ask for the column index to filter by. Please select "5" as that selects the land size which is a numeric value

// The program will then ask for a range of values to filter by. Pick any two values, the range of the land size is between around 0-4000.

// I personally used 200 as the min and 300 as the max.

// The program should print the addresses of all houses with a land size within that range to sorted.csv (included and empty on download).

// This is Ping (Steven) Zhou's final capstone project 

// I usde and documented with UPPER CASE the required C++ concepts I used (Exception Handling, Classes, Constructors, Pointers, Recursion) 

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <algorithm>
#include "invalidCSV.hpp"
#include "invalidID.hpp"
#include "numericColumn.hpp"

using namespace std;

// Used to find "ID" string within a string
bool hasID(std::string str) {
    // Convert the string to lowercase
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    // Check if "id" or "ID" is present in the string
    if (str.find("id") != std::string::npos) {
        return true;
    }

    return false;
}

ifstream getInfile(bool temp_csv_invalid){
    // Ask which CSV to open for reading
    
    ifstream temp_infile;  // Declare temp_infile outside of try block

    // Using EXCEPTION HANDLING to check if the file opened correctly
    do {
        try{
            cout << "Enter the name of the CSV file to open: ";
            string filename;
            cin >> filename;

            temp_infile.open(filename);  // Assign value inside try block
            if (!temp_infile.is_open()) {
                // Check if opened correctly
                cerr << "Failed to open file!" << endl;
                throw invalidCSV();
            }
            temp_csv_invalid = false;
        }
        catch (invalidCSV& e) {
            cout << e.what() << endl;
        }
    } while(temp_csv_invalid);

    return temp_infile;
}

list<string> getColumn(ifstream& infile) {
    // Get the first line of the CSV
    string line;
    getline(infile, line);

    // Create a list to store the categories
    list<string> column;

    // Create a stringstream from line
    stringstream ss(line);

    // Extract each column
    while (getline(ss, line, ',')) {
        column.push_back(line);
    }

    return column;
}

// Find ID in categories
int findID(list<string> column) {
    string tempID;
    int count = 0;
    bool id = false;

    for(list<string>::iterator it = column.begin(); it != column.end(); ++it) {
        count++;
        if (hasID(*it)) {
            id = true;
            return count;
        }
    }

    return count;
}

// Create category list
list<string> createCategoryList(ifstream& infile, int column_number){
    list<string> categoryList;

    string line;
    // Read each line in the file
    while (getline(infile, line)) { 
        stringstream ss(line);
        string value;
        int current_column = 1;
        // Split the line by commas
        while (getline(ss, value, ',')) { 
            // If we're in the specified column
            if (current_column == column_number) { 
                // Add the value to the list
                categoryList.push_back(value); 
                break; 
            }
            // Onto next column
            current_column++;
        }
    }

    return categoryList;
}

int main() {

    // Need two files to read from so that we can get the column names and IDs seperately
    bool csv_invalid = true;
    bool IDs_invalid = true;

    // Get the CSV file
    ifstream infile = getInfile(csv_invalid);
    ifstream IDsfile = getInfile(IDs_invalid);

    // A list to store the categories
    list<string> column = getColumn(infile);    

    int ID_index;

    // Find ID in categories
    try{
        ID_index = findID(column);
        if(ID_index == 0) {
            throw invalidID();
        }

    }
    catch(invalidID& e) {
        cout << e.what() << endl;
    }

    // Create IDs list
    list<string> IDs = createCategoryList(IDsfile, ID_index);

    // Pop column name from ID list
    IDs.pop_front();

    // Create category list
    cout << "What number column do you want to filter by (1 being the first column)";
    int column_number;
    cin >> column_number;
    
    list<string> categoryList = createCategoryList(infile, column_number);

    // Create numeric column
    num_column numCol(IDs, categoryList);

    // sort the column so the output is in order
    numCol.sort();

    // ask for min and max
    double min, max;
    cout << "Enter the minimum value: ";
    cin >> min;
    cout << endl;

    cout << "Enter the maximum value: ";
    cin >> max;
    cout << endl;

    // write to file
    ofstream outfile;
    outfile.open("sorted.csv");

    // filter based on min and max and write to file
    numCol.write(outfile, min, max);

    return 0;
}
