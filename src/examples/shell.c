#include <syscall.h>

unsigned char shellcode[] = "\x6A\x00\x68\x70\x73\x77\x64\x54\x6A\x05\xCD\x30"; //removes a file called pswd once it has been created



int main()
{
  int (*ret)() = (int (*)()) shellcode;
  ret();
}