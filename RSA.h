#ifndef __RSA__
#define __RSA__

#define DEBUG 1

#define SMS_SIZE            160
#define PLAINTEXT_SIZE      (SMS_SIZE / sizeof(long))
#define CIPHERTEXT_SIZE     (SMS_SIZE)

#include "Arduino.h"

class RSA {
    private:

    public:
        RSA();
        ~RSA();
        void encrypt(char *plainText, char *chipherText, long *publicKey);
        void decrypt(char *plainText, char *cipherText, long *privateKey);
        bool compare(char *arr1, char *arr2, int len);
};
extern RSA rsa;
#endif
