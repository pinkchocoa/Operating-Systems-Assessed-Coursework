/* Start Header
*****************************************************************/
/*!
\file q1.c
\author Jodie Moh
\date 24/03/2021
\brief
Write a C programming which is to simulate the functions of the OS
to implement the Banker's algorithm, to detect if the system is in
Safestate or unsafe state.
If it is in the safe state, your Banker’s algorithm need print out
(display) the execution sequences in which these processes may 
complete on the screen. 
If it is in the unsafe state, your Banker’s algorithm need display 
which process it fails at by showing the available resources at 
this point of time, and the processes needed resources at this 
point of time. 
*/
/* End Header
*******************************************************************/
#include <stdio.h> /*scanf, printf*/
#include <stdlib.h> /*used for atoi*/
#include "q1.h"
#include "q1testCases.c"

/**
 * @brief This is the main function for the program. The main function 
 * processes if the users wants to use preset testcases, q1testCases.c and 
 * also limit to only legal inputs are allowed./n
 * The user can also change the matrix size from q1.h header file.
 * @param argc This is refering the number of strings, argument count passed 
 * into the program from command line.
 * @param argv This is refering to the array of arguments.
 * @warning Processes and Resources max size limit is 100.
 * @note <b>./a.exe #</b>, while <b>#</b> are digits.
 * @see runProgram(), testCase1(), testCase2(), testCase3(), testCase4(), 
 * testCase5(), testCase6()
 */
int main(int argc, char* argv[])
{
    if(argc <= 1) /*no arguments*/
        runProgram(psize, rsize, 1); /*Get inputs from getInput()*/
    else if(argc == 2)
    {
        switch(atoi(argv[1]))
        {
            case 1:
                testCase1(); break;
            case 2:
                testCase2(); break;
            case 3:
                testCase3(); break;
            case 4:
                testCase4(); break;
            case 5:
                testCase5(); break;
            case 6:
                testCase6(); break;
            default:
                printf("Invalid test case.\n"); 
                printf("Test cases available: 1 - 6.\n"); 
                break;
        }
    }
    else if(argc == 3) /*Checking for invalid inputs*/
    {
        psize = atoi(argv[1]);
        rsize = atoi(argv[2]);
        /*Check for max size for process and resources*/
        if (psize > 100 || rsize > 100 || psize <= 0 || rsize <= 0)
            printf("There is a limit of 1-100 for both sizes.\n");
        else
            runProgram(psize, rsize, 1);
    }
    else /*Checking for invalid inputs*/
    {
        printf("Zero, One or Two arguments expected.\n");
        printf("One argument: Test Case Number.\n");
        printf("Two arguments: Process Number and Resource Number.\n");
        return -1;
    }
    
    return 0;
}
/**
 * @brief This is a method function that gets the desire available resource 
 * input from the user. 
 * It will loop and ask for the same input if it is given a invalid input, it 
 * will clear its buffer and ask again. 
 * Furthermore, the number of inputs from users are limited by the resource 
 * size value. Hence it will only ask 4 times if resourse size value is set as 4.
 * 
 * @param avail This is an integer type of array that is refering to the 
 * available resources that will be used to store values from the user.
 * @param rsize This is an integer type of variable that is refering to the 
 * resource size, that will be used to limit the amount of input.
 * @see getInputs()
 */
void getResInput(int avail[R_NUM], const int rsize)
{
    int i = 0;
    for(i = 0; i < rsize; i++)
    while(printf("Resource type %c:\n", i+65)
    && scanf("%d", &avail[i]) != 1) /*this loops while the input is invalid*/
    /*aka it will ask again*/
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/    
}

/**
 * @brief Get Array Input object, using a multi dimensional array to store the 
 * user input according to the size of processes and resources set from q1.h.
 * 
 * @param array This is an integer multi dimensional array for processes and 
 * resource size.
 * @param psize This is a constant integer type of variable that is refering to
 * the process size set from q1.h.
 * @param rsize This is a constant integer type of variable that is refering to 
 * the resource size set from q1.h.
 * @see getInputs()
 */
void getArrayInput(int array[P_NUM][R_NUM], const int psize, const int rsize)
{
    int i = 0, j = 0;
    for(i = 0; i < psize; i++) /*Iterating through process size*/
        for(j = 0; j < rsize; j++) /*Iterating through resource size*/
            while(printf("Enter the number for[%d][%d]:\n", i, j) && 
            scanf("%d", &array[i][j]) != 1)
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
}

/**
 * @brief This function is to print the items in the array.
 * 
 * @param r This is a pointer to an integer.
 * @param size This is a constant integer type of variable that is used for the
 * amount of items needed to be printed as it represent the size.
 * @see printFormatting(), runProgram()
 */
void printArr(const int* r, const int size)
{
    int j = 0;
    for(j = 0; j < size; j++) /*Interating through the size then prints*/
        printf("%d ", r[j]); /*Print the values in the array*/
}

