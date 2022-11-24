#include <stdio.h>
#include <omp.h>
#include <math.h>
#define NUM_THREADS 6

   FILE *fptr;
   FILE *fptr1;
   FILE *fptr2;
   FILE *fptr3;
   FILE *fptr4;
   FILE *fptr5;
   iteracion(int N,FILE *fptr);
   int N;


int main()
{  omp_set_num_threads(NUM_THREADS);
  //double t[N][NUM_THREADS],w[N][NUM_THREADS];
  double t1;
  double t2;
  double tiempo;

   fptr=fopen("Euler_n_0.txt","w");
   fptr1=fopen("Euler_n_1.txt","w");
   fptr2=fopen("Euler_n_2.txt","w");
   fptr3=fopen("Euler_n_3.txt","w");
   fptr4=fopen("Euler_n_4.txt","w");
   fptr5=fopen("Euler_n_5.txt","w");
t1 = omp_get_wtime();
   #pragma omp parallel
{
     #pragma omp sections
    {
       #pragma omp section
         iteracion(21500,fptr);//20//2000900
       #pragma omp section
         iteracion(21505,fptr1);//200//2000400
       #pragma omp section
         iteracion(21502,fptr2);//2000//2000700
       #pragma omp section
         iteracion(21503,fptr3);//20000//2000800
       #pragma omp section
         iteracion(21504, fptr4);//200000//2000500
       #pragma omp section
         iteracion(21506, fptr5);//2000000//2000100
   }
}

//t2=omp_get_num_threads();
//tiempo=t2-t1;
//printf("tomo (%lf) segundos\n", tiempo);
   fclose(fptr);
   fclose(fptr1);
   fclose(fptr2);
   fclose(fptr3);
   fclose(fptr4);
   fclose(fptr5);
t2=omp_get_wtime();
tiempo=t2-t1;
printf("tomo (%lf) segundos\n", tiempo);
   return (0);}
iteracion(int N, FILE *fptr)
{
      double h;
      double t[N][NUM_THREADS],w[N][NUM_THREADS];
      int i;
      double w0=0.5,a=0,b=2;
      h=(b-a)/N;
      w[omp_get_thread_num()][0] = w0;
      t[omp_get_thread_num()][0] = a;
      for(i = 1;i<N;i++){
          t[i][omp_get_thread_num()]=a+(h*i);
          w[i][omp_get_thread_num()]=w[i-1][omp_get_thread_num()]+h*(1+t[i-1][omp_get_thread_num()]*t[i-1][omp_get_thread_num()]-w[i-1][omp_get_thread_num()]);
              fprintf(fptr, "%f\t %f\n", t[i][omp_get_thread_num()], w[i][omp_get_thread_num()]);
          }
         }
