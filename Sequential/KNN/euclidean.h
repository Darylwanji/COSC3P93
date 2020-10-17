#include "point.h"

/*
 * This class is meant to store the value of the euclidean distances calculated, 
 * for every data point inside of the training data set. It stores both the distance
 * and a pointer to the objct in the training set.
 */
class Euclidean {
    private:
        float dist;
        Point *ptr_point;
    public:
        float getDistance();
        Point *getPointer();
        
        void setValues(int distance, Point *point);
};
