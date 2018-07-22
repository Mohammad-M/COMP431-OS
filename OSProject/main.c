/// This project is an implementation of Banker's Algorithm,
///
/// the  program reads the following from a text file:
///                 -    int  P --> number of processes running
///                 -    int R --> number of resource types
///                 -    MAXIMUM, ALLOCATION, AVAILABLE  to get details about the system.
///
/// the  program output is the following:
///                 -	The matrix MAXIMUM.
///                 -	The matrix ALLOCATION.
///                 -	The matrix NEEDS.
///                 -	The array AVAILABLE.
///                 -	The safe sequence of process if the system is safe and an Error Message if the system is not safe.
///
///                 -   In the project file there is 4 text files to test the code "safe1,safe2,unsafe1,unsafe2"
///
///\\\\\ Done by: Mohammad M. Mohammad #1141648


#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    FILE *fp;                                                       ///
    char fileName[MAX], line [MAX];                                 ///
    int P = 0, R = 0, i, j, z, element;                             /// initialing needed  variables and arrays
    char str [10];                                                  ///
    char *pch;                                                      ///
    int K[P], flag = 1, count = 0, safe[P], out [P], o = 0;         ///

    printf("Enter the file name:\t"); ///reading a file name supposed to be in Project folder
    scanf("%s",fileName);             ///

    fp = fopen(fileName,"r");///opining file in read mod
    while ( fp == NULL )///loop to check file exist and re inter file name
    {
         system("cls");///Clear Screen
         printf("File ( %s ) dose not exist!\n", fileName);
         printf("Enter the file name:\t");
         scanf("%s",fileName);
         fp = fopen(fileName,"r");///opining file in read mod
     }
    ///Reading the first two lines P & R
    fgets(line, sizeof line, fp);
    removeNewLine(line);
    P = atoi (line);

    fgets(line, sizeof line, fp);
    removeNewLine(line);
    R = atoi (line);

    ///MAXIMUM array to hold the maximum needs of resources the set of processes P
    int MAXIMUM[P][R];

    ///ALLOCATION array to hold the currently allocated resources of the set of processes P
    int ALLOCATION[P][R];

    ///AVAILABLE array to hold the currently available resources
    int AVAILABLE[R];

    ///NEEDS array to hold the currently needed resources of the set of processes P
    int NEEDS[P][R];


    fgets(line, sizeof line, fp);///to remove the line
    ///loop to read the MAXIMUM array
    for (i = 0; i < P; i++)
    {
        j = 0;
        fgets(line, sizeof line, fp);
        removeNewLine(line);

        pch = strtok (line," ");///Split by space

        while(pch != NULL)
        {
            strcpy(str, pch);
            element = atoi (str);///saving 'str' as a int
            MAXIMUM[i][j] = element;///saving MAXIMUM value
            j++;
            pch = strtok (NULL, " ");
        }

    }

    fgets(line, sizeof line, fp);///to remove the line
    ///loop to read the ALLOCATION array
    for (i = 0; i < P; i++)
    {
        j = 0;
        fgets(line, sizeof line, fp);
        removeNewLine(line);

        pch = strtok (line," ");///Split by space

        while(pch != NULL)
        {
            strcpy(str, pch);
            element = atoi (str);///saving 'str' as a int
            ALLOCATION[i][j] = element;///saving ALLOCATION value
            j++;
            pch = strtok (NULL, " ");
        }

    }

    ///reading the AVILABLE array
    fgets(line, sizeof line, fp);
    j = 0;
    fgets(line, sizeof line, fp);
    removeNewLine(line);

    pch = strtok (line," ");///Split by space

    while(pch != NULL)
    {
        strcpy(str, pch);
        element = atoi (str);///saving 'str' as a int
        AVAILABLE[j] = element;///saving AVAILABLE value
        j++;
        pch = strtok (NULL, " ");
        }

    fclose(fp);

    ///calculate the NEEDS array
    for ( i = 0; i < P; i++)
    {
        for ( j = 0; j < R; j ++)
        {
            NEEDS[i][j] = MAXIMUM[i][j] - ALLOCATION [i][j];
        }

    }


    ///printing the output
    printf("P = %d \t R = %d\n", P, R);
    printf("\nThe MAXIMUM array:\n");
    for ( i = 0; i < P; i++)
    {
        for ( j = 0; j < R; j ++)
        {
            printf("%d\t", MAXIMUM[i][j]);
        }
        printf("\n");
    }
    printf("\nThe ALLOCATION array:\n");
    for ( i = 0; i < P; i++)
    {
        for ( j = 0; j < R; j ++)
        {
            printf("%d\t", ALLOCATION[i][j]);
        }
        printf("\n");
    }

     printf("\nThe NEEDS array:\n");
    for ( i = 0; i < P; i++)
    {
        for ( j = 0; j < R; j ++)
        {
            printf("%d\t", NEEDS[i][j]);
        }
        printf("\n");
    }

    printf("\nThe AVAILABLE array:\n");
    for ( i = 0; i < R; i++)
    {
        printf("%d\t", AVAILABLE[i]);
    }
    printf("\n");


    ///Check if the system is safe
    ///Banker algorithm

    ///FIRST STEP: initializing K array as 1's
    for(i = 0;i < P; i++)
    {
        K[i] = 1;
    }

    while(flag)  ///flag for the loop correct continuity
    {
		  flag = 0;
			for(i = 0; i < P; i++) ///to check the resources for each proses (needs <= available)
		    {
				   int c = 0;
				   for(j = 0; j < R; j++)
				   {
						if((K[i]== 1)&&(NEEDS[i][j] <= AVAILABLE[j]))
						{
							c++;
							if(c == R)
							 {
								for(z = 0; z < R; z++)///if a proses completed its resources will be released as available
								{
										AVAILABLE[z] += ALLOCATION[i][j];
										K[i] = 0;
										flag = 1;
								}
								out[o] = i;///proses finished
								o++;
								if(K[i] == 0)
								{
                                    i = P;
								}
							 }
						}
				   }
			}
    }

    for(i = 0; i < P; i++)/// if a proses is not completed will be saved here
    {
        if(K[i]== 0)
        {
            count++;
        }
        else
        {
            out[o] = i;
            o++;
        }
    }

    if(count == P)///final result of system safety
    {
        printf("\n The system is in safe state");
        printf("\nThe safe sequence< ");
        for (i = 0; i < P-1; i++)
        {
            printf("P%d->", out[i]);
        }
        printf("P%d >", out[P-1]);
    }
    else
    {
        printf("\n System are in dead lock");
        printf("\n System is in unsafe state");
    }
    return 0;
}

 ///Function to remove \n from a string
 void removeNewLine(char *str)
{
  char *p1 = str, *p2 = str;
  do
    while (*p2 == '\n')
      p2++;
  while (*p1++ = *p2++);
}
