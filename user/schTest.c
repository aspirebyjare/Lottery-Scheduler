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
int main()
{
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
                after 
                    each 
                        call primeCount()
                        display process pid
                        call schedDisp to retrive the last 32 processes
                            // maybe
                               int scheduledPIDs [] =schedDisp();
                                for (int i =0 ; i < sizeof(scheduledPIDs); i++)
                                {
                                    printf("")
                                }
                            
    */
}