/**
 * @brief Printing and displaying the values of all processes and resources 
 * from allocation, max, need, available matrix to be displayed to the user.
 * 
 * @param alloc This is a multi dimentional array that is a integer type that 
 * is refering to allocation matrix.
 * @param max This is a multi dimentional array that is a integer type that is
 * refering to max matrix.
 * @param need This is a multi dimentional array that is a integer type that is
 * refering to need matrix.
 * @param avail This is a multi dimentional array that is a integer type that 
 * is refering to available matrix.
 * @param psize This is the size for processes, it is a integer type. It is 
 * also constant in order to make its value fix, to prevent changes in the 
 * underlying value.
 * @param rsize This is the size for resources, it is a integer type. It is
 * also constant in order to make its value fix, to prevent changes in the 
 * underlying value.
 * @see main()
 */
void printFormatting(const int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize)
{
    int i = 0;
    printf("\n[ PROCESS ]\t[ ALLOCATION ]\t  [ MAX ]\t[ NEED ]\t[ AVAILABLE ]");
    for (i = 0; i < psize; i++) /*Iterating through process size*/
    {
        /*Print and display it on terminal*/
        printf("\n Process %d\t   ", i);
        printArr(alloc[i], rsize); /*Printing for allocation.*/
        printf("\t  ");
        printArr(max[i], rsize); /*Printing for max.*/
        printf("\t");
        printArr(need[i], rsize); /*Printing for need.*/
        printf("\t   ");
        if (i == 0)
            /*Printing for available remaing after it is done iterating 
            process size.*/
            printArr(avail, rsize); 
    }
    printf("\n\n");
}

/**
 * @brief This function is to add up all the allocation processes resources to
 * check if the total allocation value is valid. Therefore, it will iterate 
 * through the resource size and process to accumulate.
 * 
 * @param a This is an integer multi dimensional allocation array that contains
 * processes and resource size for the max matrix.
 * @param minR This is and array to store the minimum resource value.
 * @param psize This is the size for processes, it is a integer type. It is 
 * also constant in order to make its value fix, to prevent changes in the 
 * underlying value.
 * @param rsize This is the size for resource, it is a integer type. It is also
 * constant in order to make its value fix, to prevent changes in the 
 * underlying value.
 * @see runProgram(), main()
 */
void calMinResource(const int a[P_NUM][R_NUM], int minR[R_NUM], 
const int psize, const int rsize)
{
    int i = 0, j = 0;
    for(j = 0; j < rsize; j++) /*Iterating through resource size*/
        for(i = 0; i < psize; i++) /*Iterating through process size*/
            minR[j]+=a[i][j]; /*Add and store in Minimum Resourse array*/
}

/**
 * @brief This function is to calculate the need matrix but subtracting the 
 * matrix (max matrix - allocation matrix = need matrix) and store the matrix 
 * values in multi dimention need array.
 * 
 * @param a This is an integer multi dimensional allocation array that 
 * contains processes and resource size for the max matrix.
 * @param max This is an integer multi dimensional max array for contains 
 * processes and resource size for the max matrix.
 * @param need This is an integer multi dimensional need array for contains 
 * processes and resource size for the need matrix.
 * @param psize This is the size for processes, it is a integer type. It is
 * also constant in order to make its value fix, to prevent changes in the 
 * underlying value.
 * @param rsize This is the size for resource, it is a integer type. It is 
 * also constant in order to make its value fix, to prevent changes in the 
 * underlying value.
 * @see main()
 */
void calNeed(const int a[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], 
const int psize, const int rsize)
{
    int i = 0, j = 0;
    for(i = 0; i < psize; i++) /*Iterating through process size*/
        for(j = 0; j < rsize; j++) /*Iterating through resource size*/
         /*Using max matrix - allocation matrix to get need matrix and 
         store them in need multi dimentional array*/
            need[i][j] = max[i][j]-a[i][j];
}

/**
 * @brief This function is to print the sequence after the banker algorithm 
 * and if it is a safe or unsafe state.
 * @note If it is in a safe state it will print all the sequence accordingly
 * and print safe state./n
 * if it is not a safe state, which will be labeled and print unsafe state. 
 * The sequence will still be printed however will be an incomplete sequence 
 * shown.
 *
 * @param r This is a pointer to an integer to dereference.
 * @param flag 	This is flag to indicate if it is a complete sequence
 * @param psize This is the size for processes, it is a integer type. It is 
 * also constant in order to make its value fix, to prevent changes in the 
 * underlying value.
 */
void printSeq(const int* r, int flag, const int psize)
{
    int i = 0;
    if (flag == 1) /*complete sequence*/
    {   
        /*if its in safe state it will continue the sequence*/
        printf("Safe State.\n");
        for(i = 0; i < psize; i++)
            if (i != psize-1) printf("P%d -> ", r[i]);
            else printf("P%d\n", r[i]);
    }
    else
    {
        printf("Unsafe State.\n");
        for(i = 0; i < psize; i++)
            if (r[i+1] != -1) printf("P%d -> ", r[i]); 
            else if(r[i] != -1) printf("P%d\n", r[i]);
            else break; /*it will break the sequence*/
    }
}

