#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#include "./dataloader.h"

unsigned int& endianSwap(unsigned int &x);

Data::Data(FILE* images, FILE* labels) {
  unsigned int magic_number = 0, num_images = 0, num_labels = 0;
  unsigned int rows = 0, columns = 0;
  unsigned char pixel_value, label;

  fread(&magic_number, sizeof(int), 1, images);
  endianSwap(magic_number);
  cout << "Loaded images with magic number: " << magic_number << endl;

  fread(&num_images, sizeof(int), 1, images);
  endianSwap(num_images);
  std::cout << "Number of training images: " << num_images << std::endl;

  fread(&rows, sizeof(int), 1, images);
  fread(&columns, sizeof(int), 1, images);

  fread(&magic_number, sizeof(int), 1, labels);
  endianSwap(magic_number);
  cout << "Loaded labels with magic number: " << magic_number << endl;
  fread(&num_labels, sizeof(int), 1, labels);
  endianSwap(num_labels);
  if (num_labels == num_images) {
    cout << "--- # of images matches # of labels ---" << endl;
      pixelRows = endianSwap(rows);
      pixelColumns = endianSwap(columns);
      size = num_images;

      imageVectors = new vector<int>[num_images];
      labelArray = new int[num_labels];

      for (int i = 0; i < size; i++) {
          for (int j = 0; j < (rows * columns); j++) {
            fread(&pixel_value, sizeof(char), 1, images);
            imageVectors[i].push_back((int)pixel_value);
          }
        fread(&label, sizeof(char), 1, labels);
        labelArray[i] = (int)label;
      }
      cout << "-- Filled image vectors and label array ---" << endl;

  } else {
    cout << "--- Load failed - arrays empty ---" << endl;
    size = 0;
    pixelRows = 0;
    pixelColumns = 0;
    labelArray = NULL;
    imageVectors = NULL;
  }
}

Data::~Data() {
  delete [] imageVectors;
  delete [] labelArray;
}

// Prints the MNIST number at index, according to grayscale threshold
void Data::print(int index, float threshold) {
  int pixelCount = 0;

  for (auto element: imageVectors[index]) {
    if (pixelCount % 28 == 0) cout << endl;
    if (element >= threshold) cout << "* ";
    else cout << "0 ";
    pixelCount++;
  }

  cout << endl;
}

unsigned int& endianSwap(unsigned int &x) {
  x = (x>>24)|((x<<8)&0x00FF0000)|((x>>8)&0x0000FF00)|(x<<24);
  return x;
}

