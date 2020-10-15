#include "point.h"
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
        sum += pow(difference,2);
    }
    EuclideanDistance = sqrt(sum);
    return EuclideanDistance;
}

/*
 * Returns the features
*/
float *Point::getCoords(){
	return coords;
}