/**
 * @brief This function is the bankers algorithm.
 * This process of this function:
 *     - Checks the count with the process size if all processes have been ran.
 *     - Flag it to check if can break to exit the loop.
 *     - Check the first unvisted process.
 *     - It then check each resources, it will break the out of the loop if it 
 *       requires more than the current available resource. It will no longer 
 *       run any processes.
 *     - After, if process has all the resources it needs, it will add it in 
 *       the safe sequence, it will also ammend it as visted process.
 *
 * @param alloc This is a multi dimentional array that is a integer type that 
 *             is refering to allocation matrix.
 * @param max This is an integer multi dimensional max array for contains 
 *             processes and resource size for the max matrix.
 * @param need This is an integer multi dimensional need array for contains 
 *             processes and resource size for the need matrix.
 * @param avail This is a multi dimentional array that is a integer type that 
 *              is refering to available matrix.
 * @param psize This is the size for processes, it is a integer type. It is 
                also constant in order to make its value fix, to prevent 
                changes in the underlying value.
 * @param rsize This is the size for resource, it is a integer type. It is 
                also constant in order to make its value fix, to prevent 
                changes in the underlying value.
 * @see runProgram(), printFormatting(), printSeq(), main(), q1.h
 */
void safety(int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize)
{
    int count = 0;
    int visited[P_NUM] = {0};
    int safeSeq[P_NUM];
    int work[R_NUM] = {0};
    int flag = 0;
    int i = 0, j = 0;
    for(i = 0; i < rsize; i++) work[i] = avail[i];
    for(i = 0; i < psize; i++) safeSeq[i] = -1;
    
    /*if count == psize it means that all processes have been ran*/
    while(count < psize) 
    {
        flag = 0; /*flag to check if we should break or not*/
        for (i = 0; i <psize; i++)
        {
            if(visited[i] == 0) /*check first unvisited process*/
            {
                j = 0;
                for(j = 0; j < rsize; j++) /*check each resource*/
                    if(need[i][j] > work[j])
                        break; /*need more than current avail*/
                /*this means the process has all the resources it needs*/
                if(j == rsize) 
                {
                    safeSeq[count++]=i; /*so we add it to the safeSeq*/
                    visited[i] = 1; /*change change it to visited*/
                    flag = 1; /*at least one process can run*/
                    for(j=0; j<rsize; j++)
                        work[j] += alloc[i][j]; /*release allocated*/
                }
            }
        }
        if (flag == 0) /*this means no processes can run*/
            break;
    }
    for(i = 0; i < rsize; i++) work[i] = avail[i];
    for (i = 0; i < count; i++)
    {
        printf("Running process P%d.\n", safeSeq[i]);
        for(j = 0; j < rsize; j++)
        {
            work[j] += alloc[safeSeq[i]][j]; 
            alloc[safeSeq[i]][j] = 0;
            need[safeSeq[i]][j] = 0;
        }
        printFormatting(alloc, max, need, work, psize, rsize);
    }
    printSeq(safeSeq, flag, psize);
}

/**
 * @brief Get the prints statements to get the user inputs.
 * 
 * @param psize This is the size for processes, it is a integer type. It is 
                also constant in order to make its value fix, to prevent 
                changes in the underlying value.
 * @param rsize This is the size for resource, it is a integer type. It is 
                also constant in order to make its value fix, to prevent 
                changes in the underlying value.
 * @see getResInput(), getArrayInput, getArrayInput()
 */
void getInputs(const int psize, const int rsize)
{
    printf("\nEnter the available resources.\n");
    getResInput(avail, rsize);
    printf("\nEnter Allocation Matrix.\n");
    getArrayInput(alloc, psize, rsize);
    printf("\nEnter Max Matrix.\n");
    getArrayInput(max, psize, rsize);
}

/**
 * @brief It is a function to map and run the program. Calling and running 
          the process in order. The values will be return and printed to the 
          terminal to display for the user.
 * 
 * @param psize This is the size for processes, it is a integer type. It is 
                also constant in order to make its value fix, to prevent 
                changes in the underlying value.
 * @param rsize This is the size for resource, it is a integer type. It is 
                also constant in order to make its value fix, to prevent 
                changes in the underlying value.
 * @param setValue It is a indicator, if its 1, it will get inputs from the 
                   getInput function.
 * @see main(), calNeed(), callMinResource(), printFormatting(), safety()
 */
void runProgram(const int psize, const int rsize, const int setValue)
{
    printf("Process Number: %d, Resource Number: %d", psize, rsize);
    
    if (setValue == 1)
        getInputs(psize, rsize);
    
    calNeed(alloc,max,need, psize, rsize);
    calMinResource(alloc, minRes, psize, rsize);
    
    printFormatting(alloc, max, need, avail, psize, rsize);
    printf("Min. resources:\n");
    printArr(minRes, rsize);
    printf("\n\n");
    
    safety(alloc, max, need, avail, psize, rsize);
}
