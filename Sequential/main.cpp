#include <iostream>
#include <math.h>

//Function prototypes
int euclideanDist(int x1[], int x2[], int sizeX1);

int main() {
    /* TODO
     - Implement a function to calculate the euclidean distance
     - Sort the list generated from all distances
     - Initialize K to some integer and take the first k distances from the sorted list.
     - Figure out what the K-points are corresponding to each distance
     */
    return 0;
}

int euclideanDist(int x1[], int x2[], int sizeX1) {
    int sum = 0;
    for (int index = 0; index < sizeX1; index++) {
        int difference = x1[index] - x2[index];
        sum += std::abs(difference);
    }
    return sum;
}
