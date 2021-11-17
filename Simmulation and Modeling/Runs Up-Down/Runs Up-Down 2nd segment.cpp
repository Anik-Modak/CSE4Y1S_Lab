//Anik_Modak
#include<bits/stdc++.h>
using namespace std;

int numbers[100005];
int main()
{
    freopen("1st-segment-out.txt","r",stdin);
    freopen("2nd-segment-out.txt","w",stdout);

    int n = 0, runs = 0, mr = -1;

    //input from file
    while(cin>>numbers[++n]);

    n--;
    cout<<"Sequence of run ups and downs : ";
    for(int i=1; i<n; i++)
    {
        if(numbers[i+1] > numbers[i])
        {
            cout<<'+'<<" ";
            if(mr!=1)
                runs++;
            mr = 1;
        }
        else
        {
            cout<<'-'<<" ";
            if(mr!=0)
                runs++;
            mr = 0;
        }
    }

    double mean, variance, z;

    mean = (2*n-1)/3.0;
    variance = (16*n-29)/90.0;
    z = ((double)runs - mean)/sqrt(variance);

    cout<<"\nTotal numbers : "<<n<<endl;
    cout<<"Number of runs : "<<runs<<endl;
    cout<<"Mean : "<<mean<<endl;
    cout<<"Variance : "<<variance<<endl;
    cout<<"Z0 : "<<z<<endl;

    if(z >= -1.96 && z <= 1.96)
        cout<<"Result : ACCEPTED\n";
    else
        cout<<"Result : NOT ACCEPTED\n";
    return 0;
}
