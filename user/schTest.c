#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define LIMIT 50000
#define MAX_PROCESS 1 

// returns number of primes between 2 and a passed int
int primeCount(int limit)
{
    int numOfPrimes = 0;  // Change to integer

    for (int n = 2; n < limit; n++) 
    {
        int isPrime = 0;// flag for true

        for (int i = 2; i <= n / 2; i++) 
        {
            if (n % i == 0) {
                isPrime = -1; // flag for false
                break;
            }
        }

        if (isPrime ==0) 
        {   
            numOfPrimes++;
        }
    }
    return (numOfPrimes);
}

struct schedInfo {
    int pid;
    int tokens;
};

    /* 
    primeCount() computes the count of prime numbers between 2 and some LIMIT
    initialize LIMIT=50000; 
    make sure to stop at n/2

    After finishing the following
    create schTest.c(this file)
    MAX_PROCESS=12;
        fork (MAX_PROCESS many (12)) children 
            they will all be doing the same cpu bound program
                loop to create child processes
                each child will adjust its number of tokens 
                    4 with 5 tokens
                        setToken(5);
                    4 with 10 tokens
                        setToken(10);
                    4 with 15 tokens
                        setToken(15);
         int 
                after 
                for each child
                    call primeCount()
                        int count = primeCount();
                    display process pid
                        int childPID= getpid();
                    call schedDisp to retrive the last 32 processes
                        // maybe
                           int scheduledPIDs [] =schedDisp();
                            for (int i =0 ; i < sizeof(scheduledPIDs); i++)
                            {
                                printf("%d ", scheduledPIDs[i]);
                            }
                            printf("\n");
                            
    */
int schedDisp(uint64 address);

int main() 
{
    // print stats
    printf("-----schTest---- \nMAX: %d LIMIT: %d parentPID: %d\n\n", MAX_PROCESS, LIMIT, getpid());
    int childrenPIDs[MAX_PROCESS];
    int tokens[] = {5, 10, 15}; 

    for (int i = 0; i < MAX_PROCESS; i++) 
    {
        if ((childrenPIDs[i] = fork()) == 0) 
        {
            // Child process
            int token = tokens[i % 3]; 
            setToken(token); 

            //call primeCount() 
            int primes = primeCount(LIMIT);
            wait(0);// used to stop print statements from jumbling
            printf("child pid = %d: total = %d\n", getpid(), primes);

            // call schedDisp to retrive the last 32 processes
            struct schedInfo processes[32];
            schedDisp((uint64)processes);

            printf("last 32 processes scheduled (Most recent to least recent)\n");
            for (int j = 0; j < 32; j++) 
            {
               // printf(" ( %d )",processes[j].pid ); // test
                if (processes[j].pid != -1) 
                {
                    //printf("In procs loop\n"); // test
                    wait(0);
                    printf("%d ", processes[j].pid);
                }
            }
            printf("\n");

            exit(0); 
        }
    }

    // Parent processes
    //for (int i = 0; i < MAX_PROCESS; i++) 
    //{
       //wait(0);
    //}

    //printf("parent Done\n");
    exit(0);
}
