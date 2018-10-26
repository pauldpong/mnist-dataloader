#ifndef dataloader
#define dataloader

#include <vector>
#include <stdio.h>
#include <iostream>

class Data {
  private:
    std::vector<int>* imageVectors;
    int* labelArray;
    int size;
    int pixelRows;
    int pixelColumns;
  public: 
    Data(FILE* images, FILE* labels);
    ~Data();
    void print();
};

#endif