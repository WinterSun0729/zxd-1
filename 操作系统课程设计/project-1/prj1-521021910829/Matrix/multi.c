#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int **matrix1;
int **matrix2;
int **res_mat;

int size, num_threads;

struct mat{
int row1;//row of mat1
int column1;//column of mat1
int row2;//row of mat2
int column2;//column of mat2
};

//run partitional matrix multiplication in pthread
void *matrix_multiply(void *args)
{
    int i, j, k, tid, portion_size, row_start, row_end;
    double sum;
    
    tid = *(int *)(args); // get the thread ID assigned sequentially.
    portion_size = size / num_threads;
    row_start = tid * portion_size;
    row_end = (tid+1) * portion_size;

    for (i = row_start; i < row_end; ++i) { // hold row index of 'matrix1'
    for (j = 0; j < size; ++j) { // hold column index of 'matrix2'
        sum = 0; // hold value of a cell
        for (k = 0; k < size; ++k) { 
	        sum += matrix1[i][k] * matrix2[k][j];
        }
        res_mat[i][j] = sum;
    }
  }
}

int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("more argv needed\n command: ./multi <number of threads> <(size of matrix)>");
        return -1;
    }
    //version 1
    else if(argc == 2){
        pthread_t * threads;
        num_threads = atoi(argv[1]);

        //open read file1
        FILE *src1;
        src1 = fopen("data.in","r");
        if(src1 == NULL){
            printf("Error!");
            fclose(src1);
            exit(-1);
        }
        FILE *src2;
        src2 = fopen("data.in","r");
        if(src2 == NULL){
            printf("Error!");
            fclose(src2);
            exit(-1);
        }
        struct mat *data = (struct mat *) malloc(sizeof(struct mat));
        //read file and parse the matrix
        fscanf(src1, "%d", &data->row1);
        data->column1 = data->row1;
        size = data->column1;
        matrix1 = malloc(data->row1 * sizeof(int*));
        for(int i = 0; i < data->row1; ++i){
            matrix1[i] = malloc(data->column1 * sizeof(int));
            for(int j = 0; j < data->column1; ++j)
                fscanf(src1, "%d", &matrix1[i][j]);
        }
        fclose(src1);
        //second matrix
        fscanf(src2, "%d", &data->row2);
        data->column2 = data->row2;
        matrix2 = malloc(data->row2 * sizeof(int*));
        for(int i = 0; i < data->row2; ++i){
            matrix2[i] = malloc(data->column2 * sizeof(int));
            for(int j = 0; j < data->column2; ++j)
                fscanf(src2, "%d", &matrix2[i][j]);
        }
        fclose(src2);

        if ( size % num_threads != 0 ) {
            fprintf( stderr, "size %d must be a multiple of num of threads %d\n",
                size, num_threads );
            return -1;
        }

        res_mat = malloc(data->row1 * sizeof(int*));
        for(int i = 0; i < data->row1; ++i){
            res_mat[i] = malloc(data->row1 * sizeof(int));
        }

        ////////////////////////////////////////////////////////////
        //ptread
        threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );
        
        for (int i = 0; i < num_threads; ++i ) {
            int *tid;
            tid = (int *) malloc( sizeof(int) );
            *tid = i;
            pthread_create( &threads[i], NULL, matrix_multiply, (void *)tid );
        }

        //set and start timer
        clock_t start, end;
        double elapsed;
        start = clock();
        for (int i = 0; i < num_threads; ++i ) {
            pthread_join( threads[i], NULL );
        }
        //end timer
        end = clock();
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

        FILE *dest;
            dest = fopen("data.out","w+");
            if(dest == NULL){
                printf("Error!");
                fclose(dest);
                exit(-1);
            }
        for(int i = 0; i < data->row1; i++) {
            for(int j = 0; j < data->column2; j++) {
                fprintf(dest, "%d ", res_mat[i][j]);
            }
            fprintf(dest, "\n");
        }
        fclose(dest);
        printf("Time used: %f millisecond.\n", elapsed);

        return 0;
    }
    
    //version 2
    else if(argc == 3){
        pthread_t * threads;
        num_threads = atoi(argv[1]);
        size = atoi(argv[2]);
        if ( size % num_threads != 0 ) {
        fprintf( stderr, "size %d must be a multiple of num of threads %d\n",
            size, num_threads );
        return -1;
        }

        //create random matrix
        matrix1 = malloc(size * sizeof(int*));
        for(int i = 0; i < size; ++i){
            matrix1[i] = malloc(size * sizeof(int));
            for(int j = 0; j < size; ++j)
                matrix1[i][j] = rand()%100;
        }
        matrix2 = malloc(size * sizeof(int*));
        for(int i = 0; i < size; ++i){
            matrix2[i] = malloc(size * sizeof(int));
            for(int j = 0; j < size; ++j)
                matrix2[i][j] = rand()%100;
        }
        res_mat = malloc(size * sizeof(int*));
        for(int i = 0; i < size; ++i){
            res_mat[i] = malloc(size * sizeof(int));
        }


        ////////////////////////////////////////////////////////////
        //ptread
        threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );
        
        for (int i = 0; i < num_threads; ++i ) {
            int *tid;
            tid = (int *) malloc( sizeof(int) );
            *tid = i;
            pthread_create( &threads[i], NULL, matrix_multiply, (void *)tid );
        }

        //set and start timer
        clock_t start, end;
        double elapsed;
        start = clock();
        for (int i = 0; i < num_threads; ++i ) {
            pthread_join( threads[i], NULL );
        }
        //end timer
        end = clock();
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

        FILE *dest;
            dest = fopen("random_data.out","w+");
            if(dest == NULL){
                printf("Error!");
                fclose(dest);
                exit(-1);
            }
        fprintf(dest, "%d\n", size);
        fprintf(dest, "Matrix A:\n");
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                fprintf(dest, "%d %d %d\n", i, j, matrix1[i][j]);
            }
        }
        fprintf(dest, "Matrix B:\n");
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                fprintf(dest, "%d %d %d\n", i, j, matrix2[i][j]);
            }
        }
        fprintf(dest, "Matrix AB:\n");
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                fprintf(dest, "%d %d %d\n", i, j, res_mat[i][j]);
            }
        }
        fclose(dest);
        printf("Time used: %f millisecond.\n", elapsed);

        return 1;
    }
    else{
        printf("argv overflow \n command: ./multi <number of threads> <size of matrix>");
        return -1;
    }
}