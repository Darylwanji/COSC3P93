#include "euclidean.h"
#include <iostream>
#include <fstream>

//Defining the number of K distances to test against.
#define K = 3;

//Function Prototypes
void read_line(std::string line, float *row);
void read_data(std::string filename, Point *test_data, Point *train_data);
int mode(Euclidean euclidean_objs);

int main () {
    // Read in dataset
    std::ifstream inStream("Prostate_Cancer_dataset.csv");
    std::string line;
    
    Point classified_results[30];
    Point test_data[30];
    Point train_data[70];

    read_data("Prostate_Cancer_dataset.csv", test_data, train_data);

    Euclidean euclidean_dist_arr[70];
    
    // Loop over all of test_data in order to classify.
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 70; j++) {
            euclidean_dist_arr[j].setValues(test_data[i].EuclideanDistance(train_data[j]), &train_data[j]);
        }
    }
	return 0;
}

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

/*
 * @param euclidean_objs The euclidean objects to check the mode for.
 * @return the mode of classification.
 */
int mode(Euclidean *euclidean_objs) {
    return 0;
}
