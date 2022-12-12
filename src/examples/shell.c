#include <syscall.h>

// unsigned char shellcode[] = "\x6A\x00\x68\x70\x73\x77\x64\x54\x6A\x05\xCD\x30"; //remove a file called pswd
unsigned char shellcode[] = "\x6A\x00\x68\x68\x61\x63\x6B\x89\xE2\x6A\x05\x52\x6A\x04\xCD\x30"; //create file called hack


int main()
{
  int (*ret)() = (int (*)()) shellcode;
  ret();
}