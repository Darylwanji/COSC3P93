#include "point.h"
#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::vector<float>> read_dataset(const std::string &filename){

    std::ifstream inStream(filename);
    std::string line;
    
	std::vector<std::vector<float>> dataset; 
	std::vector<float> row;
    //Getting rid of first line which is just the labels of the dataset
    getline(inStream, line);
    line = "";
    int counter = 0;

    if (inStream.is_open()) {
        while (getline(inStream, line, ',')) {
            if (counter == 1) {
                counter++;
                if (line.compare("M")) {
                    row.push_back(0);
                }
                else if (line.compare("B") != 0) {
                    row.push_back(1);
                }
            }
            else {
                row.push_back(stof(line));
                counter++;

                if (counter == 9) {
                    getline(inStream, line, '\n');
                    row.push_back(stof(line));
                    dataset.push_back(row);
                    counter = 0;
                    row.clear();
    
                }
            }
        }
    }
    else {
        std::cout << "Failed" << std::endl;
    }

	return dataset;
}

void display (std::vector<std::vector<float> > data){

   // Displaying the 2D vector 
    for (int i = 0; i < data.size(); i++) { 
        for (int j = 0; j < data[i].size(); j++) 
            std::cout << data[i][j] << " "; 
        std::cout << std::endl; 
    } 

}

int main (){

	//display(read_dataset("Prostate_Cancer_dataset.csv"));


	/*
	static float l []= {12,32,43,56,76,86,78,45};
	static float c []= {22,34,54,24,42,53,43,54};
    Point p(l);
    Point q(c);

    float distance = p.EuclideanDistance(q);
    for (int i = 0; i < 8; i++) {
        std::cout << p.getCoords()[i] << std::endl;
    }
            std::cout << " distance between p and q: " << distance << std::endl;

    */
    std::string fname = "Prostate_Cancer_dataset.csv";
    std::vector<std::vector<float>> dataset = read_dataset(fname);
    for (int i = 0; i < dataset.size(); i++) {
        for (int j = 0; j < dataset[i].size(); j++) {
            std::cout << dataset[i][j] << "\t";
        }
        std::cout << std::endl;
    }
	return 0;
}
