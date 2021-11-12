#include<bits/stdc++.h>
#include<pthread.h>
 
using namespace std;
 
int thread_count;
 
// function to run from creating a thread
void * hello(void * rank){
   long my_rank = (long) rank;
   cout<<"printing from :"<<my_rank<<endl;
   return NULL;
}
 
int main(int argc, char * argv[]){
   long thread;
   pthread_t * thread_handels;
 
   thread_count = strtol(argv[1], NULL, 10); // reading number of thread from the commmnad line
   // allocating thread handles object which is opaque object
   thread_handels = (pthread_t *) malloc(thread_count * sizeof(pthread_t));
 
 
   // starting thread with the thread create function
   for(thread = 0; thread < thread_count; thread++){
       pthread_create(&thread_handels[thread], NULL, hello, (void *) thread);
   }
 
   puts("printing from main program");
 
   // joining or ending threads by this segment
   for(thread = 0; thread < thread_count; thread++){
       pthread_join(thread_handels[thread], NULL);
   }
 
   // freeing allocated memory by malloc fucntion
   free(thread_handels);
 
   return 0;
}
