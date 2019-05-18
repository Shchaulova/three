#include <iostream>

#include "GLBall.h"

#include "NBodyScene.h"

using namespace std;

#include <vector>

#include <cmath>


// Ваш класс для описания тела.

// Унаследован от GLBall, реализует его интерфейс с методами getX / getY / getR.

// (Для точечных тел внутри getR можете сделать возврат константы.)

class SampleBall : public GLBall {

protected:

    double vx;

    double vy;

    double x;

    double y;

    double r;

    vector<SampleBall> v;

    int i = 0;


public:
    // Конструктор *ваш* - что нужно, то в нём и получаете.

    // Копировать этот конструктор *не* надо.
    double ax = 0, ay = 0, m = 0;

    SampleBall(double x, double y, double r, double vx, double vy)

            : x(x), y(y), r(r), vx(vx), vy(vy) {}


    // Ваши методы, никак не связанные с GLBall

    void move(double dt) {

        x += vx * dt;

        y += vy * dt;

    }
    void push_mas (double m){
        m = m;
    }

    void add(int k) {

       // v.push_back (SampleBall k);

        i = i + 1;

    }

    void show() {

        int d;

        for (d = 0; d < i; d++) {

            cout << v[d].x;

            cout << " ";

            cout << v[d].y;

            cout << "    ";

        }

    }

    int number() {

        cout << i;

        return i;

    }


    void count() {

        int q1;
        long double kx, ky, sx, sy, dx, dy;
        int q2;

        for (q2 = 0; q2 < i; q2++) {

            v[q2].ax = 0;

            v[q2].ay = 0;

            for (q1 = 0; q1 < i; q1++) {

                if (q1 != q2) {
                    kx = sqrt((v[q1].x - v[q2].x) * (v[q1].x - v[q2].x) + (v[q1].y - v[q2].y) * (v[q1].y - v[q2].y));
                    ky = sqrt((v[q1].x - v[q2].x) * (v[q1].x - v[q2].x) + (v[q1].y - v[q2].y) * (v[q1].y - v[q2].y));
                    sx = ((v[q1].x - v[q2].x) * (v[q1].x - v[q2].x) + (v[q1].y - v[q2].y) * (v[q1].y - v[q2].y));
                    sy = ((v[q1].x - v[q2].x) * (v[q1].x - v[q2].x) + (v[q1].y - v[q2].y) * (v[q1].y - v[q2].y));
                    dx = 6.67408 * v[q1].m * (v[q1].x - v[q2].x);
                    dy = 6.67408 * v[q1].m * (v[q1].y - v[q2].y);
                    v[q2].ax += dx / 100000 / sx / kx;
                    v[q2].ay += dy / 100000 / sy / ky;

                }

            }

        }

    }


    void delay(double t) {

        while (t > 0) {

            int p;

            t = t - 0.01;

            count();

            for (p = 0; p < i; p++) {

                v[p].x += v[p].vx * 0.01;

                v[p].y += v[p].vy * 0.01;

                v[p].vx += v[p].ax * 0.01;

                v[p].vy += v[p].ay * 0.01;

            }


        }


        // Реализация методов интерфейса на базе *ваших* переменных.

        // Переписывать всю свою реализацию под эти имена *не* надо.

        double getX() const override {

                return x;

        }

        double getY() const override{

                return y;

        }

        double getR() const override{

                return r;

        }

    }
};


// Ваш класс сцены. В него де-факто превратится текущий main или его аналог.

// Унаследован от NBodyScene, реализует интерфейс с методами getNumberOfBodies / getBody / doTimeStep.

    class SampleScene : public NBodyScene {

    protected:

        std::vector<SampleBall> bodies;


    public:

        // Реализация методов интерфейса на базе *ваших* переменных



        unsigned int getNumberOfBodies() const override {

            return bodies.size();

        }

        const GLBall &getBody(unsigned int number) const override {

            return bodies.at(number);

        }


        void doTimeStep() override {

            for (SampleBall &b : bodies)

                b.move(0.1);

        }



        // Далее ещё куча ваших методов, никак не связанных с NBodyScene



        void initScene() {

            bodies.push_back(SampleBall(0, 0, 10, 1, 0));

            bodies.push_back(SampleBall(15, 15, 1, 0, 1));

        }

        void show()
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

        int number()
        {
            cout<< i;
            return i;
        }

        void count()
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

        void delay (double t) {

            while (t > 0) {
                int c;
                t = t - 0.01;
                count();
                for (c = 0; c < i; c++) {
                    v[c].x += v[c].velocityX * 0.01;
                    v[c].y += v[c].velocityY * 0.01;
                    v[c].velocityX += v[c].accelerationX * 0.01;
                    v[c].velocityY += v[c].accelerationY * 0.01;
                }

            }
        }





    };

// Функция, которая готовит всю сцену и возвращает готовый объект.

// Если нужно читать из файла и консоли, вызывать кучу методов - это здесь.

    NBodyScene *getScene() {

        SampleScene *s = new SampleScene();

        s->initScene();

        return s;

    }

