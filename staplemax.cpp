//Author: Christopher Fong
//Date: 5/12/2019
//Name: staplemax.cpp
//Project 2

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PEN = 100;
const int MAX_PAPER = 200;
const int MAX_TONER = 40;
const int MAX_LAPTOPS = 15;

const char* SALES_1  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales1.txt";
const char* SALES_2  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales2.txt";
const char* SALES_3  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales3.txt";
const char* SALES_4  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales4.txt";
const char* SALES_5  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales5.txt";
const char* SALES_6  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales6.txt";
const char* SALES_7  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales7.txt";
const char* SALES_8  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales8.txt";
const char* SALES_9  = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales9.txt";
const char* SALES_10 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales10.txt";
const char* SALES_11 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales11.txt";
const char* SALES_12 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales12.txt";
const char* SALES_13 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales13.txt";
const char* SALES_14 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales14.txt";
const char* SALES_15 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales15.txt";
const char* SALES_16 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales16.txt";
const char* SALES_17 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales17.txt";
const char* SALES_18 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales18.txt";
const char* SALES_19 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales19.txt";
const char* SALES_20 = "/home/fac/lillethd/cpsc3500/projects/sales_data/sales20.txt";

int pens = MAX_PEN;
int paper = MAX_PAPER;
int toner = MAX_TONER;
int laptops = MAX_LAPTOPS;

pthread_mutex_t lock;

struct args
{
  int sales;
  const char* location;
};

void* MakeSales(void* threadArg);

int main(int argc, char** argv)
{  
  int allSales = 0;
  
  pthread_t tid[20];
  
  args arguments[20];
  
  const char* SALES[20] = {SALES_1, SALES_2, SALES_3, SALES_4, SALES_5, SALES_6, SALES_7,
  SALES_8, SALES_9, SALES_10, SALES_11, SALES_12, SALES_13, SALES_14, SALES_15, 
  SALES_16, SALES_17, SALES_18, SALES_19, SALES_20};
  
  for(int i = 0; i < 20; i++)
  {
    int error = -1;
    arguments[i].sales = 0;
    arguments[i].location = SALES[i];
    error = pthread_create(&tid[i], NULL, MakeSales,(void *) &arguments[i]);
    if (error != 0) 
    {
      cout << "FATAL ERROR creating thread " << i + 1 << ": " << strerror(error) << endl;
      exit(1);
    }
  }
  for(int i = 0; i < 20; i++)
  {
    int error = -1;
    error = pthread_join(tid[i], NULL);
    if (error != 0) 
    {
      cout << "WARNING - failed to join thread " << i + 1 << ": " << strerror(error) << endl;
      exit(1);
    }
  }
  
  for(int i = 0; i < 20; i++)
  {
    allSales += arguments[i].sales;
  }
  
  cout << endl << "Shelf:" << endl;
  cout << "   Pens      " << pens << endl;
  cout << "   Paper     " << paper << endl;
  cout << "   Toner     " << toner << endl;
  cout << "   Laptops   " << laptops << endl << endl;
  
  cout << "Total Sales: " << allSales << endl << endl;
  
  return 0;
}

void* MakeSales(void* threadArg) 
{
  struct args *t = (struct args *)threadArg;
    
  string item = "";
  
  ifstream file;
  
  const char* SalesFile = t->location;
  
  file.open(SalesFile);
  
  while(file >> item)
  {
    pthread_mutex_lock(&lock);
    if(item == "pen")
    {
      if(pens == 0)
        pens = MAX_PEN;
      pens--;
    }
    if(item == "paper")
    {
      if(paper == 0)
        paper = MAX_PAPER;
      paper--;
    }
    if(item == "toner")
    {
      if(toner == 0)
        toner = MAX_TONER;
      toner--;
    }
    if(item == "laptop")
    {
      if(laptops == 0)
        laptops = MAX_LAPTOPS;
      laptops--;
    }
    pthread_mutex_unlock(&lock);
    t->sales++;
  }
  
  file.close();
  
  return NULL;
}