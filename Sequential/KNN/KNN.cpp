#include "point.h"
#include <iostream>
#include <fstream>

//Defining the number of K distances to test against.
#define K = 3;

void read_line(std::string line, float *row) {
    int counter = 0;
    std::string temp;

    while (line.length() > 0) {
       temp = line.substr(0, line.find(',')); 

       if (counter == 9) {
           row[counter] = stof(line);
           counter = 0;

           break;
       }
       
       else if (temp.compare("M") == 0) {
          row[counter] = 0; 
       }
       else if (temp.compare("B") == 0) {
          row[counter] = 1; 
       }
       else {
          row[counter] = stof(temp); 
       }
       
       line.erase(0, line.find(',')+1);
       counter++;
    }
}

void read_data(std::string filename, Point *test_data, Point *train_data) {
    std::ifstream inStream(filename);
    std::string line;

    float row[10];
    int line_count = 0;
    int test_index = 0;
    int train_index = 0;
    
    getline(inStream, line);
    line = "";

    if (inStream.is_open()) {

        while (getline(inStream, line, '\n')) {
            read_line(line, row);

            if (line_count < 30) {
                test_data[test_index].setCoords(row);  
                test_index++;
            }
            else if (line_count < 100) {
                train_data[train_index].setCoords(row);  
                train_index++;
            }
            line_count++;
        }
    }
    else {
        std::cout << "Failed" << std::endl;
    }
}

int main () {
    // Read in dataset
    std::ifstream inStream("Prostate_Cancer_dataset.csv");
    std::string line;
    
    Point test_data[30];
    Point train_data[70];

    read_data("Prostate_Cancer_dataset.csv", test_data, train_data);

    for (int i = 0; i < 30; i++) {
        test_data[i].printCoords();
    }

    for (int i = 0; i < 70; i++) {
        train_data[i].printCoords();
    }

    float euclidean_dist_arr[30][2];
    // Print
	return 0;
}
