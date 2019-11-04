// gcc -O0 20190921.c -lcrypto -o key_check
#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>

//static void printError(char *msg, unsigned long err);
int check(RSA* key);
void test_your_key();

int check(RSA* key)
{
  const BIGNUM *n, *e;
  int public_exponent, modulus;

  if(key==NULL)return -1;
  RSA_get0_key(key, &n, &e, NULL);
  public_exponent = BN_get_word(e);
  modulus = BN_num_bits(n);

  if (public_exponent != 65537)return -1;
  if (512 > modulus || modulus > 8192)return -1;

  return 0;
}

void test_your_key()
{
  unsigned int len, len2,a;
  char buf;
  BIO *mem = BIO_new(BIO_s_mem());
  RSA *x = NULL;
  unsigned char c[512];
  const unsigned char msg[] = "If you see this message, your RSA key is valid!";
  unsigned char *pem;
  unsigned char *data;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  memset(c,0,512);

  pem = malloc(4096);

  while(1)
  {
  puts("Please input your public key: ");
    for(a=0;a<2000;a++)
    {
    buf = getchar();
    if(buf=='.'){pem[a]='\x00';break;}
    pem[a] = buf;
    }
  pem[a] = '\x00';
  getchar();

  BIO_puts(mem, pem);
  x = PEM_read_bio_RSAPublicKey(mem, NULL, NULL, NULL);
    if(x==NULL || check(x)==-1)
    {
    puts("Something wrong...");
    exit(0);
    }
  printf("Key test: ");
  len = RSA_size(x);
  len2 = RSA_public_encrypt(len,msg,c,x,RSA_NO_PADDING);
    if(len2==-1)
    {
    printf("Error: %s\n", ERR_reason_error_string(ERR_get_error()));
    exit(0);
    }

  puts("Give me your private key!");
    for(a=0;a<4000;a++)
    {
    buf = getchar();
    if(buf=='.'){pem[a]='\x00';break;}
    pem[a] = buf;
    }
  pem[a] = '\x00';
  //getchar();

  BIO_puts(mem, pem);
  x = PEM_read_bio_RSAPrivateKey(mem, NULL, NULL, NULL);
    if(x==NULL || check(x)==-1)
    {
    puts("Something wrong...");
    //puts(pem);
    exit(0);
    }
  len = RSA_size(x);
  printf("%d\n",len);
  data = malloc(len);
  len2 = RSA_private_decrypt(len, c, data, x, RSA_NO_PADDING);
    if(len2==-1)
    {
    printf("Error: %s\n", ERR_reason_error_string(ERR_get_error()));
    exit(0);
    }

  puts("Decryption complete.");
  puts(data);
  puts("continue?(y/n)");
    while(1)
    {
    buf = getchar();
    if(buf == 'Y' || buf == 'y')break;
    if(buf == 'N' || buf == 'n')return;
    }
  }
}

int main(int argc, char *argv[])
{
  test_your_key();
  return 0;
}
