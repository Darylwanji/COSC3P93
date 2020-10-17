#include "euclidean.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>

// TODO : Might wanna get 2 more values to check {3,5,7}
//Defining the number of K distances to test against.
int K = 3;


//Function Prototypes
void read_line(std::string line, float *row);
void read_data(std::string filename, Point *test_data, Point *train_data);
void quick_sort(Euclidean *distance_arr, int pivot, int size_of_arr); 
void swap_numbers(Euclidean *distance_arr, int large_index, int small_index);

int partition(Euclidean *distance_arr, int small, int big, int pivot);
int mode(Euclidean euclidean_objs);

int main () {
    // Read in dataset
    std::ifstream inStream("Prostate_Cancer_dataset.csv");
    std::string line;
    
    Point classified_results[30];
    Point test_data[30];
    Point train_data[70];

    struct timeval start, end;
    float duration; 

    std::cout << " Reading data..." << std::endl;
    read_data("Prostate_Cancer_dataset.csv", test_data, train_data);
    std::cout << " Done reading data." << std::endl;


    Euclidean euclidean_dist_arr[70];
    
    // time at start of classification
    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);
    // Loop over all of test_data in order to classify.
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 70; j++) {
            euclidean_dist_arr[j].setValues(test_data[i].EuclideanDistance(train_data[j]), &train_data[j]);
        }

        for (int k = 0; k < 70; k++) {
            float dist = euclidean_dist_arr[k].getDistance();
            std::cout << k << ": Distance: " << dist << std::endl;
        }

        quick_sort(euclidean_dist_arr, 0, 70);
        
        std::cout << "-------------------------------------------------------" << std::endl;
        for (int k = 0; k < 70; k++) {
            float dist = euclidean_dist_arr[k].getDistance();
            std::cout << k << ": Distance: " << dist << std::endl;
        }
        break;
    }
    /* TODO
     * - Sort the distances - Quicksort algorithm.
     * - Pick K entries.
     * - Find mode of the K entries
     */
    
    // time at the enf of classification
    gettimeofday(&end, NULL);
    duration = (end.tv_sec - start.tv_sec) * 1e6; 
    duration = (duration + (end.tv_usec - start.tv_usec)) * 1e-6;


    std::cout << "Time taken for classification with " << 3 << " neighbors : " << duration << std::endl;
	return 0;
}

/*
 * This function emulates the split function in python. It takes
 * a string passed in from the CSV file and builds an array delimited by commas.
 *
 * @param line A string variable delimited by commas
 * @param row Float array to store the values from the line param.
 *
 * @returns none
 */
void read_line(std::string line, float *row) {
    int counter = 0;
    std::string temp;

    while (line.length() > 0) {
       temp = line.substr(0, line.find(',')); 

       if (counter == 9) {
           row[counter] = stof(line);
           counter = 0;

           break;
       }
       
       else if (temp.compare("M") == 0) {
          row[counter] = 0; 
       }
       else if (temp.compare("B") == 0) {
          row[counter] = 1; 
       }
       else {
          row[counter] = stof(temp); 
       }
       
       line.erase(0, line.find(',')+1);
       counter++;
    }
}

/*
 * This function is responsible for reading in the prostate dataset
 * csv file and loading it into the respective arrays of test_data and
 * train_data. In this case the first 30 points are used for testing and
 * the remaining 70 are used for training the classification. The test data
 * also has its classification removed by setting its value to 3 (0 is Malignant,
 * 1 is Benign).
 *
 * @param filename A string value holding the name of the dataset.
 * @param test_data A pointer to an array of Point objects
 * @param train_data A pointer to an array of Point objects.
 *
 * @returns none
 */
void read_data(std::string filename, Point *test_data, Point *train_data) {
    std::ifstream inStream(filename);
    std::string line;

    float row[10];
    int line_count = 0;
    int test_index = 0;
    int train_index = 0;
    
    getline(inStream, line);
    line = "";

    if (inStream.is_open()) {

        while (getline(inStream, line, '\n')) {
            read_line(line, row);

            if (line_count < 30) {
                test_data[test_index].setCoords(row);  
                test_data[test_index].setClassification(3);
                test_index++;
            }
            else if (line_count < 100) {
                train_data[train_index].setCoords(row);  
                train_index++;
            }
            line_count++;
        }
    }
    else {
        std::cout << "Failed" << std::endl;
    }
}

int partition(Euclidean *euclidean_arr, int low, int high, float pivot) {
    
    while (low <= high) {
        while (euclidean_arr[low].getDistance() < pivot) {
            low++;
        }
        while (euclidean_arr[high].getDistance() > pivot) {
            high--;
        }
        if (low <= high) {
            swap_numbers(euclidean_arr, low, high);
            low++;
            high--;
        }
    }
    return low;
    
}

void quick_sort(Euclidean *euclidean_arr, int small, int big) {
    
    if (small < big) {

        float pivot = euclidean_arr[(small+big)/2].getDistance(); 
        int j = partition(euclidean_arr, small, big, pivot);

        quick_sort(euclidean_arr, small, j-1);
        quick_sort(euclidean_arr, j, big);

    }
}

void swap_numbers(Euclidean *euclidean_arr, int large_index, int small_index) {

    Euclidean temp = euclidean_arr[large_index];
    euclidean_arr[large_index] = euclidean_arr[small_index];
    euclidean_arr[small_index] = temp;
}

/*
 * @param euclidean_objs The euclidean objects to check the mode for.
 * @return the mode of classification.
 */
int mode(Euclidean *euclidean_objs) {
    int benign = 0;
    int malignant = 0;

    for (int index = 0; index < K; index++) {
        if (euclidean_objs->getPointer()->getClassification() == 0) {
            malignant++;
        }
        else {
            benign++;
        }
    }

    return (malignant > benign) ? malignant : benign;
}
