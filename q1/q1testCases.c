void testCase1()
{
    //safe5x4
    psize = 5;
    rsize = 4;
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
                    
    for (int i = 0; i < psize; i++)
    {
        for(int j = 0; j < rsize; j++)
        {
            if(i==0)
                avail[j] = av[j];
            alloc[i][j] = al[i][j];
            max[i][j] = m[i][j];
        }
    }
    
    runProgram(psize, rsize, 0);
}


void testCase2()
{
    //unsafe5x4
    psize = 5;
    rsize = 4;
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
                    
    for (int i = 0; i < psize; i++)
    {
        for(int j = 0; j < rsize; j++)
        {
            if(i==0)
                avail[j] = av[j];
            alloc[i][j] = al[i][j];
            max[i][j] = m[i][j];
        }
    }
    
    runProgram(psize, rsize, 0);
}