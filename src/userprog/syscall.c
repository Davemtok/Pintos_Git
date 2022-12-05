// #include "userprog/syscall.h"
// #include <stdio.h>
// #include <syscall-nr.h>
// #include "threads/interrupt.h"
// #include "threads/thread.h"
#include "filesys/directory.h"
// #include "filesys/filesys.h"
// #include "filesys/file.h"
// #include "devices/shutdown.h"
// #include "userprog/process.h"

#include "userprog/syscall.h"
#include "userprog/process.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "lib/user/syscall.h"
#include "threads/vaddr.h"
#include "lib/stdio.h"
#include "devices/shutdown.h"
#include "lib/string.h"
#include "threads/palloc.h"
#include "devices/input.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "threads/synch.h"

static void syscall_handler (struct intr_frame *);

struct lock files_lock;
void
syscall_init (void)
{
  lock_init (&files_lock);
          intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f )
{
    // const char * name;
    // const char * file_name;
    // unsigned int initial_size;
    // int tid_t;
    // char* parameter1;

    //int code_tester = *(int*)f->esp;
    printf ("system call!\n");
    void *esp = f->esp;
    // int ret = exec((const char *)*(esp + 1));

    //int code_tester = 0;
    // int code_tester = 9;
    //int code_tester = 3;
    
    switch (*(int*)(esp )) 
    { 

        case SYS_HALT: // 0
        {
            printf("HALT CALL ACTIVATED\n");
            shutdown_power_off();
            break;
        }

        case SYS_EXIT: // 1
        {
            printf("EXIT CALL ACTIVATED\n");
            thread_exit();
            break;
        }

        case SYS_EXEC: // 2
        {
            
            const char* cmdline=*(char**)(f->esp + 4);
            f->eax  = process_execute((const char*) cmdline);
            break;
        }


        case SYS_REMOVE: // 5
        {
            char *name=*( char**)(esp + 4);
            lock_acquire(&files_lock);
            f->eax=filesys_remove(name);
            lock_release(&files_lock);
            printf("System Call Executed Successfully\n");
            break;
        }

        //working on write at the moment
        case SYS_WRITE: // 9
        {
            printf("WRITE\n");
            
            char *buffer=*( char**)(esp + 8);
            unsigned size= *(unsigned*)(esp + 12);
            putbuf(buffer, size);
            int ret_write = size;
            f->eax = ret_write;
            break;}

        default :
            printf("No SYSTEM CALL %d \n", *(int*)(esp));
        thread_exit ();
        break;
    }

}
