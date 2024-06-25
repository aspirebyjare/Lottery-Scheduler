#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define LIMIT 50000

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
    int howManyPrimes = primeCount(LIMIT);
    printf("The number of primes between 2 and %d is: %d\n", LIMIT, howManyPrimes);
    return 0;
}
