
/********************* Cubic Spline Interpolation **********************/
#include<math.h>

#include <QDebug>

using namespace std;

int spline()
{

    int n,i,j,k;
    float h[10],a,b,c,d,sum;
    float s[10]={0},x[10],F[10],f[10],p,m[10][10]={0},temp;
    n = 10;
    x[0] = f[0] = 0.0;
    x[1] = 1.0; f[1] = 1.0;
    x[2] = 2.0; f[2] = 2.0;
    x[3] = 3.0; f[3] = 3.0;
    x[4] = 4.0; f[4] = 4.0;
    x[5] = 5.0; f[5] = 5.0;
    x[6] = 6.0; f[6] = 4.0;
    x[7] = 7.0; f[7] = 3.0;
    x[8] = 8.0; f[8] = 2.0;
    x[9] = 9.0; f[9] = 1.0;

    for(i=n-1;i>0;i--)
    {
        F[i]=(f[i]-f[i-1])/(x[i]-x[i-1]);
        h[i-1]=x[i]-x[i-1];
    }

    //*********** formation of h, s , f matrix **************//
    for(i=1;i<n-1;i++)
    {
    m[i][i]=2*(h[i-1]+h[i]);
    if(i!=1)
    {
        m[i][i-1]=h[i-1];
        m[i-1][i]=h[i-1];
    }
    m[i][n-1]=6*(F[i+1]-F[i]);
    }

    //***********  forward elimination **************//

    for(i=1;i<n-2;i++)
    {
        temp=(m[i+1][i]/m[i][i]);
        for(j=1;j<=n-1;j++)
            m[i+1][j]-=temp*m[i][j];
    }

    //*********** back ward substitution *********//
    for(i=n-2;i>0;i--)
    {
        sum=0;
        for(j=i;j<=n-2;j++)
            sum+=m[i][j]*s[j];
        s[i]=(m[i][n-1]-sum)/m[i][i];
    }
    for (float p = 0.0f; i < 9.0f; i += 0.5f)
    {

        for(i=0;i<n-1;i++)
            if(x[i]<=p&&p<=x[i+1])
            {
                a=(s[i+1]-s[i])/(6*h[i]);
                b=s[i]/2;
                c=(f[i+1]-f[i])/h[i]-(2*h[i]*s[i]+s[i+1]*h[i])/6;
                d=f[i];
                sum=a*pow((p-x[i]),3)+b*pow((p-x[i]),2)+c*(p-x[i])+d;
            }
        qDebug()<<"coefficients of sub interval : \n"<<a<<"\n"<<b<<"\n"<<c<<"\n"<<d;
        qDebug()<<"\nFuntional value is: "<<"\n"<<sum;
    }

    return 0;
}
