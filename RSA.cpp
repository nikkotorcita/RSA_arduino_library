#include "RSA.h"

RSA rsa;

RSA::RSA()
{

}

RSA::~RSA()
{

}

void RSA::encrypt(char *plainText, char *cipherText, long *publicKey)
{
   long m = 1;
   long n = publicKey[0];
   long e = publicKey[1];
   int ctr = 0;

   for(int i = 0; i < PLAINTEXT_SIZE; i++) {
       for(int j = 0; j < e; j++) {
           m = (m * plainText[i]) % n;
       }
       
       ctr = i * sizeof(long);

       cipherText[ctr]     = (char) (m & 0x000000ff);
       cipherText[ctr + 1] = (char) ((m & 0x0000ff00) >> 8);
       cipherText[ctr + 2] = (char) ((m & 0x00ff0000) >> 16);
       cipherText[ctr + 3] = (char) ((m & 0xff000000) >> 24);

       m = 1;
   }

#if DEBUG
   Serial.println("==========BEGIN CIPHERTEXT==========");
   for(int i = 0; i < CIPHERTEXT_SIZE; i++) {
       Serial.print(cipherText[i]);
   }
   Serial.println("\n===========END CIPHERTEXT===========");
#endif
}

void RSA::decrypt(char *plainText, char *cipherText, long *privateKey)
{
   long M = 1;
   long n = privateKey[0];
   long d = privateKey[1];
   long temp = 0;
   int ctr = 0;

   //re-assemble char array to array of long
   for(int i = 0; i < PLAINTEXT_SIZE; i++) {
       ctr = i * sizeof(long);
       temp = (((unsigned char)cipherText[ctr + 3] << 24) | ((unsigned char)cipherText[ctr + 2] << 16) | ((unsigned char)cipherText[ctr + 1] << 8) | (unsigned char)cipherText[ctr]);
       
       for(int j = 0; j < d; j++) {
           M = (M * temp) % n;
       }

       plainText[i] = (unsigned char)(M & 0xFF); 
//       Serial.print(temp); Serial.print(" "); Serial.println((unsigned char)plainText[i], DEC);
       M = 1;
   }

#if DEBUG
   Serial.println("==========BEGIN PLAINTEXT==========");
   for(int i = 0; i < PLAINTEXT_SIZE; i++)
       Serial.print(plainText[i]); 
   Serial.println("\n===========END PLAINTEXT===========");
#endif
}

bool RSA::compare(char *arr1, char *arr2, int len)
{
    int res = 0;
    
    res = memcmp(arr1, arr2, len);
    if(res == 0)
        return true;
    else 
        return false;
}
