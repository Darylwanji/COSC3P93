/*
 * Name: Aditya Rajyaguru
 * Student Number: 6582282
 *
 * Name: Brandon Daryl Wanji
 * Student Number: 6151351
 */
#include "euclidean.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <omp.h>


std::string filenames[4] = {"datasets/Prostate_Cancer_dataset.csv", "datasets/Breast_Cancer_dataset.csv","datasets/abalone.csv", "datasets/letters.csv"};
int file_index; // Global var used for parsing

//Global vars to be used for parsing a CSV
int test_data_size;
int train_data_size;
int size_of_line;

//Defining the number of K distances to test against.
//It's defined in the switch case statements below, it takes 10% of the training set.
int K;


//Function Prototypes
void read_line(std::string line, float *row, int line_size, char &category);
void read_data(std::string filename, Point *test_data, Point *train_data, int line_size);
void quick_sort(Euclidean *euclidean_arr, int pivot, int size_of_arr);
void swap_numbers(Euclidean *euclidean_arr, int large_index, int small_index);

int partition(Euclidean *euclidean_arr, int small, int big, int pivot);
int max(int a, int b);
char mode(Euclidean *euclidean_arr, int thread_count);

int main (int argc, char* argv[]) {
    
    std::cout << " Please enter a number to choose a data-set" << std::endl;
    std::cout << "0: Prostate Cancer Data-set (100 data points)" << std::endl;
    std::cout << "1: Breast Cancer Data-set (569 data points)" << std::endl;
    std::cout << "2: Abalone Data-set (4177 data point))" << std::endl;
    std::cout << "3: Letters Data-set (20000 data points)" << std::endl;
    std::cout << "Any other key to quit." << std::endl;
    std::cout << "Input: ";

    char input;
    int thread_count = strtol(argv[1], NULL, 10);
    std::cin >> input;
    int check = input - '0';

    if (check < 0 || check > 3) {
        std::cerr << "Exiting." << std::endl;
        return 0;
    }
    else {
        file_index = check;
    }

    switch(file_index){
        case 0:
            test_data_size = 30;
            train_data_size = 70;
            size_of_line = 10;
            K = 10;
            break;
        case 1:
            test_data_size = 170;
            train_data_size = 399;
            size_of_line = 33;
            K = 58;
            break;
        case 2:
            test_data_size = 1253;
            train_data_size = 2924;
            size_of_line = 10;
            K = 418;
            break;
        case 3:
            test_data_size = 6000;
            train_data_size = 14000;
            size_of_line = 18;
            K = 2000;
    }

    Point test_data[test_data_size];
    Point train_data[train_data_size];

    // Execution time variables for benchmarking performance
    struct timeval start, end;
    float duration;

    std::cout << " Reading data..." << std::endl;
    read_data(filenames[file_index], test_data, train_data, size_of_line);
    std::cout << " Done reading data." << std::endl;

    //Array that holds the distance between testing point and the training one.
    Euclidean euclidean_dist_arr[train_data_size];

    // time at start of classification
    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);
    for (int test_index = 0; test_index < test_data_size; test_index++) {
        #pragma omp parallel for num_threads(thread_count)
        for (int train_index = 0; train_index < train_data_size; train_index++) {
            euclidean_dist_arr[train_index].setValues( test_data[test_index].EuclideanDistance(train_data[train_index], thread_count), &train_data[train_index]);
        }
        quick_sort(euclidean_dist_arr, 0, (sizeof(euclidean_dist_arr)/sizeof(Euclidean))-1);
        Euclidean k_selections[K];

        #pragma omp parallel for num_threads(thread_count)
        for (int index = 0; index < K; index++) {
            k_selections[index] = euclidean_dist_arr[index];
        }
        char classification = mode(k_selections, thread_count);
        test_data[test_index].setClassification(classification);

        //Uncomment this if you wish to see the classifications for every data point.
        //Not recommended for the letters.csv dataset as it has 20000 lines to print.
        //test_data[test_index].printCoords();

    } //End outer for loop
 // time at the end of classification
    gettimeofday(&end, NULL);
    duration = (end.tv_sec - start.tv_sec) * 1e6;
    duration = (duration + (end.tv_usec - start.tv_usec)) * 1e-6;

    std::cout << "Time taken for classification with " <<  K << " neighbors : " << duration << std::endl;
    return 0;

} //End main

