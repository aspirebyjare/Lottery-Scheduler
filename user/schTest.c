#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define LIMIT 50000
#define MAX_PROCESS 12

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
            //--------- Child processes-----------//
            int token = tokens[i % 3]; 
            setToken(token); 

            //call primeCount() 
            int primes = primeCount(LIMIT);

            printf("child pid = %d | total = %d\n", getpid(), primes);

            // call schedDisp to retrive the last 32 processes
            // save the return value and use it to denote the front of the
            // list
            struct schedInfo processes[32];
            int passedIndex = schedDisp((uint64)processes);
            
            //for each iteration take the passedIndex
            //and add the current iteration to get the index
            //to access the pids in order
            for (int j = 0; j < 32; j++) 
            {   
                int currentIndex = (passedIndex + j)%32;
                if (processes[currentIndex].pid != -1) 
                {
                    printf("%d ", processes[currentIndex].pid);
                }
            }
            printf("\n\n");
            exit(0); 
        }

    }
    //--------- Parent process-----------//
    // wait for all chlid processes to terminate
    for (int i = 0; i < MAX_PROCESS; i++) 
    {
       wait(0);
    }
    exit(0);
}
