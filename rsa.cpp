/***********************************************************************
 * RSA Encryption/Decryption
 ***********************************************************************/
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <assert.h>
using namespace std;

int eeGCD(int a, int m, int &s, int &t)
{
   int x = a;
   int y = m;
   int oldolds = 1;
   int olds = 0;
   int oldoldt = 0;
   int oldt = 1;

   while(y != 0)
   {
      int q = x/y;
      int r = x%y;
      x=y;
      y=r;
      s = oldolds - q *olds;
      t = oldoldt - q *oldt;
      oldolds = olds;
      oldoldt = oldt;
      olds = s;
      oldt = t;
   }

   s = oldolds;

   return x;
}

// finds b^n % m
int modExp(int b, int n, int m)
{
   int x = 1;
   int power = b % m;
   while (n > 0)
   {
      if (n % 2 == 1)
      {
         x = (x * power) % m;
      }
      power = (power * power) % m;
      n /= 2;
   }
   return x;
}

// finds i such that a * i is congruent to 1 (mod m)
int findInverse(int a, int m)
{
   int s;
   int t;
   assert(eeGCD(a,m,s,t) == 1);
   while (s < 0)
   {
      s += m;
   }

   return s;
}

/******************************************************************************
 * Run it through its paces.
 ******************************************************************************/
int main(int argc, char* argv[])
{
   if (argc < 5)
   {
      cout << "Usage: " << argv[0] << " p q e message\n";
      return 1;
   }

   int p = atoi(argv[1]);
   int q = atoi(argv[2]);
   int n = p * q;
   int e = atoi(argv[3]);
   int d = 0;

   char* message = argv[4];
   int offset = 'A';    // offset for conversion without spaces
   bool spaces = false; // true => there are spaces in the message

   int length = strlen(message);

   if (isalpha(message[0]))
   {
      int size = (int) (ceil(length / 2.0));
      int numeric[size];
      int number;

      for (int i = 0; i < length; i++)
      {
         // is there a space?
         if (message[i] == ' ')
         {
            spaces = true;
            offset--;
            break;
         }
      }

      cerr << "RSA Encryption:\n\n";

      cerr << "Translate the letters in '" << message << "' into their "
           << "numerical\nequivalents and then group the numbers into "
           << "blocks of four, result is:\n";

      for (int i = 0; i < length; i++)
      {
         message[i] = toupper(message[i]); // Change to all upper case
         if (message[i] == ' ')
         {
            number = 0; // spaces translate as zero
         }
         else
         {
            number = message[i] - offset; // find numeric equivalent
         }
         if (i % 2 == 0)
         {
            numeric[i / 2] = number * 100; // 2 hundreds digits
         }
         else
         {
            numeric[i / 2] += number; // 2 tens digits
         }
      }

      // output the converted letters as a number with leading zeros
      for (int i = 0; i < size; i++)
      {
         cout << setfill('0') << setw(4) << numeric[i] << " ";
      }
      cout << endl;
      cout.flush();

      cerr << "\nEncrypt each block using the mapping C = M^e mod n, ";
      cerr << "result is:\n";

      for (int i = 0; i < size; i++)
      {
         cout << setfill('0') << setw(4) << modExp(numeric[i], e, n)
              << " ";
      }
      cout << endl;
   }
   else
   {
      cerr << "RSA Decryption:\n\n";

      length = argc - 4;
      int numeric[length];

      for (int i = 0; i < length; i++)
      {
         numeric[i] = atoi(argv[i + 4]);
      }

      cerr << "Find the inverse of " << e << " modulo " << p - 1 << " * "
           << q - 1 << " = " << ((p - 1) * (q - 1)) << ", result is: ";
      d = findInverse(e, ((p - 1) * (q - 1)));
      cerr << d << endl << endl;

      cerr << "Decrypt the message ";
      for (int i = 0; i < length; i++)
      {
         cerr << setfill('0') << setw(4) << numeric[i] << " ";
      }

      cerr << "\nusing fast modular exponentiation to compute P = C^"
           << d << " mod " << n << ", result is:\n";

      for (int i = 0; i < length; i++)
      {
         numeric[i] = modExp(numeric[i], d, n);
         cerr << setfill('0') << setw(4) << numeric[i] << " ";
      }
      cerr << endl;
      cerr.flush();

      cerr << "\nTranslate back to English letters, result is:\n";
      cerr.flush();

      if (d > 1000) offset--;

      for (int i = 0; i < length * 2; i++)
      {
         char c = ((i % 2 == 0) ?
                   (numeric[i / 2] / 100) + offset
                   :
                   (numeric[i / 2] % 100) + offset);
         cout << ((c < 'A') ? ' ' : c);
      }
      cout << endl;
   }

   return 0;
}
