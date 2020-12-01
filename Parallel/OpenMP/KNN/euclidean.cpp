#include "euclidean.h"
#include <omp.h>


/*
 * Returns the Euclidean distance
 *
 * @params none
 * @returns the euclidean distance stored in the object value.
 */
float Euclidean::getDistance() {
    return this->dist;
}

/*
 * Returns the Point object pointer.
 *
 * @params none
 * @returns the pointer pointing to a Point object
 */

Point *Euclidean::getPointer() {
    return this->ptr_point;
}

/*
 * Initializes values for the distance and Point object.
 *
 * @param distance The value of the Euclidean distance.
 * @param point The pointer pointing to a Point object.
 * @returns none
 */
void Euclidean::setValues(float distance, Point *point) {
    this->dist = distance;
    this->ptr_point = point;
}
