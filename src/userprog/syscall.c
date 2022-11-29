#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "filesys/directory.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "devices/shutdown.h"
#include "userprog/process.h"


static void syscall_handler (struct intr_frame *);

void
syscall_init (void)
{
          intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


static void
syscall_handler (struct intr_frame *f UNUSED)
{
    const char * name;
    const char * file_name;
    unsigned int initial_size;
    int tid_t;
    char* parameter1;
    
    // int code_tester = *(int*)f->esp;
    printf ("system call!\n");
    
    // int code=f->esp;

    int code_tester = 1;
    switch (code_tester) 
    { 
        
        case SYS_HALT: //0
        {
            shutdown_power_off();
            break;
        }

        case SYS_CREATE:
        {
            parameter1 = *(char*) f->esp +4;
            unsigned int parameter2 = *(unsigned int*) f->esp +8;
            parameter1 = name;
            parameter2 = initial_size;
            filesys_create(name, initial_size);
            printf("System Call Executed Successfully\n");
            break;
        }

        case SYS_REMOVE:
        {
            parameter1 = *(char*) f->esp + 4;
            parameter1 = name;
            filesys_remove(name);
            printf("System Call Executed Successfully\n");
            break;
        }

            
        case SYS_WAIT:
        {
            process_wait(tid_t);
            break;
        }

        case SYS_EXIT: // 1
        {
        int exitcode;
        memread_user(f->esp + 4, &exitcode, sizeof(exitcode));

        sys_exit(exitcode);
        NOT_REACHED();
        break;
        }

        default :
            printf("No SYSTEM CALL %d \n", code_tester);
        thread_exit ();
        break;
    }
}
