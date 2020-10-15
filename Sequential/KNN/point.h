class point {
	public:
		float EuclideanDistance (point p, point q); 
		void setFeatures(float*);
		float* getFeatures();
	private:
		float* features;
	};