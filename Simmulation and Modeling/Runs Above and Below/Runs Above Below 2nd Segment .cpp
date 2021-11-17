//Anik_Modak
#include<bits/stdc++.h>
#define MX 100005
using namespace std;

int numbers[MX];
int main()
{
    freopen("1st-segment-out.txt","r",stdin);
    freopen("2nd-segment-out.txt","w",stdout);

    int n, n1, n2, runs, mr;
    n = n1 = n2 = runs = 0;
    mr = -1;

    int mean_val, mx = 0;
    while(cin>>numbers[++n])
    {
        mx = max(mx, numbers[n]);
    }
    mean_val = ((double)mx + 0.0)/2.0;

    cout<<"Sequence of run ups and downs : ";
    for(int i=1; i<n; i++)
    {
        if(numbers[i] > mean_val)
        {
            cout<<'+'<<" ";
            if(mr != 1)
                runs++;
            n1++;
            mr = 1;
        }
        else
        {
            cout<<'-'<<" ";
            if(mr != 0)
                runs++;
            n2++;
            mr = 0;
        }
    }

    double mean, variance, z;
    mean = 2*n1*n2/(double)n + 0.5;
    variance = 2*n1*n2*(2*n1*n2 - n)/(double)(n*n*(n-1));
    z = (runs - mean)/sqrt(variance);

    cout<<"\n\nAbove from the mean : "<<n1<<endl;
    cout<<"Below from the mean : "<<n2<<endl;
    cout<<"Total number of runs  : "<<runs<<endl;
    cout<<"Mean : "<<mean<<endl;
    cout<<"Variance : "<<variance<<endl;
    cout<<"Z0 : "<<z<<endl;

    if(z >= -1.96 && z <= 1.96)
        cout<<"Result : ACCEPTED\n";
    else
        cout<<"Result : NOT ACCEPTED\n";
    return 0;
}
