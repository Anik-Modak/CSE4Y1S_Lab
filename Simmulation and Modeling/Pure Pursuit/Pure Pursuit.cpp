#include<bits/stdc++.h>
#include<graphics.h>
#define MX 100007
using namespace std;

double  bx[MX],by[MX];
double  fx[MX],fy[MX];

int main()
{
    int flag=0, time, posx=0, posy=0;
    freopen("pure_pursuit.txt","r",stdin);

    cin>>time;
    for(int i=0; i<=time; i++)
    {
        cin>>bx[i]>>by[i];
        posx = min(posx,(int)bx[i]);
        posy = min(posy,(int)by[i]);
    }

    double vf, distance, sin_theta, cos_theta;
    cin>>fx[0]>>fy[0];
    cin>>vf;

    for(int i=0; i<=time; i++)
    {
        distance = sqrt((bx[i]-fx[i])*(bx[i]-fx[i]) + (by[i]-fy[i])*(by[i]-fy[i]));
        sin_theta = (by[i]-fy[i])/distance;
        cos_theta = (bx[i]-fx[i])/distance;
        fx[i+1] = fx[i] + vf*cos_theta;
        fy[i+1] = fy[i] + vf*sin_theta;

        posx = min(posx,(int)fx[i]);
        posy = min(posy,(int)fy[i]);

        if(distance<=vf && i<time)
        {
            cout<<"Time : "<<i<<"\nDistance : "<<distance<<endl;
            flag = 1;
            time = i;
            break;
        }
    }

    if(!flag)
    {
        cout<<"Target Escaped!\n";
    }

    int gd=DETECT,gm;
    initgraph(&gd, &gm,"");

    int fct = 3,inc = 5;
    int ymx = getmaxy();
    posx = abs(posx);
    posy = abs(posy);

    setcolor(15);
    line((inc+posx)*fct, 0, (inc+posx)*fct, getmaxy());
    line(0, getmaxy() - (inc+posy)*fct, getmaxx(), getmaxy() - (inc+posy)*fct);

    posx = posx+inc;
    posy = posy+inc;

    bx[0] = (bx[0]+posx)*fct;
    by[0] = (by[0]+posy)*fct;
    fx[0] = (fx[0]+posx)*fct;
    fy[0] = (fy[0]+posy)*fct;

    for(int i=1; i<=time; i++)
    {
        bx[i] = (bx[i]+posx)*fct;
        by[i] = (by[i]+posy)*fct;
        fx[i] = (fx[i]+posx)*fct;
        fy[i] = (fy[i]+posy)*fct;

        setcolor(10);
        line(bx[i-1], ymx - by[i-1], bx[i], ymx - by[i]);
        delay(100);

        setcolor(5);
        line(fx[i-1], ymx - fy[i-1], fx[i], ymx - fy[i]);
        delay(100);
    }

    getch();
    closegraph();
    return 0;
}
