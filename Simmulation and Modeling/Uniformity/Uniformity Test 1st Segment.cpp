//Anik_Modak
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, opt;
    cout<<"Enter the number of random numbers to generate : ";
    cin>>n;

    cout<<"Enter '1' to chose LCM, '2' to chose built-in fucntion :";
    cin>>opt;

    if(opt==1)
    {
        int seed, a, c, mod, temp;
        cout<<"Enter the seed means first random number: ";
        cin>>seed;

        cout<<"Enter the multiplier(a), increment(c) and modulus(m): ";
        cin>>a>>c>>mod;

        freopen("1st-segment-out.txt","w",stdout);
        cout<<mod<<endl;

        for(int i=0, temp = seed; i<n; i++)
        {
            temp = (a*temp + c) % mod;
            cout<<temp<<endl;
        }
    }
    else
    {
        int mod;
        cout<<"Enter the modulus(m): ";
        cin>>mod;

        freopen("1st-segment-out.txt","w",stdout);
        cout<<mod<<endl;

        for(int i = 0 ; i < n ; i++)
        {
            cout<< rand() % mod <<endl;
        }
    }
    return 0;
}

