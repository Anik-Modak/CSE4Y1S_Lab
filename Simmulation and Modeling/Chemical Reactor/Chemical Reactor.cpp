//Anik_Modak
#include<bits/stdc++.h>
#include<graphics.h>
using namespace std;

double A[100],B[100],C[100];
int main()
{
    freopen("chemical_reactor.txt","r",stdin);
    int N=20;
    float k1,k2;
    cin>>k1>>k2;
    cin>>A[0]>>B[0];
    C[0] = 0;

    double T=0, Delta = 0.1;
    printf("\t\t\tChemical Reactor Problem\n\n");
    printf("Time\t\t\tA(I)\t\t\tB(I)\t\t\tC(I)\n");

    double mx = max(A[0], B[0]);
    for(int i=0; i<=N; i++)
    {
        printf("%0.4f\t\t\t%0.4f\t\t\t%0.4f\t\t\t%0.4f\n",T,A[i],B[i],C[i]);
        A[i+1]=A[i]+(k2*C[i]-k1*A[i]*B[i])*Delta;
        B[i+1]=B[i]+(k2*C[i]-k1*A[i]*B[i])*Delta;
        C[i+1]=C[i]+2*(k1*A[i]*B[i]-k2*C[i])*Delta;
        T=T+Delta;
        mx = max(A[i+1], max(B[i+1], C[i+1]));
    }

    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");

    int fctx, fcty, inc = 30;
    int ymx = getmaxy();
    fctx = (double)(getmaxx()-inc)/N;
    fcty = (getmaxy()-inc*4)/(int)mx;

    setcolor(15);
    line(inc, 0, inc, getmaxy());
    line(0, ymx - inc, getmaxx(), ymx - inc);

    for(int j=1,k=30+fctx; j<=N; j++,k+=fctx)
    {
        setcolor(15);
        line(k-fctx, ymx - inc - A[j-1]*fcty, k, ymx - inc - A[j]*fcty);
        delay(50);

        setcolor(15);
        line(k-fctx, ymx - inc - B[j-1]*fcty, k, ymx - inc - B[j]*fcty);
        delay(50);

        setcolor(5);
        line(k-fctx, ymx - inc - C[j-1]*fcty, k, ymx - inc - C[j]*fcty);
        delay(50);
    }

    getch();
    closegraph();
    return 0;
}
