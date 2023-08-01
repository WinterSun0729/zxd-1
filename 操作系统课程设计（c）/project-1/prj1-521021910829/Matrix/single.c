#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int **matrix1;
int **matrix2;
int **res_mat;

struct mat{
int row1;//row of mat1
int column1;//column of mat1
int row2;//row of mat2
int column2;//column of mat2
};

//run matrix multiplication in pthread
void *matrix_multiply(void *args){
   struct mat *a = args;
   for (int i = 0; i < a->row1; i++){
		for (int j = 0; j < a->column2; j++){
			res_mat[i][j] = 0;
			for (int k = 0; k < a->column1; k++)
				res_mat[i][j] += matrix1[i][k] *matrix2[k][j];
		}
	}
   pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
   //set and start timer
	clock_t start, end;
	double elapsed;
	start = clock();

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

   res_mat = malloc(data->row1 * sizeof(int*));
   for(int i = 0; i < data->row1; ++i){
      res_mat[i] = malloc(data->row1 * sizeof(int));
   }

   pthread_t tid;
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   
   int rc = pthread_create(&tid,&attr,matrix_multiply,data);
   if (rc) {
      printf("ERROR; return code from pthread_create(tid) is %d\n", rc);
      exit(-1);
   }
   pthread_join(tid, NULL);

   // //Print out the resulting matrix
   // for(int i = 0; i < data->row1; i++) {
   //    for(int j = 0; j < data->column2; j++) {
   //       printf("%d ", res_mat[i][j]);
   //    }
   //    printf("\n");
   // }

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

   //end timer
   end = clock();
   elapsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
   printf("Time used: %f millisecond.\n", elapsed);

   return 0;
}