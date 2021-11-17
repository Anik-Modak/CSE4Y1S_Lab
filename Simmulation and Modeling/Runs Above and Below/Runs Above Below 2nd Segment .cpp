//Anik_Modak
#include<bits/stdc++.h>
using namespace std;

int numbers[100005];
int main()
{
    freopen("1st-segment-out.txt","r",stdin);
    freopen("2nd-segment-out.txt","w",stdout);

    int n, n1, n2, mr, mean_middle;
    n = n1 = n2 = 0;
    mr = -1;
    mean_middle = (0+(double)n-1.0)/2.0;

    while(cin>>numbers[n++]);

    cout<<"Sequence of run ups and downs : ";
    for(int i=1; i<n; i++)
    {
        if(numbers[i]>mean_middle)
        {
            cout<<'+'<<" ";
            if(mr!=1)
                n1++;
            mr = 1;
        }
        else
        {
            cout<<'-'<<" ";
            if(mr!=0)
                n2++;
            mr = 0;
        }
    }

    double mean, variance, z, runs = n1+n2;
    mean = 2*n1*n2/(double)n + 0.5;
    variance = 2*n1*n2*(2*n1*n2 - n)/(double)(n*n*(n-1));
    z = (runs - mean)/sqrt(variance);

    cout<<"\n\n";
    cout<<"Above from the mean : "<<n1<<endl;
    cout<<"Below from the mean : "<<n2<<endl;
    cout<<"Maximum number of possible runs : "<<n1+n2<<endl;
    cout<<"Mean : "<<mean<<endl;
    cout<<"Variance : "<<variance<<endl;
    cout<<"Z0 : "<<z<<endl;

    if(z >= -1.96 && z <= 1.96)
        cout<<"Result : ACCEPTED\n";
    else
        cout<<"Result : NOT ACCEPTED\n";
    return 0;
}
