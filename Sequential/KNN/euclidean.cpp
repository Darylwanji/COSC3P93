#include "euclidean.h"

/*
 * @params none
 * @returns the euclidean distance stored in the object value.
 */
int Euclidean::getDistance() {
    return this->dist;
}

/*
 * @params none
 * @returns the pointer pointing to a Point object
 */

Point *Euclidean::getPointer() {
    return this->ptr_point;
}

/*
 * @param distance The value of the Euclidean distance.
 * @param point The pointer pointing to a Point object.
 * @returns none
 */
void Euclidean::setValues(int distance, Point *point) {
    this->dist = distance;
    this->ptr_point = point;
}
