#include "point.h"
#include <iostream>
#include<cmath>

/*
 * Finds the Euclidean distance between two given points.
 *
 * @param q A point object representing a data point in the dataset.
 * @returns the Euclidean Distance between this point object and point q
 * */
float Point::EuclideanDistance (Point q){
	float sum = 0;
	float EuclideanDistance = 0; 
    for (int index = 1; index < this->size_of_coords; index++) {
        float difference = coords[index] - q.getCoords()[index];
        sum += (difference*difference);
    }
    EuclideanDistance = sqrt(sum);
    return EuclideanDistance;
}

/*
 * This function prints the attributes in a table to standard out.
 *
 * @params none
 * @returns none
 */
void Point::printCoords() {
	/*
    for (int counter = 0; counter < 10; counter++) {
		if (counter == 1) {
			if (coords[counter] == 0) {
				std::cout << "M" << "\t";
			}
			else {
				std::cout << "B" << "\t";
			}
		}
		else {
        	std::cout << coords[counter] << "\t";
		}
    }
    std::cout << std::endl;
	*/
	std::cout << "ID: " << this->coords[0] << "\tClassification: " << this->classification << std::endl;
}

/*
 * @param none
 * @returns the attributes for the data point.
*/
float *Point::getCoords(){
	return coords;
}

/* 
 * @param row A float array containing the values for a data point in the prostate cancer csv
 * @returns none
 */
void Point::setCoords(float *row) {
    for (int i = 0; i < this->size_of_coords; i++) {
        this->coords[i] = row[i];
    }
}

/*
 * @param value A float value containing the classification (0 for M, 1 for B)
 * @returns none
 */
void Point::setClassification(char value) {
    this->classification = value;
}

char Point::getClassification() {
    return this->classification;
}

void Point::setSize(int size) {
	this->size_of_coords = size;
}
