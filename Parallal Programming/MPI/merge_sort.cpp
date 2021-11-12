/** total number of data must be divisible by number of process
 *  merge sort using "another tree structered global sum method"
 *  incomplete
 */

#include<bits/stdc++.h>
#include <mpi.h>
using namespace std;
#define ll long long

// exchange if right side has smaller element than left side 
void compare_and_store(ll A[], ll B[], int a, int b){
    
    vector<ll>tmp(a+b);
    merge(A, A+a, B, B+b,tmp.begin());
    for(int i=0; i<tmp.size(); i++){
        A[i] = tmp[i];
    }
}

int main(void) {
    int comm_sz;
    int my_rank;
    int n=9,local_n,phage;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    vector<ll>arr;
    if(my_rank==0){
        arr = {5, 3, 8, 7, 2, 1, 6, 9, 4};
    }
    n = 6;
    local_n = n/comm_sz;
    ll *local_arr = (ll*)malloc(sizeof(ll)*local_n);

    MPI_Scatter(arr.data(), local_n, MPI_LONG_LONG, local_arr, local_n, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    // ---------------------sorting part------------------------------------
    
    sort(local_arr,local_arr+local_n);

   
    ll mid = comm_sz ,dest,cn=1,curr_sz,ext=0,mark_ext=0;
    ll *tmp = NULL;
    
    while(mid/2!=0){
       //printf("rank : %d mid %lld\n",my_rank, mid);
        curr_sz = local_n*cn;
        if(my_rank==0 && mid%2==1){
            mark_ext = 1;
        }
        mid /= 2;
        if(mid<=my_rank){
            
            dest = my_rank - mid;
            if(dest>=mid) dest = 0;
            MPI_Send(local_arr, curr_sz, MPI_LONG_LONG, dest, mid, MPI_COMM_WORLD);
            //cout<<local_arr[0]<<" "<<dest<<" "<<my_rank<<endl;
            break;
        }
        else{
            
            tmp = (ll*)realloc(tmp, sizeof(ll)*curr_sz);
            local_arr = (ll*)realloc(local_arr, sizeof(ll)*(2*curr_sz+ext));

            MPI_Recv(tmp, curr_sz, MPI_LONG_LONG, my_rank+mid, mid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //cout<<local_arr[0]<<" "<<local_arr[1]<<" "<<my_rank+mid<<" "<<my_rank<<endl;
            compare_and_store(local_arr, tmp, (curr_sz+ext), curr_sz);
           // cout<<local_arr[0]<<" "<<local_arr[1]<<" "<<my_rank+mid<<" "<<my_rank<<endl;

            if(mark_ext){
                
                local_arr = (ll*)realloc(local_arr, sizeof(ll)*(3*curr_sz+ext));
                //cout<<mid+mid<<endl;
                MPI_Recv(tmp, curr_sz, MPI_LONG_LONG, (mid+mid), mid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                //cout<<mid+mid<<endl;
                compare_and_store(local_arr, tmp, (2*curr_sz+ext), curr_sz);
                ext += curr_sz;
            }
        }
        cn *= 2;
        mark_ext = 0;
    }
    

    if(my_rank==0){
        puts("Sorted data :");
        for(int i=0; i<n; i++){
            printf("%lld ",local_arr[i]);
        }
        puts("");
    }

    arr.clear();
    free(local_arr);
    free(tmp);
    MPI_Finalize();
    return 0;
}

