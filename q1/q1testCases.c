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