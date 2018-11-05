#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define FILE_PATH "input.txt"

int size_in_byte(FILE* pFile){
  int bytes_num;
  fseek (pFile , 0 , SEEK_END);
  bytes_num = ftell (pFile);
  rewind (pFile);
  printf("size of file in bytes:%d\n", bytes_num);
  return bytes_num;
}
FILE* read_file(int* bytes_num){
  FILE * pFile;
  pFile = fopen ( FILE_PATH , "rb" );
  if (pFile==NULL){
    fputs ("File error",stderr);
    exit (1);
  }
  *bytes_num=size_in_byte(pFile);
  return pFile;
}
