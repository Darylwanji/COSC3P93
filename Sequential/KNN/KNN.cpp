#include "point.h"
#include <iostream>
#include <fstream>
#include <vector>

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

int main () {
    // Read in dataset
    std::ifstream inStream("Prostate_Cancer_dataset.csv");
    std::string line;
    
	float row[10];
    Point points[100];
    int count = 0;

    getline(inStream, line);
    line = "";

    if (inStream.is_open()) {
        while (getline(inStream, line, '\n')) {
            read_line(line, row);
            points[count].setCoords(row);  
            count++;
        }
    }
    else {
        std::cout << "Failed" << std::endl;
    }

    // Print
    for (int i = 0; i < 100; i++) {
        points[i].printCoords();
    }
	return 0;
}
