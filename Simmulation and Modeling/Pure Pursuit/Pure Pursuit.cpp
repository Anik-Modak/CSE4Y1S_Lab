//Anik_Modak
#include<bits/stdc++.h>
#include<graphics.h>
#define MX 100007
using namespace std;

int main()
{
    freopen("pure_pursuit.txt","r",stdin);

    int time, flag = 0, posx = 0, posy = 0;
    cin>>time;

    int bx[time+5], by[time+5];
    for(int i=0; i<=time; i++)
    {
        cin>>bx[i]>>by[i];
        posx = min(posx, bx[i]);
        posy = min(posy, by[i]);
    }

    double vf, distance, fx[time+5], fy[time+5];
    cin>>fx[0]>>fy[0]>>vf;

    for(int i=0; i<=time; i++)
    {
        distance = sqrt((bx[i]-fx[i])*(bx[i]-fx[i]) + (by[i]-fy[i])*(by[i]-fy[i]));
        double sin_t = (by[i]-fy[i])/distance;
        double cos_t = (bx[i]-fx[i])/distance;

        fx[i+1] = fx[i] + vf*cos_t;
        fy[i+1] = fy[i] + vf*sin_t;

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

    int gd = DETECT,gm;
    initgraph(&gd, &gm,"");

    int fct = 5, inc = 5;
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
