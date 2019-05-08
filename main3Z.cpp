#include <iostream>
using namespace std;
#include <vector>
#include <cmath>

class Particle
{
	friend class System;

	private:
        long double mas;
		long double x;
		long double y;
		long double velocityX;
		long double velocityY;
		long double accelerationX;
		long double accelerationY;

    public:
        Particle(double x, double y, double velocityX, double velocityY, double mas );
       ~Particle();
};

Particle::Particle(double x, double y, double velocityX, double velocityY, double mas):
    x(x),
    y(y),
    velocityX(velocityX),
    velocityY(velocityY),
    mas(mas),
    accelerationX(0.0),
    accelerationY(0.0)
    {}

Particle::~Particle()
{}

class System
{
	friend class Particle;
	private:
		vector<Particle> v;
		int i=0;
	public:
		System();
		~System();
		void add (Particle k);
		void show();
		void count();
		void delay (double t);
		int number();
};

System::System()
{}

System:: ~System()
{}

void System:: add (Particle k)
{
    v.push_back(k);
    i=i+1;
}

void System:: show()
{
    int d;
    for (d=0; d<i; d++)
    {
        cout << v[d].x;
        cout<< " ";
        cout << v[d].y;
        cout<< "    ";
    }
}

int System::number()
{
    cout<< i;
    return i;
}

void System:: count()
{
    int d;
    int c;
    for (d=0; d<i; d++)
    {
        v[d].accelerationX=0;
        v[d].accelerationY=0;
        for (c=0; c<i; c++)
        {
            if (c!=d)
            {
                v[d].accelerationX+=6.67408*v[c].mas*(v[c].x-v[d].x)/100000/((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y))/sqrt(((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y)));
                v[d].accelerationY+=6.67408*v[c].mas*(v[c].y-v[d].y)/100000/((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y))/sqrt(((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y)));
            }
        }
    }
}

void System:: delay (double t)
{
    while (t>0)
    {
        int c;
        t=t-0.01;
        count();
        for (c=0; c<i; c++)
        {
            v[c].x+=v[c].velocityX*0.01;
            v[c].y+=v[c].velocityY*0.01;
            v[c].velocityX+=v[c].accelerationX*0.01;
            v[c].velocityY+=v[c].accelerationY*0.01;
        }

    }
}


int main()
{
	System w;
	Particle t1(1, 3.5, 12, 194, 1);
	Particle t2(2, 1000, 4647, 0, 7);
	Particle t3(956, 0, 3, 45, 9);
	Particle t4(56, 567, 23, 3684, 1);
	w.add (t1);
	w.add(t2);
	w.add (t3);
	w.add(t4);
	w.delay(5);
	w.show();
	return 0;
}