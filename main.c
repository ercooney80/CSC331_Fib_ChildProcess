/*
 * Author: 	Edward Cooney
 * Class:       main.c
 * Section: 	CSC331-01
 * Date:       	02/01/2014
 * Notes:       This program prints the Fibonacci sequence.    
 *              The child process will call two functions to get the user input 
 *              and to print Fibonacci numbers starting at fib0 and going to  
 *		fib(thisMany).  The program can calculate up to fib93 due to 
 *              the use of unsigned long long for output.
 *              FIB_92        =  7540113804746346429
 *              FIB_93        = 12200160415121876738 
 *              MAV_VALUE ULL = 18446744073709551615
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

/* Prototypes */
static int getInput();
static void fibonacci(int);

int main() {
    pid_t pid;
    int thisMany;

    /*fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) { /* child process */
        /* Get user input */
        thisMany = getInput();

        /* Print numbers */
        printf("Child process is calculating fib sequence for "
                "%d numbers...\n", thisMany);
        fibonacci(thisMany);
        
    } else { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("\nChild Complete\n");
    }
    return 0;
}

/*-----------------------------------------------------------------------------
        Name: getInput
        Args: n/a 
        Returns: The list of finonacci numbers the user wants
        Calls: n/a
        Called By: main()
        Notes: Requires a number >= 1 or <= 93 in order to return.  
-----------------------------------------------------------------------------*/
static int getInput() {

    // User input
    int num;
    printf("How many Fibonacci numbers do you want to see? ");
    scanf("%d", &num);

    // Simple out-of-bounds input check
    while (num < 1 || num > 93) {
        printf("That is an invalid quantity.\n");
        printf("How many fib numbers do you want: ");
        scanf("%d", &num);
    }
    return num;
}

/*-----------------------------------------------------------------------------
        Name: Fibonacci
        Args: n - Number of Fibonacci numbers to display
        Returns: n/a
        Calls: n/a
        Called main()
        Notes: Prints out the Fibonacci sequence requested by the user
-----------------------------------------------------------------------------*/
static void fibonacci(int n) {
    unsigned long long fib0 = 0, fib1 = 1; // f(n-1) and f(n-2) Seeds
    int i; // for loop increment 	
    unsigned long long sum = 0; // Next number in sequence   
    
    // print fib0 and fib1
    printf("fib0: %llu\n", fib0);
    if (n >= 1) printf("fib1: %llu\n", fib1);
    
    // print fib2 to fib(n)
    for (i = 2; i <= n; i++) {
        sum = fib0 + fib1;
        fib0 = fib1;
        fib1 = sum;
        printf("fib%d: %llu\n", i, sum);

    }
}



