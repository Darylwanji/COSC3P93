#include "point.h"
#include <iostream>
#include<cmath>

/*
 * Finds the Euclidean distance between two given points.
 *
 * @param Point q        - Represents a Point with 8 dimensions
 *
 * @return the EuclideanDistance between coords and point q
 * */
float Point::EuclideanDistance (Point q){
	float sum = 0;
	float EuclideanDistance = 0; 
    for (int index = 0; index < 8; index++) {
        float difference = coords[index] - q.getCoords()[index];
        sum += (difference*difference);
    }
    EuclideanDistance = sqrt(sum);
    return EuclideanDistance;
}

void Point::printCoords() {
    for (int counter = 0; counter < 10; counter++) {
        std::cout << coords[counter] << "\t";
    }
    std::cout << std::endl;
}
/*
 * Returns the features
*/
float *Point::getCoords(){
	return coords;
}

void Point::setCoords(float *row) {
    for (int i = 0; i < sizeof(this->coords)/sizeof(float); i++) {
        this->coords[i] = row[i];
    }
}
