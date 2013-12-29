/***********************************************************************
 * Program:
 *    Exploration 3, RSA
 *    Brother Neff, CS237
 *
 * Author:
 *    Brother Neff
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
#include <iomanip>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

NTL_CLIENT

/******************************************************************************
 * Find b^n % m.
 ******************************************************************************/
ZZ modExp(ZZ b, ZZ n, ZZ m)
{
   return PowerMod(b, n, m);
}

/******************************************************************************
 * Find i such that a * i is congruent to 1 (mod m).
 ******************************************************************************/
ZZ findInverse(ZZ a, ZZ m)
{
   ZZ d = to_ZZ(0);
   ZZ s = to_ZZ(0);
   ZZ t = to_ZZ(0);
   XGCD(d,s,t,a,m); // extended euclidean algorithum
   assert (d == 1); // GCD must be 1

   while (s < 0)
   {
      s += m;
   }
   
   return s;
}

/******************************************************************************
 * Convert from a text message representing a base 27 number to a ZZ number.
 ******************************************************************************/
ZZ fromBase27(string message)
{
   ZZ total = to_ZZ(0);
   
   for (int i = 0; i < message.length(); i++)
   {
      total += ((message[i] - '@') * power_ZZ(27, message.length() - i - 1));
   }
   return total;
}

/******************************************************************************
 * Convert from a ZZ number to a base 27 number represented by a text message.
 ******************************************************************************/
string toBase27(ZZ n)
{
   string message = "";
   for(int remainder = 0;n > 1;n = n / 27)
   {
      remainder = n % 27;
      message.insert(0,1,(remainder + '@'));
   }
   return message;
   
}

/******************************************************************************
 * Find a suitable e for a ZZ number that is the "totient" of two primes.
 ******************************************************************************/
ZZ findE(ZZ t)
{
   ZZ e;
   for(e = 3; GCD(t,e) != 1; e++)
      ;
   return e;
}

/******************************************************************************
 * Find suitable primes p and q for encrypting a ZZ number that is the message.
 ******************************************************************************/
void findPandQ(ZZ m, ZZ& p, ZZ& q)
{
   p = NextPrime(SqrRoot(m));
   q = NextPrime(p+1);
}
