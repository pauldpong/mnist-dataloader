#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#include "./dataloader.h"

unsigned int& endianSwap(unsigned int &x);
void fillImageVectors(vector<int>* vector, FILE* images, int size);
void fillLabelArray(int* array, FILE* labels, int size);

Data::Data(FILE* images, FILE* labels) {
  unsigned int magic_number = 0, num_images = 0, num_labels = 0;
  unsigned int rows = 0, columns = 0;

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

      fillImageVectors(imageVectors, images, size);
      fillLabelArray(labelArray, labels, size);

  } else {
    cout << "--- Load failed - every empty, all zero/NULL ---" << endl;
    size = 0;
    pixelRows = 0;
    pixelColumns = 0;
    labelArray = NULL;
    imageVectors = NULL;
  }
}

Data::~Data() {
  //delete the imageVector and labelArray
}
void Data::print() {
  cout << pixelRows << endl;
  cout << pixelColumns << endl;
}

unsigned int& endianSwap(unsigned int &x) {
  x = (x>>24)|((x<<8)&0x00FF0000)|((x>>8)&0x0000FF00)|(x<<24);
  return x;
}

void fillImageVectors(vector<int>* vector, FILE* images, int size) {
  unsigned char pixel_value;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 784; j++) {
      fread(&pixel_value, sizeof(char), 1, images);
      vector[i].push_back((int)pixel_value);
    }
  }

  cout << "-- Filled image vectors ---" << endl;
}

void fillLabelArray(int* array, FILE* labels, int size) {
  unsigned char label;

  for (int i = 0; i < size; i++) {
    fread(&label, sizeof(char), 1, labels);
    array[i] = (int)label;
  }

  cout << "-- Filled labels array ---" << endl;
}