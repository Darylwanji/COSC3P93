#include "point.h"
#include <iostream>
#include <fstream>
#include <vector>


std::vector<std::vector<float> >read_dataset(const std::string &filename){

	std::vector<std::vector<float> > dataset; 
	std::vector<float> row;
	float radius,texture,perimeter, area, smoothness,compactness,symmetry,fractal_dimension;

	// open Dataset csv file
	std::fstream file(filename);


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


	
	static float l []= {12,32,43,56,76,86,78,45};
	static float c []= {22,34,54,24,42,53,43,54};
    Point p(l);
    Point q(c);

    float distance = p.EuclideanDistance(q);
    for (int i = 0; i < 8; i++) {
        std::cout << p.getCoords()[i] << std::endl;
    }
            std::cout << " distance between p and q: " << distance << std::endl;


	return 0;
}
