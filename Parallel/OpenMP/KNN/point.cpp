#include "point.h"
#include <omp.h>
#include <iostream>
#include<cmath>

/*
 * Finds the Euclidean distance between two given points.
 *
 * @param q A point object representing a data point in the dataset.
 * @returns the Euclidean Distance between this point object and point q
 * */
float Point::EuclideanDistance (Point q, int thread_count){
	float sum = 0;
	float EuclideanDistance = 0; 
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum) 
    for (int index = 1; index < this->size_of_coords; index++) {
	float difference = coords[index] - q.getCoords()[index];
        sum += (difference*difference);
    }
    
    EuclideanDistance = sqrt(sum);
    return EuclideanDistance;
}

/*
 * Prints the ID and Classification for a object.
 */
void Point::printCoords() {
	std::cout << "ID: " << this->coords[0] << "\tClassification: " << this->classification << std::endl;
}

/*
 * Returns a float array of coordinates stored in a object.
 *
 * @returns the attributes for the data point.
*/
float *Point::getCoords(){
	return coords;
}

/* 
 * Initializes the float coords array
 *
 * @param row A float array containing the values for a data point in the prostate cancer csv
 */
void Point::setCoords(float *row) {
    for (int i = 0; i < this->size_of_coords; i++) {
        this->coords[i] = row[i];
    }
}

/*
 * Sets the value for the classification of this object, represented by a char.
 *
 * @param value A float value containing the classification (0 for M, 1 for B)
 */
void Point::setClassification(char value) {
    this->classification = value;
}

/*
 *
 * @returns classification character a letter from 'A' to 'Z'
 */
char Point::getClassification() {
    return this->classification;
}

/*
 * Sets the size for the float coords array.
 *
 * @param size An Integer value containing the size of the coords array.
 */
void Point::setSize(int size) {
	this->size_of_coords = size;
}
