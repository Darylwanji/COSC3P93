#include "euclidean.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>


std::string filenames[4] = {"Prostate_Cancer_dataset.csv", "Breast_Cancer_dataset.csv","abalone.csv", "letters.csv"};
int file_index; // Cin

int test_data_size;
int train_data_size;
int size_of_line;
//Defining the number of K distances to test against.
int K = 5;


//Function Prototypes
void read_line(std::string line, float *row, int line_size, char &category);
void read_data(std::string filename, Point *test_data, Point *train_data, int line_size);
void quick_sort(Euclidean *euclidean_arr, int pivot, int size_of_arr);
void swap_numbers(Euclidean *euclidean_arr, int large_index, int small_index);

int partition(Euclidean *euclidean_arr, int small, int big, int pivot);
int max(int a, int b);
char mode(Euclidean *euclidean_arr);

int main () {
    std::cout << " Please enter a number to choose a dataset " << std::endl;
    std::cout << " 0- Prostate_Cancer_dataset  1- Breast_Cancer_dataset  2- Abalone_dataset 3- Letters_dataset " << std::endl;
    std::cin >> file_index; 
    if (file_index >= 0 && file_index <= 3) {
    std::cout << filenames[file_index] << std::endl;
    switch(file_index) {
        case 0:
            test_data_size = 30;
            train_data_size = 70;
            size_of_line = 10;
            break;
        case 1:
            test_data_size = 170;
            train_data_size = 399;
            size_of_line = 33;
            break;
        case 2:
            test_data_size = 1253;
            train_data_size = 2924;
            size_of_line = 10;
            break;
        case 3:
            test_data_size = 6000;
            train_data_size = 14000;
            size_of_line = 18;
    }
    // Read in dataset
    std::string line;

    Point test_data[test_data_size];
    Point train_data[train_data_size];

    // Execution time variables
    struct timeval start, end;
    float duration;

    std::cout << " Reading data..." << std::endl;
//    read_data("Prostate_Cancer_dataset.csv", test_data, train_data);
    read_data(filenames[file_index], test_data, train_data, size_of_line);
    std::cout << " Done reading data." << std::endl;

    Euclidean euclidean_dist_arr[train_data_size];

    // time at start of classification
    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);
    // Loop over all of test_data in order to classify.

    for (int test_index = 0; test_index < test_data_size; test_index++) {
        // Training
        for (int train_index = 0; train_index < train_data_size; train_index++) {
            euclidean_dist_arr[train_index].setValues( \
                     test_data[test_index].EuclideanDistance(train_data[train_index]), \
                                                            &train_data[train_index]);
        }
        // Sorting 
        quick_sort(euclidean_dist_arr, 0, (sizeof(euclidean_dist_arr)/sizeof(Euclidean))-1);
        Euclidean k_selections[K];

        //  std::cout << "distances are :"<<std::endl;

        //  for (int i =0; i < 70; i++){
        //   std::cout << i << " : "<< euclidean_dist_arr[i].getDistance() << std::endl;
        //  }
        for (int index = 0; index < K; index++) {
            k_selections[index] = euclidean_dist_arr[index];
            //    std::cout << k_selections[index].getDistance() << std::endl;
        }

        char classification = mode(k_selections);
        test_data[test_index].setClassification(classification);
        test_data[test_index].printCoords();
    }



    // time at the enf of classification
    gettimeofday(&end, NULL);
    duration = (end.tv_sec - start.tv_sec) * 1e6;
    duration = (duration + (end.tv_usec - start.tv_usec)) * 1e-6;


    std::cout << "Time taken for classification with " <<  K << " neighbors : " << duration << std::endl;
}
else {
    std::cerr << " Wrong number of Entered" << std::endl;
}
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
void read_line(std::string line, float *row, int line_size, char &category) {

    int counter = 0;
    std::string temp;

    while (line.length() > 0) {
        temp = line.substr(0, line.find(','));

        if (counter == (line_size - 2)) {

            row[counter] = stof(line);
            counter = 0;

            break;
        }

//       else if ((temp.compare("M") == 0) || (temp.compare("B") == 0) || \
                (temp.compare("I") == 0) || (temp.compare("F") == 0)) {
        int char_val = temp.c_str()[0];
        if (char_val >= 65 && char_val <= 90) {

            //Converts to char array and then assigns 0th element to char, being
            //the letter for classification
            category = char_val;
        }

        else {
            row[counter] = stof(temp);
            counter++;
        }

        line.erase(0, line.find(',')+1);
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
void read_data(std::string filename, Point *test_data, Point *train_data, int line_size) {

    std::ifstream inStream(filename);
    std::string line;

    //Removing 1 because the classification is not stored in the array
    float row[line_size-1];

    int line_count = 0;
    int test_index = 0;
    int train_index = 0;
    char category;

    getline(inStream, line);
    line = "";

    if (inStream.is_open()) {

        while (getline(inStream, line, '\n')) {
            read_line(line, row, line_size, category);

            if (line_count < test_data_size) {

                test_data[test_index].setSize(line_size-1);
                test_data[test_index].setCoords(row);

                test_index++;
            }
            else if (line_count < (train_data_size+test_data_size)) {

                train_data[train_index].setSize(line_size);
                train_data[train_index].setCoords(row);
                train_data[train_index].setClassification(category);

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
            swap_numbers(euclidean_arr, low++, high--);
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
char mode(Euclidean *euclidean_objs) {

    int class_values[25] = { 0 };
//    int M = 0;
//    int B = 0;
//    int I = 0;
//    int F = 0;
    char classification;
    int index;
    int largest_index = 0;

    for (int k_counter = 0; k_counter < K; k_counter++) {

        classification = euclidean_objs[k_counter].getPointer()->getClassification();
        index = (classification + 25) - 'Z';
        class_values[index] += 1;

        if (class_values[index] > class_values[largest_index]) {
            largest_index = index;
        }

        /*
        if (classification == 'M') {
            M++;
        }
        else if (classification == 'B') {
            B++;
        }
        else if (classification == 'I') {
            I++;
        }
        else if (classification == 'F') {
            F++;
        }
        */
    }

//    int largest_num = max(max(M, B), max(I, F));
//
//    return (largest_num == M) ? 'M' : \
//           (largest_num == B) ? 'B' : \
//           (largest_num == I) ? 'I' : 'F';\

    char letter = (largest_index+90)-25;
    return letter;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}
