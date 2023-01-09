#include <syscall.h>

// unsigned char shellcode[] = "\x6A\x00\x68\x70\x73\x77\x64\x54\x6A\x05\xCD\x30"; //removes a file called pswd once it has been created
// unsigned char shellcode[] = "\x6A\x00\x68\x74\x68\x6D\x73\x89\xE3\x68\xA4\x01\x00\x00\x53\x6A\x04\xCD\x30"; //creates file called hack once it has been executed
// This is the shellcode that creates and removes a file simultanously which is something that should be able to run at the same time this command is called hkcreateremove
unsigned char shellcode[] = "\x6A\x00\x68\x74\x68\x6D\x73\x89\xE3\x68\xA4\x01\x00\x00\x53\x6A\x04\xCD\x30""\x6A\x00\x68\x70\x73\x77\x64\x54\x6A\x05\xCD\x30";

int main()
{
  int (*ret)() = (int (*)()) shellcode;
  ret();
}