/*
 * This function emulates the split function in python. It takes
 * a string passed in from the CSV file and builds an array delimited by commas.
 *
 * @param line A string variable delimited by commas
 * @param row Float array to store the values from the line param.
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

        //Converts a string to char array to get the letter for classification
        int char_val = temp.c_str()[0];

        //Check for capital letters specifically
        if (char_val >= 65 && char_val <= 90) {
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
 * This function is responsible for reading in a dataset csv file and
 * loading it into the respective arrays of test_data and train_data.
 * It splits the data into testing/training arrays based on the global
 * vars test_data_size and train_data_size. The default is a 70/30 split.
 *
 * @param filename A string value holding the name of the dataset.
 * @param test_data A pointer to an array of Point objects
 * @param train_data A pointer to an array of Point objects.
 */
void read_data(std::string filename, Point *test_data, Point *train_data, int line_size) {

    std::ifstream inStream(filename);
    std::string line;

    //Removing 1 because the classification is not stored in the array
    float row[line_size-1];

    int line_count  = 0;
    int test_index  = 0;
    int train_index = 0;

    char category;

    //The first line for every CSV file is just a descriptor so we don't need that.
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
        std::cout << "Failed to open file." << std::endl;
    }
}

/*
 * Sorts elements on the part of the Euclidean array specified
 * by the low and high indexes. It sorts with comparisons of elements
 * at the indexes to the value of the pivot.
 *
 * @param euclidean_arr An array Euclidean objects
 * @param low The value where the left pointer should start
 * @param high The value where the right pointer should start
 * @param pivot Value that is used for the sorting
 * @returns low The position of the pointer from the left side
 */
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

/*
 * Quicksort algorithm, sorts an array of Euclidean objects based
 * on their distance values from smallest to biggest.
 *
 * @param euclidean_arr An array of euclidean objects
 * @param small Lower index for the array
 * @param big Higher index for the array
 */
void quick_sort(Euclidean *euclidean_arr, int small, int big) {

    if (small < big) {

        float pivot = euclidean_arr[(small+big)/2].getDistance();

        //Initial sort to get an index for the sorted value in the middle
        //of the array.
        int j = partition(euclidean_arr, small, big, pivot);

        //Running quicksort recursively on two halves of the array
        quick_sort(euclidean_arr, small, j-1);
        quick_sort(euclidean_arr, j, big);
    }
}

/*
 * Swaps two numbers in an array given their indices.
 *
 * @param euclidean_arr Array of Euclidean objects
 * @param large_index An index in the array
 * @param small_index An index in the array
 */
void swap_numbers(Euclidean *euclidean_arr, int large_index, int small_index) {

    Euclidean temp = euclidean_arr[large_index];
    euclidean_arr[large_index] = euclidean_arr[small_index];
    euclidean_arr[small_index] = temp;
}

/*
 * Returns the most repeated classification value for the first K
 * elements in a Euclidean array.
 *
 * @param euclidean_objs The euclidean objects to check the mode for.
 * @return the mode of classification.
 */
char mode(Euclidean *euclidean_objs, int thread_count) {

    int class_values[25] = { 0 };
    int index;
    int largest_index = 0;

    char classification;
    #pragma omp parallel for num_threads(thread_count) private(classification, index)
    // Write and Read True dependency going on with Classification and index
    for (int k_counter = 0; k_counter < K; k_counter++) {

        classification = euclidean_objs[k_counter].getPointer()->getClassification();

        //Converts the letter's ASCII value to an index in the array.
        index = (classification + 25) - 90;
        
        class_values[index]++;

//        #pragma omp critical
        if (class_values[index] >= class_values[largest_index]) {
            largest_index = index;
        }
    }

    //Convert the index back to the ASCII value
    char letter = (largest_index+90)-25;
    return letter;
}
