#include<bits/stdc++.h>
#include <mpi.h>
using namespace std;
#define ll long long

// exchange if right side has smaller element than left side 
void compare_and_store(ll A[], ll B[], int size){
    vector<ll>tmp(size+size);
    merge(A, A+size, B, B+size,tmp.begin());
    for(int i=0; i<tmp.size(); i++){
        if(i<size){
            A[i] = tmp[i];
        }
        else{
            B[i-size] = tmp[i];
        }
    }
    tmp.clear();
}

// just sendig message of current phage and receving after compare and store
void idle_phage(ll local_arr[], int local_n, int phage, int my_rank){
    MPI_Send(local_arr, local_n, MPI_LONG_LONG, my_rank-1, phage,MPI_COMM_WORLD);
    MPI_Recv(local_arr, local_n, MPI_LONG_LONG, my_rank-1, phage, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

// receive meassage then compare and merge then send to its sender
void active_phage(ll local_arr[], ll tmp[], int local_n, int phage, int my_rank){
    MPI_Recv(tmp, local_n, MPI_LONG_LONG, my_rank+1, phage, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    compare_and_store(local_arr, tmp, local_n);
    MPI_Send(tmp, local_n, MPI_LONG_LONG, my_rank+1, phage,MPI_COMM_WORLD);
}

int main(void) {
    int comm_sz;
    int my_rank;
    int n=8, local_n,phage;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    vector<ll>arr;
    ll *result = NULL; 
    if(my_rank==0){
        arr = {5, 3, 7, 8, 2, 1, 6, 9, 4};
        result = (ll*)malloc(sizeof(ll)*n);
    }
    
    //n = 8;
    local_n = n/comm_sz;
    ll local_arr[local_n];

    MPI_Scatter(arr.data(), local_n, MPI_LONG_LONG, local_arr, local_n, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    // ---------------------sorting part-------------------------------------
    
    sort(local_arr,local_arr+local_n);
    
    ll * tmp = new ll(local_n+2);

    for(phage  = 1; phage <= comm_sz; phage++){
        if(phage%2==1){
            if(my_rank%2==0){
                if(my_rank != 0){
                    idle_phage(local_arr, local_n, phage, my_rank);
                }
            }
            else if(my_rank!=comm_sz-1){
                active_phage(local_arr, tmp, local_n, phage, my_rank);
            }
        }
        else{
            if(my_rank%2==0){
                if(my_rank!=comm_sz-1){
                    active_phage(local_arr, tmp, local_n, phage, my_rank);
                }
            }
            else if(my_rank != 0){
                idle_phage(local_arr, local_n, phage, my_rank);
            }
        }
    }
    
    /// gather and print section of all sorted data

    MPI_Gather(local_arr, local_n, MPI_LONG_LONG, result, local_n, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    if(my_rank==0){
        puts("Sorted data :");
        for(int i=0; i<n; i++){
            printf("%lld ",result[i]);
        }
        puts("");
        free(result);
    }

    delete(tmp);
    arr.clear();
    MPI_Finalize();
    return 0;
}

