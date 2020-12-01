/*
 * This class represents a line in a dataset CSV file. It holds all the attributes
 * defined on the line and functions necessary for classification like the EuclideanDistance
 * function.
 */

class Point {
    private:
       float coords[32];
	   int size_of_coords;
	   char classification = 'N'; //N = no classification

	public:
	float EuclideanDistance (Point q, int thread_count); 
        float *getCoords();
        char getClassification();

        void printCoords();
		void setSize(int size);
        void setCoords(float *row);
        void setClassification(char value);
};
