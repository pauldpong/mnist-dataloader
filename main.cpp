#include <vector>
#include <stdio.h>
#include <iostream>

#include "./dataloader.h"

int main() {
  
  FILE * training_images = fopen("./resources/train-images.idx3-ubyte", "r");
  FILE * training_labels = fopen("./resources/train-labels.idx1-ubyte", "r");
  FILE * test_images = fopen("./resources/t10k-images.idx3-ubyte", "r");
  FILE * test_labels = fopen("./resources/t10k-labels.idx1-ubyte", "r");

  if (training_images != NULL && training_labels != NULL 
    && test_images != NULL && test_labels != NULL) {
    Data training(training_images, training_labels);
    Data test(test_images, test_labels);
  } else {
    std::cout << "Failed to open files" << std::endl;
  }
}