#include "types.h"
#include "user.h"

#define WNOHANG 1

int main(int argc, char *argv[])
{

    int priorSchedulerTest(void);      // test for main assignment, not implemented
    int starvationTest(void);          // test for bonus 1, not implemented
    int donationInheritanceTest(void); // test for bonus 2, not implemented
    int performanceTest(void);         // test for bonus 3, not implemented

    printf(1, "\nThis program tests the correctness of your lab#2\n\n");

    if (atoi(argv[1]) == 1)
        priorSchedulerTest();
    else if (atoi(argv[1]) == 2)
        starvationTest();
    else if (atoi(argv[1]) == 3)
        donationInheritanceTest();
    else if (atoi(argv[1]) == 4)
        performanceTest();
    else
        printf(1, "\ntype \"lab2 1\" to test priority scheduler, \"lab2 2\" to test starvation \"lab2 3\" to test the donation/inheritance and \n\"lab2 4\" to test scheduling performance");

    // End of test
    printf(1, "\n");
    exit();
    return 0;
}

int priorSchedulerTest()
{
    // printf(1, "Running priority scheduler test... unimplemented");

    int pids[3];
    int i = 0;
    while (i < 3)
    {
        pids[i] = fork();
        printf(1, "creating process with pid: %d\n", pids[i]);
        if (pids[i] == 0)
        {
            break;
        }
        i++;
    }

    if (pids[0])
    {
        printf(1, "Catching process with pid: %d\n", pids[0]);
        wait();
    }
    if (pids[1])
    {
        printf(1, "Catching process with pid: %d\n", pids[1]);
        wait();
    }
    if (pids[2])
    {
        printf(1, "Catching process with pid: %d\n", pids[2]);
        wait();
    }
    return 0;
}

int starvationTest()
{
    printf(1, "Running starvation test... unimplemented");
    return 0;
}

int donationInheritanceTest()
{
    printf(1, "Running donation/inheritance test... unimplemented");
    return 0;
}

int performanceTest()
{
    printf(1, "Running performance test... unimplemented");
    return 0;
}