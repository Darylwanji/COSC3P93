class Point {
    private:
       int size;
       float *coords;

	public:
		float EuclideanDistance (Point q); 
        float *getCoords();
        Point(float *coordinates) {        
            coords = coordinates;
        }
};
