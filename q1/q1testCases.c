/* Start Header
*****************************************************************/
/*!
\file q1testCases.c
\author Jodie Moh
\date 24/03/2021
\brief
This is a preset test case values file to q1.c.
This is meant for the user to use these preset test cases if the user do not 
wish to key in individual inputs manually.
*/
/* End Header
*******************************************************************/
/**
 * @brief This function changes the values, using the preset test case to 
 * runProgram() to proceed with the banker algorithm program.
 * 
 * @note The parameters are all constant type in order to make its value fix, 
 * to prevent changes in the underlying value.
 * @param psize This is refering to the int type variable that represent the 
 * process size.
 * @param rsize This is refering to the int type variable that represent the 
 * resource size.
 * @param av This is a pointer to an integer to dereference available value. 
 * @param al This is a pointer to an integer to dereference allocation value. 
 * @param m This is a pointer to an integer to dereference max value.
 * @brief These are the 6 preset testcases: testCase1() testCase2() testCase3() 
 * testCase4() testCase5() testCase6()
 */
void changeVals(const int psize, const int rsize, 
const int *av, const int *al, const int *m)
{
    int i = 0, j = 0;
    for (i = 0; i < psize; i++)
    {
        for(j = 0; j < rsize; j++)
        {
            if(i==0) avail[j] = av[j];
            alloc[i][j] = al[i*rsize+j];
            max[i][j] = m[i*rsize+j];
        }
    }
}
/**
 * @brief First test case that is a "5 x 4" matrix input.
 * @note This will result in a safe state, P0 -> P2 -> P3 -> P4 -> P1.
 */
void testCase1()
{
    /*safe5x4*/
    int av[4] = {1, 1, 0, 0};
    int al[5][4] = {{0, 0, 1, 2},
                    {1, 4, 2, 0},
                    {1, 3, 5, 4},
                    {0, 6, 3, 2},
                    {0, 0, 1, 4}};
    int m[5][4] =  {{0, 0, 1, 2},
                    {1, 7, 5, 0}, 
                    {2, 3, 5, 6},
                    {0, 6, 5, 2},
                    {1, 6, 5, 6}};
    psize = 5;
    rsize = 4;
    changeVals(psize, rsize,av,(int *)al,(int *)m);
    runProgram(psize, rsize, 0);
}

/**
 * @brief First test case that is a "5 x 4" matrix input.
 * @note This will result in a unsafe state.
 */
void testCase2()
{
    /*unsafe5x4*/
    int av[4] = {0, 1, 0, 0};
    int al[5][4] = {{0, 0, 1, 2},
                    {1, 4, 2, 0},
                    {1, 3, 5, 4},
                    {0, 6, 3, 2},
                    {0, 0, 1, 4}};
    int m[5][4] =  {{0, 0, 1, 2},
                    {1, 7, 5, 0}, 
                    {2, 3, 5, 6},
                    {0, 6, 5, 2},
                    {1, 6, 5, 6}};
    psize = 5;
    rsize = 4;
    changeVals(psize, rsize,av,(int *)al,(int *)m);
    runProgram(psize, rsize, 0);
}

/**
 * @brief First test case that is a "5 x 4" matrix input.
 * @note This will result in a safe state, P4 -> P1 -> P2 -> P3 -> P0.
 */
void testCase3()
{
    /*safe2-5x4*/
    int av[4] = {2, 0, 0, 1};
    int al[5][4] = {{1, 0, 2, 0},
                    {0, 3, 1, 2},
                    {2, 4, 5, 1},
                    {3, 0, 0, 6},
                    {4, 2, 1, 3}};
    int m[5][4] =  {{3, 2, 4, 2},
                    {3, 5, 1, 2},
                    {2, 7, 7, 5},
                    {5, 5, 0, 8},
                    {6, 2, 1, 4}};
    psize = 5;
    rsize = 4;
    changeVals(psize, rsize,av,(int *)al,(int *)m);
    runProgram(psize, rsize, 0);
}

/**
 * @brief First test case that is a "4 x 5" matrix input.
 * @note This will result in a safe state, P3 -> P0 -> P2 -> P1.
 */
void testCase4()
{
    /*safe4x5*/
    int av[5] = {0, 0, 1, 1, 1};
    int al[4][5] = {{1, 0, 2, 1, 1},
                    {2, 0, 1, 1, 0},
                    {1, 1, 0, 1, 0},
                    {1, 1, 1, 1, 0}};
    int m[4][5] =  {{1, 1, 2, 1, 2},
                    {2, 2, 2, 1, 0},
                    {2, 1, 3, 1, 0},
                    {1, 1, 2, 2, 1}};
    psize = 4;
    rsize = 5;
    changeVals(psize, rsize,av,(int *)al,(int *)m);
    runProgram(psize, rsize, 0);
}

/**
 * @brief First test case that is a "4 x 5" matrix input.
 * @note This will result in a safe state, P3 -> P0 -> P2 -> P1.
 */
void testCase5()
{
    /*safe4x5*/
    int av[5] = {0, 0, 1, 1, 1};
    int al[4][5] = {{1, 0, 2, 1, 1},
                    {2, 0, 1, 1, 0},
                    {1, 1, 0, 1, 0},
                    {1, 1, 1, 1, 0}};
    int m[4][5] =  {{1, 1, 2, 1, 2},
                    {2, 2, 2, 1, 0},
                    {2, 1, 3, 1, 0},
                    {1, 1, 2, 2, 1}};
    psize = 4;
    rsize = 5;
    changeVals(psize, rsize,av,(int *)al,(int *)m);
    runProgram(psize, rsize, 0);
}

/**
 * @brief First test case that is a "5 x 4" matrix input.
 * @note This will result in a unsafe state, P3 -> P4 -> P1.
 */
void testCase6()
{
    /*unsafe5x4*/
    int av[4] = {3, 0, 1, 1};
    int al[5][4] = {{2,1,2,2},
                    {4,0,2,1},
                    {1,3,2,1},
                    {1,1,1,0},
                    {2,0,2,1}};
    int m[5][4] =  {{4,2,6,6},
                    {6,1,4,3}, 
                    {2,5,4,3},
                    {3,1,2,1},
                    {3,1,3,2}};
    psize = 5;
    rsize = 4;
    changeVals(psize, rsize,av,(int *)al,(int *)m);
    runProgram(psize, rsize, 0);
}