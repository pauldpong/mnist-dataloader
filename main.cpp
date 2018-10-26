#include <vector>
#include <stdio.h>
#include <iostream>

#include "./dataloader.h"

void displayImages(FILE* & training_images, FILE* & training_labels, int n, int rows, int cols, float threshold);

int main() {
  
  FILE * training_images = fopen("./resources/train-images.idx3-ubyte", "r");
  FILE * training_labels = fopen("./resources/train-labels.idx1-ubyte", "r");

  if (training_images != NULL && training_labels != NULL) {
    Data training(training_images, training_labels);
    training.print();


    // displayImages(training_images, training_labels, 10, rows, columns, 200);

  }
}