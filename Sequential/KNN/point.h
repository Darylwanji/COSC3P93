class Point {
    private:
       int size;
       float coords[10];

	public:
		float EuclideanDistance (Point q); 
        float *getCoords();
        void printCoords();
        void setCoords(float *row);
};
