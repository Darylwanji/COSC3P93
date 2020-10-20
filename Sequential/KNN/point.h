/*
 * This class holds the attributes for every data point inside of the data set for,
 * prostate cancer. It also has a function to calculate the euclidean distance in
 * relation to itself with another data point.
 */

class Point {
    private:
       float coords[32];
	   int size_of_coords;
	   char classification = 'N'; //N = no classification

	public:
		float EuclideanDistance (Point q); 
        float *getCoords();
        char getClassification();

        void printCoords();
		void setSize(int size);
        void setCoords(float *row);
        void setClassification(char value);
};
