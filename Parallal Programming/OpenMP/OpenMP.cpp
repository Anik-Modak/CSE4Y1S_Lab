#include<bits/stdc++.h>
 
#ifdef _OPENMP
#include<omp.h>
#endif
 
using namespace std;
 
void hello(void){
 
   int my_rank = 0;
   int number_of_thread = 1;
 
   #ifdef _OPENMP
       my_rank = omp_get_thread_num();
       number_of_thread = omp_get_num_threads();
   #endif
 
   cout<<"Rank :"<< my_rank<<" of " << number_of_thread<<"threads"<<endl;
}
 
int main(int argc, char * argv[]){
 
   int thread_count = strtol(argv[1],NULL,10);
 
   // this pragma is a pre processor which will start openmp code if we don't put this , then the programm will run as a seial code of cpp
   # pragma omp parallel num_threads(thread_count)
 
   hello();
 
   return 0;
}
