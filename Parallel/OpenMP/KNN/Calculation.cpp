#include <iostream>
#include <fstream>

using namespace std;

float Calculate_average(float arr[]){
	float sum = 0; 
	float average = 0;
	for(int i = 0; i < 5; i++){
		sum+=arr[i];
	}
	average = sum/5;
	return average;
}

float Calculate_speedup(float serialtime, float n_processor_time){
	//cout<< "\n-------- DEBUG START ------- "<<endl;
	//cout<< serialtime << " " << n_processor_time;
	//cout<< "\n-------- DEBUG END ------- "<<endl;
	return serialtime/n_processor_time;
}
float Calculate_Efficiency(float speedup, float processor){
	return speedup/processor;
}
float Calculate_cost(float N, float Tp){
	return N*Tp;
}
int main () {
	string file_names [] = {"Prostate Cancer","Breast Cancer"," Abalone ", "Letters "};
	int file_index[4];
	int p = 0;
	float serial_times[] = {0.0015654,0.0168444,0.669101,17.4909};
	float average, speedup, efficiency, cost;
	
	ifstream fin("values.txt");
	if(fin.is_open()) {
		cout << "File loaded " <<endl; 
		for(int k = 0; k < 4; k++){
		int number_of_threads; 
		fin>> number_of_threads;
		for(int j =0; j<4; j++){
		fin >> file_index[j];
		cout<<" Reading the values for " << file_names[file_index[j]] << " with " << number_of_threads << " threads" << endl;
		float times[5];
		
		for(int i = 0; i< 5; i++){
			fin>>times[i];
		}
		average = Calculate_average(times);
		cout<< " Values are : ";
		for(int i = 0; i< 5; i++){
			cout<< times[i] << "\t";
		}
		speedup = Calculate_speedup(serial_times[j],average);
		efficiency = Calculate_Efficiency(speedup,number_of_threads);
		cost = Calculate_cost(number_of_threads,average);
		
		cout<<"\nSpeed-up : " << speedup << endl;
		cout<<"Efficiency : " << efficiency << endl;
		cout<<"Average : " << average << endl;
		cout<<"Cost : " << cost << endl;
		cout << " |---------------------------------------------------------|  \n"; 
	}
	cout<< "                 Done for " << number_of_threads<<" threads \n";
	cout << " |---------------------------------------------------------|  \n"; 
	p++;
}
	} else { 
		cout<< " File couldn't be loaded \n";
	}
		
	
	
	
	
	
	
}
