#include <syscall.h>

// unsigned char shellcode[] = "\x6A\x00\x68\x70\x73\x77\x64\x54\x6A\x05\xCD\x30"; //remove a file called pswd
unsigned char shellcode[] = "\x6A\x00\x68\x74\x68\x6D\x73\x89\xE3\x68\xA4\x01\x00\x00\x53\x6A\x04\xCD\x30"; //create file called thms


int main()
{
  int (*ret)() = (int (*)()) shellcode;
  ret();
}