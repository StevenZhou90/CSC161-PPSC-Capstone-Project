#ifndef NUMCOL_HPP
#define NUMCOL_HPP

#include <iostream>
#include "numericNode.hpp"
#include <list>

using namespace std;


// use of CLASS
class num_column{
    public:

    // Using POINTER to create dynamic array
    Node *nodes;
    int size;

    // CONSTRUCTOR
    num_column(list<string> IDs, list<string> vals){
        if(IDs.size() != vals.size()){
            int size = IDs.size();
            int size2 = vals.size();
            cout << "IDS" << size << endl;
            cout << "vals" << size2 << endl;

            cerr << "Error: IDs and values are not the same size!" << endl;
            exit(1);
        } else{
            size = IDs.size();
            nodes = new Node[size];
            int i = 0;

            for (std::list<string>::iterator it1 = IDs.begin(), it2 = vals.begin(); it1 != IDs.end() && it2 != vals.end(); ++it1, ++it2) {
                nodes[i] = Node(stod(*it2), *it1);
                i++;
            }
        }
    };

    // Destructor
    ~num_column(){
        delete[] nodes;
    };

    // print items in list
    void print(){
        for(int i = 0; i < size; i++){
            cout << "Index: " << nodes[i].getIndex() << "Value: " << nodes[i].getValue() << endl;
        }
    };    

    // Sort the list with quick sort that uses RECURSION
    void sort(){
        quickSort(nodes, 0, size-1);
    };

    // Quick sort 
    void quickSort(Node *arr, int low, int high){
        if (low < high){
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    };

    // Partition for quick sort
    int partition(Node *arr, int low, int high){
        double pivot = arr[high].getValue();
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++){
            if (arr[j].getValue() < pivot){
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        return (i + 1);
    };

    // Swap for quick sort
    void swap(Node *a, Node *b){
        Node t = *a;
        *a = *b;
        *b = t;
    };

    // Write to output .csv file and filter by value   
    void write(ofstream& outfile, double min, double max){
        for(int i = 0; i < size; i++){
            if(nodes[i].getValue() >= min && nodes[i].getValue() <= max){
                outfile << nodes[i].getIndex() << "--" << nodes[i].getValue() << endl;
            }
        }
    };

};

#endif