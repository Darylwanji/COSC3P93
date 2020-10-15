#include "point.h"
float point::EuclideanDistance (point p, point q){
	return 0; 

}
void point::setFeatures(float p[]){
	for (int i = 0; i < 8;i++){
		features[i] = p[i]; 
	}
}

float *point::getFeatures(){
	return features;
}
