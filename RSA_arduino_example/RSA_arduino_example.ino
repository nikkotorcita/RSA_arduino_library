#include <RSA.h>

int led = 13;

char msg[PLAINTEXT_SIZE] = "The quick brown fox jumped over the lazy dog. Does it really have to be this?";

int publicKey[2] = {14351, 11};
int privateKey[2] = {14351, 1283};

void setup()
{
  Serial.begin(115200);
  
  char cipher_msg[CIPHERTEXT_SIZE];
  rsa.encrypt(msg, cipher_msg, publicKey);
  for(int i = 0; i < CIPHERTEXT_SIZE; i++)
    Serial.write(cipher_msg[i]);
  
  pinMode(led, OUTPUT);
}
void loop()
{
  char cipher[CIPHERTEXT_SIZE];
  char plain[PLAINTEXT_SIZE];
  
  memset(cipher, 0, CIPHERTEXT_SIZE);
  memset(plain, 0, PLAINTEXT_SIZE);
  
  while(!Serial.available());
  if(Serial.available() > 0)
    Serial.readBytes(cipher, CIPHERTEXT_SIZE);
  
  rsa.decrypt(plain, cipher, privateKey);
  
  if(strstr(plain, "enable") != NULL)
    digitalWrite(led, HIGH);
  else if(strstr(plain, "disable") != NULL)
    digitalWrite(led, LOW);
}
