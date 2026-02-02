#include <bits/stdc++.h>
using namespace std;

/* ---------- Euler Step ---------- */
void euler_step(double &S, double &I, double &R,
                double beta, double gamma, double N, double h)
{
    double dS = -beta * S * I / N;
    double dI = beta * S * I / N - gamma * I;
    double dR = gamma * I;

    S += h * dS;
    I += h * dI;
    R += h * dR;
}

/* ---------- RK4 Step ---------- */
void rk4_step(double &S, double &I, double &R,
              double beta, double gamma, double N, double h)
{
    auto fS = [&](double s, double i){ return -beta * s * i / N; };
    auto fI = [&](double s, double i){ return beta * s * i / N - gamma * i; };
    auto fR = [&](double i){ return gamma * i; };

    double k1S = h * fS(S, I);
    double k1I = h * fI(S, I);
    double k1R = h * fR(I);

    double k2S = h * fS(S + k1S/2, I + k1I/2);
    double k2I = h * fI(S + k1S/2, I + k1I/2);
    double k2R = h * fR(I + k1I/2);

    double k3S = h * fS(S + k2S/2, I + k2I/2);
    double k3I = h * fI(S + k2S/2, I + k2I/2);
    double k3R = h * fR(I + k2I/2);

    double k4S = h * fS(S + k3S, I + k3I);
    double k4I = h * fI(S + k3S, I + k3I);
    double k4R = h * fR(I + k3I);

    S += (k1S + 2*k2S + 2*k3S + k4S) / 6;
    I += (k1I + 2*k2I + 2*k3I + k4I) / 6;
    R += (k1R + 2*k2R + 2*k3R + k4R) / 6;
}

int main()
{
    cout << fixed << setprecision(4);

    /* ---------- 1. Infected on Day 10 ---------- */
    {
        double S=999, I=1, R=0, N=1000, beta=0.5, gamma=0.1, h=0.1;
        for(double t=0;t<10;t+=h) euler_step(S,I,R,beta,gamma,N,h);
        cout<<"1) Infected at Day 10 = "<<I<<"\n\n";
    }

    /* ---------- 2. Peak Infection ---------- */
    {
        double S=9900, I=100, R=0, N=10000, beta=0.6, gamma=0.2, h=0.05;
        double maxI = I, peakT = 0;
        double t=0;
        while(t<=50){
            if(I>maxI){ maxI=I; peakT=t; }
            euler_step(S,I,R,beta,gamma,N,h);
            t+=h;
        }
        cout<<"2) Peak Infection at Day "<<peakT<<" , Max I = "<<maxI<<"\n\n";
    }

    /* ---------- 3. Sensitivity Analysis ---------- */
    double S1, S2;
    {
        double S=490, I=10, R=0, N=500, beta=0.4, gamma=0.1;
        for(int i=0;i<20;i++) euler_step(S,I,R,beta,gamma,N,1.0);
        S1 = S;
    }
    {
        double S=490, I=10, R=0, N=500, beta=0.4, gamma=0.1;
        for(double t=0;t<20;t+=0.01) euler_step(S,I,R,beta,gamma,N,0.01);
        S2 = S;
    }
    cout<<"3) |S(h=1) - S(h=0.01)| = "<<fabs(S1-S2)<<"\n\n";

    /* ---------- 4. Threshold Phenomenon ---------- */
    {
        double S=1990,I=10,R=0,N=2000,gamma=0.3,h=0.1;
        double betaA=0.2,betaB=0.4;
        double IA=I, IB=I;

        for(double t=0;t<30;t+=h) euler_step(S,IA,R,betaA,gamma,N,h);
        S=1990; R=0;
        for(double t=0;t<30;t+=h) euler_step(S,IB,R,betaB,gamma,N,h);

        cout<<"4) Epidemic occurs in Scenario "
            <<(IB>10 ? "B (Beta)\n\n" : "A (Alpha)\n\n");
    }

    /* ---------- 5. Initial Infection Slope ---------- */
    {
        double S=140,I=10,R=850,N=1000,beta=0.5,gamma=0.1,h=0.1;
        double I0 = I;
        euler_step(S,I,R,beta,gamma,N,h);
        cout<<"5) Initial slope = "<<(I-I0)/h<<"\n\n";
    }

    /* ---------- 6. Total Epidemic Size ---------- */
    {
        double S=99990,I=10,R=0,N=100000,beta=0.4,gamma=0.15,h=0.1;
        for(double t=0;t<200;t+=h) euler_step(S,I,R,beta,gamma,N,h);
        cout<<"6) Total Recovered = "<<R<<"\n\n";
    }

    /* ---------- 7. Lockdown ---------- */
    {
        double S=990,I=10,R=0,N=1000,gamma=0.1,h=0.1;
        for(double t=0;t<40;t+=h){
            double beta = (t<20)?0.5:0.15;
            euler_step(S,I,R,beta,gamma,N,h);
        }
        cout<<"7) Infected at Day 40 = "<<I<<"\n\n";
    }

    /* ---------- 8. Hospital Capacity ---------- */
    {
        double S=4995,I=5,R=0,N=5000,beta=0.5,gamma=0.1,h=0.1;
        double maxI = I;
        for(double t=0;t<100;t+=h){
            euler_step(S,I,R,beta,gamma,N,h);
            maxI = max(maxI,I);
        }
        cout<<"8) Max Infected = "<<maxI
            <<(maxI>1500 ? " (Capacity Breached)\n\n" : " (Safe)\n\n");
    }

    /* ---------- 9. Slow Burn ---------- */
    {
        double S=99,I=1,R=0,N=100,beta=0.15,gamma=0.1,h=0.5;
        for(double t=0;t<365;t+=h) euler_step(S,I,R,beta,gamma,N,h);
        cout<<"9) Recovered after 1 year = "<<R<<"\n\n";
    }

    /* ---------- 10. Euler vs RK4 ---------- */
    {
        double S1=900,I1=100,R1=0;
        double S2=900,I2=100,R2=0;
        double N=1000,beta=1.0,gamma=0.5,h=0.5;

        for(double t=0;t<2;t+=h){
            euler_step(S1,I1,R1,beta,gamma,N,h);
            rk4_step(S2,I2,R2,beta,gamma,N,h);
        }
        cout<<"10) Euler I(2) = "<<I1<<"\n";
        cout<<"    RK4   I(2) = "<<I2<<"\n";
    }

    return 0;
}
