/***********************************************************************
 * Program:
 *    Exploration 3, RSA
 *    Brother Neff, CS237
 *
 * Author:
 *    Jared Wadsworth
 *
 * Summary:
 *    RSA Encryption/Decryption Driver
 *    Compile with:
 *      g++ -c rsaZZ.cpp
 ***********************************************************************/
#include <cstdlib>
#include <NTL/ZZ.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

NTL_CLIENT

/***********************************************************************
 *
 *
 *
 *
 ***********************************************************************/
int main()
{
   char fileName[9] = "text.txt";
//   vector<int> numbers;
   int messageLength = 0;
   int pLength       = 0;
   int qLength       = 0;
   int eLength       = 0;
   
   ifstream fin(fileName);
    if (fin.fail())
   {
      cout << "Could not open the file.\n";
      return false;
   }

    string data;

    getline(fin,data);

//    data.shrink_to_fit();

    int count = 0;
    int varCount = 0;

    cout << data << endl;

    int size = data.length();
    cout << size << endl;
    
    for(int i = 0; i < size; i++)
    {
       count++;

       if(varCount == 3)
          cout << count << ' ' << data[i] << endl; 
       
       if(data[i] == ' ' || i + 1 == size)
       {
          cout << "data == " << data[i] << endl;
          // don't include the space in the count
          count--;

          // there are two spaces at the end of the file
          if(i+1 == size)
             count -= 2;
          
          // set the length of the various parts
          switch(varCount)
          {
             case 0:
                messageLength = count;
                break;
             case 1:
                pLength = count;
                break;
             case 2:
                qLength = count;
                break;
             case 3:
                eLength = count;
                break;
             default:
                cout << "error counting file\n";
                break;
          }

          varCount++;

          // erase the spaces
          if(i + 1 != size)
          {
             data.erase(i,1);
             // move i to the last position
             i--;
          }
          // reset the count
          count = 0;
       }
    }

    cout << data    << ' ' << messageLength << ' '
         << pLength << ' ' << qLength       << ' '
         << eLength << endl;
}
