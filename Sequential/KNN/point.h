/*
 * This class holds the attributes for every data point inside of the data set for,
 * prostate cancer. It also has a function to calculate the euclidean distance in
 * relation to itself with another data point.
 */

class Point {
    private:
       int size;
       float coords[10];

	public:
		float EuclideanDistance (Point q); 
        float *getCoords();
        int getClassification();

        void printCoords();
        void setCoords(float *row);
        void setClassification(float value);
};
