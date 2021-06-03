#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int importCSV(const char* path, float *matrix, int rows, int columns, bool strict, bool verbose){
    char buffer[1024] ;
    char *record,*line;
    int i=0,j=0;
    FILE *fstream = fopen(path,"r");
    if(fstream == NULL){
        printf("file opening failed\n");
        return -1;
    }

 
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
        if(i>=rows){
            printf("rows exceeded row limit\n");
            return -1;
        }
        j=0;
        record = strtok(line,",");
        while(record != NULL){
            if(j>=columns){
                printf("columns exceeded column limit\n");
                return -1;
            }
            // printf("%d ", *matrix);

            // printf("%d ", (i*columns) + j);
            *((matrix+i*columns) + j) = atof(record);
            if(verbose){
                printf("%f, ", atof(record)); 
            }
            record = strtok(NULL,",");
            j++;
        }
        if(strict && j != columns){
            printf("columns should exactly be column limit: %d", columns);
            return -1;
        }

        if(verbose){
            printf("%d, \n", i);
        }
         
        i++;
        
    }
    return 0;
}

float accessMatrix(float *matrix, int row_num, int column_num, int columns){
    return matrix[row_num*columns+column_num];
}

int main(){
    int rows = 100, columns = 4;
    float matrix[rows][columns];
    // matrix = malloc(rows * columns * sizeof *matrix);

    importCSV("test.csv", (float *)matrix, rows, columns, true, false);
    int i = 0, j = 0;
    for(i = 0; i < 20; i++){
        for(j=0;j<4;j++){
            printf("%f ", matrix[i][j]);

        }
        printf("\n");
    }
    // free(matrix);
}