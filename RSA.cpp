#include "RSA.h"

RSA rsa;

RSA::RSA()
{

}

RSA::~RSA()
{

}

void RSA::encrypt(char *plainText, char *cipherText, int *publicKey)
{
   long m = 1;
   int n = publicKey[0];
   int e = publicKey[1];
   int ctr = 0;

   for(int i = 0; i < PLAINTEXT_SIZE; i++) {
       for(int j = 0; j < e; j++) {
           m = (m * plainText[i]) % n;
       }
       
       ctr = i * sizeof(int);

       cipherText[ctr]     = (char) (m & 0x00ff);
       cipherText[ctr + 1] = (char) ((m & 0xff00) >> 8);

       m = 1;
   }

#if DEBUG
   Serial.println("\n==========BEGIN CIPHERTEXT==========");
   for(int i = 0; i < CIPHERTEXT_SIZE; i++) {
       Serial.print((unsigned char)cipherText[i], DEC); Serial.print(" ");
   }
   Serial.println("\n===========END CIPHERTEXT===========\n");
#endif
}

void RSA::decrypt(char *plainText, char *cipherText, int *privateKey)
{
   long M = 1;
   int n = privateKey[0];
   int d = privateKey[1];
   int temp = 0;
   int ctr = 0;

   //re-assemble char array to array of int
   for(int i = 0; i < PLAINTEXT_SIZE; i++) {
       ctr = i * sizeof(int);
       temp = (((unsigned char)cipherText[ctr + 1] << 8) | (unsigned char)cipherText[ctr]);
       
       for(int j = 0; j < d; j++) {
           M = (M * temp) % n;
       }

       plainText[i] = (unsigned char)(M & 0xFF); 
       M = 1;
   }

#if DEBUG
   Serial.println("\n==========BEGIN PLAINTEXT==========");
   for(int i = 0; i < PLAINTEXT_SIZE; i++)
       Serial.print(plainText[i]); 
   Serial.println("\n===========END PLAINTEXT===========\n");
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
