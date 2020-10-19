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
    for (int index = 2; index <=9; index++) {
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
    for (int i = 0; i < sizeof(this->coords)/sizeof(float); i++) {
        this->coords[i] = row[i];
    }
}

/*
 * @param value A float value containing the classification (0 for M, 1 for B)
 * @returns none
 */
void Point::setClassification(float value) {
    this->coords[1] = value;
}

int Point::getClassification() {
    return this->coords[1];
}
