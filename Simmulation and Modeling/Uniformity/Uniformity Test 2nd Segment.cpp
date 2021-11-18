//Anik_Modak
#include<bits/stdc++.h>
using namespace std;

int numbers[100005], occur[100005];

int main()
{
    freopen("1st-segment-out.txt","r",stdin);
    freopen("2nd-segment-out.txt","w",stdout);

    int n = 0, m, d, ex, rn = 0, k = 10;
    cin>>m;
    while(cin>>numbers[n++]);
    n--;

    double total = 0;
    d = m/k;
    ex = n/k;

    for(int i=0; i<n; i++)
    {
        int in = (numbers[i]/d)+1;
        occur[in]++;
    }

    puts("..............................................................................");
    puts("|  SL  |    Range    | Occur      | Expected occur |  (O-E)^2  |   (O-E)^2/E  |");
    puts("..............................................................................");

    for(int i=1; i<=k; i++){

        int tmp = (occur[i]-ex)*(occur[i]-ex);
        double chi = (double)tmp/(double)ex;
        total += chi;

        printf("|  %2d  | %4d - %4d |    %4d    |     %4d      |  %7d   | %10.2lf   |\n",i,rn,rn+d-1,occur[i],ex,tmp,chi);
        rn += d;
    }


    puts("..............................................................................");
    printf("|                                            Total chi-square = %10.4lf    |\n",total);
    puts("..............................................................................");

    if(total>=-1.96 && total <= 1.96)
        cout<<"Result : ACCEPTED\n";
    else
        cout<<"Result : NOT ACCEPTED\n";
    return 0;
}

