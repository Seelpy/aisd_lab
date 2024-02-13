/*
 * Задание:
 * 2.11. Бильярд 1 (10)
 * Бильярдный стол расчерчен на квадратные клетки и имеет размеры M×N клеток. В углах стола находятся четыре лузы для шаров. В центрах некоторых клеток находятся шары. По определенному шару, называемому битком, наносится удар, в результате которого шар может катиться в одном из четырех направлений вдоль диагоналей клетки. Если этот шар достигает края стола, то отражается и продолжает движение, а если попадает в угол стола, то сваливается в лузу и игра заканчивается. Если биток не встречает на своем пути других шаров и не сваливается в лузу, то он проходит ровно K клеток, не считая начальной, но включая конечную клетку либо лузу. Если же биток достигает клетки с другим шаром, то встреченный шар удаляется, а биток занимает его место и используется для последующих ударов. По заданному расположению шаров найти наименьшее количество ударов, необходимое для снятия всех шаров, включая биток.
 * Ввод из файла INPUT.TXT. Первая  строка  содержит целые числа  M, N  и K  (1 ≤  M, N ≤ 15;  1 ≤ K ≤ 10) через пробел. Каждая  i-я  строка  из  следующих M  строк  содержит  N  символов Cij  (1 ≤ j ≤ N). Свободные клетки стола помечаются символами ‘.’, клетки с неподвижными шарами символами ‘#’, а клетка с битком - символом ‘&’. Общее количество шаров, включая биток, может быть от 1 до 15.
 * Вывод в файл OUTPUT.TXT. В единственной строке выводится минимальное количество ударов, необходимое для снятия всех шаров. Если это невозможно, вывести No.
 *
 * ФИО: Веселов Максим Геннадьевич
 * Группа: ПС-21
 * Версия c++: 17
 */


#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "assert.h"

using namespace std;

#define ErrCountCMDArgs "count args error"
#define ErrOpenFile "open file error"

typedef pair<int, int> Coord;
typedef pair<int, int> Size;
typedef int Power;

enum Direction {
    LEFTUP,
    LEFTDOWN,
    RIGHTUP,
    RIGHTDOWN
};

enum CoordDirection {
    PLUS,
    MINUS,
};

bool isOnDiagonal(Size size, Coord c1, Coord c2) {
    return abs(c1.first - c2.first) == abs(c1.second - c2.second) ||
            abs(c1.first + c2.first) == abs(c1.second - c2.second) ||
            abs(c1.first - c2.first) == abs(c1.second + c2.second) ||
            abs(c1.first + c2.first) == abs(c1.second + c2.second) ||
            abs(c1.first - ( 2*size.first -  c2.first - 1)) == abs(c1.second - c2.second) ||
            abs(c1.first - c2.first) == abs(c1.second - (2*size.second  - c2.second - 1)) ||
            c1.first == 0 && c2.first == 0 && abs(c1.second - c2.second) == 1 ||
            c1.second == 0 && c2.second == 0 && abs(c1.first - c2.first) == 1;
}

int pong(int c, int s) {
    if (c > 0 && c <= s) {
        return c;
    }
    if (c <= 0 ) {
        c--;
    }
    int cTmp = abs(c % (2 * s));
    if (cTmp > 0 && cTmp <= s) {
        return cTmp;
    }
    int cTmp2 = cTmp % s;
    if (c > 0) {
        return s + 1 - cTmp2;
    } else {
        return cTmp2;
    }
}

Coord module(Size size, Coord coord) {
    return Coord{
            pong(coord.first, size.first),
            pong(coord.second, size.second)
    };
}

Coord newCoord(Size size, Coord coord, Power power, Direction direct) {
    Coord newCoord;
    switch (direct) {
        case LEFTUP:
            newCoord = Coord{coord.first - power, coord.second - power};
            break;
        case LEFTDOWN:
            newCoord =  Coord{coord.first + power, coord.second - power};
            break;
        case RIGHTUP:
            newCoord =  Coord{coord.first - power, coord.second + power};
            break;
        case RIGHTDOWN:
            newCoord =  Coord{coord.first + power, coord.second + power};
            break;
    }
    return module(size, newCoord);
}

int countStrokes(Size size, Power power, Coord mainBall, vector<Coord> balls) {
    queue<Coord> q;
    q.push(mainBall);
    const int y = size.first;
    const int x = size.second;

    bool visited[size.first  + 1][size.second + 1];
    int countBalls = balls.size();
    bool visitedBalls[balls.size()];
    int dist[size.first + 1][size.second + 1];
    visited[mainBall.second][mainBall.second] = true;
    dist[mainBall.second][mainBall.second] = 1;

    while (!q.empty()) {
        auto coord = q.front();
        q.pop();
        for (int visitedBall= 0; visitedBall < countBalls; visitedBall++) {
            if (!visitedBalls[visitedBall]) {
                Coord ball = balls.at(visitedBall);
                if (isOnDiagonal(size, coord, ball)) {
                    visitedBalls[visitedBall] = true;
                    visited[ball.first][ball.second] = true;
                    q.push(ball);
                }
            }
        }
        Coord newCoords[4] = { newCoord(size, coord, power, LEFTUP),
                               newCoord(size, coord, power, LEFTDOWN),
                               newCoord(size, coord, power, RIGHTUP),
                               newCoord(size, coord, power, RIGHTDOWN)};
        for (auto nCord: newCoords) {
            if (visited[nCord.first][nCord.second]) {
                visited[nCord.first][nCord.second] = true;
                q.push(nCord);
            }
        }

    }
    return 0;
}

void run(std::ifstream *in, std::ostream *out) {
    Size size;
    Power power;
    const char MAIN_BALL = '&';
    const char OTHER_BALL = '#';
    *in >> size.first >> size.second >> power;
    Coord mainBall;
    vector<Coord> balls;
    char ch;
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            *in >> ch;
            if (ch == OTHER_BALL) {
                balls.emplace_back(i + 1, j + 1);
            } else if (ch == MAIN_BALL) {
                mainBall = Coord{i + 1, j + 1};
            }
        }
    }

    int count = countStrokes(size, power, mainBall, balls);
    if (count < 0) {
        *out << "No";
    } else {
        *out << count;
    }
    *out << endl;
    return;
}

void testPong();

void testDiagonile();

void testNewCoord();

int main(int argc, char **argv) {
    if (argc < 2) // no arguments were passed
    {
        cout << ErrCountCMDArgs << endl;
        return -1;
    }

    string inFileName = argv[1];
    string outFileName = argv[2];

    ifstream in(inFileName);
    ofstream out(outFileName);

    if (!in.is_open() || !out.is_open())
    {
        cout << ErrOpenFile << endl;
        return -1;
    }
    testDiagonile();
    testPong();
    testNewCoord();
    run(&in, &out);
    return 0;
}

void testDiagonile() {
    cout << "Test Diagonile" <<endl;
    {
        cout<<"Test 1";
        Size size{4, 4};
        Coord c1{1, 1};
        Coord c2{2, 2};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 2";
        Size size{4, 4};
        Coord c1{4, 4};
        Coord c2{1, 1};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 3";
        Size size{4, 4};
        Coord c1{0, 1};
        Coord c2{1, 2};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 4";
        Size size{4, 4};
        Coord c1{0, 1};
        Coord c2{0, 2};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 5";
        Size size{4, 4};
        Coord c1{3, 1};
        Coord c2{3, 2};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 6";
        Size size{4, 4};
        Coord c1{2, 3};
        Coord c2{1, 3};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 7";
        Size size{4, 4};
        Coord c1{0, 1};
        Coord c2{0, 2};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 8";
        Size size{4, 4};
        Coord c1{1, 1};
        Coord c2{1, 2};
        assert(isOnDiagonal(size, c1, c2) == false);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 9";
        Size size{4, 4};
        Coord c1{0, 0};
        Coord c2{0, 2};
        assert(isOnDiagonal(size, c1, c2) == false);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 10";
        Size size{5, 5};
        Coord c1{0, 0};
        Coord c2{1, 2};
        assert(isOnDiagonal(size, c1, c2) == false);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 11";
        Size size{5, 5};
        Coord c1{1, 2};
        Coord c2{0, 0};
        assert(isOnDiagonal(size, c1, c2) == false);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 12";
        Size size{4, 7};
        Coord c1{2, 1};
        Coord c2{1, 4};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    {
        cout<<"Test 13";
        Size size{4, 7};
        Coord c1{0, 0};
        Coord c2{1, 6};
        assert(isOnDiagonal(size, c1, c2));
        cout<<" success" << endl;
    }
    cout <<endl;
}

void testPong() {
    cout << "Test Pong" << endl;
    {
        cout<<"Test 1";
        int c1 = -1;
        int s = 9;
        int c2 = pong(c1, s);
        cout << ":" << c2<<":";
        assert(c2 == 2);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 2";
        int c1 = 5;
        int s = 9;
        int c2 = pong(c1, s);
        cout << ":" << c2;
        assert(c2 == 5);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 3";
        int c1 = 10;
        int s = 9;
        int c2 = pong(c1, s);
        cout << ":" << c2;
        assert(c2 == 9);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 3";
        int c1 = 21;
        int s = 10;
        int c2 = pong(c1, s);
        cout << ":" << c2;
        assert(c2 == 1);
        cout<<" success" << endl;
    }
    cout <<endl;
}

void testNewCoord() {
    cout << "Test Coord" <<endl;
    {
        cout<<"Test 1";
        Size s{4, 7};
        Coord c1{1, 2};
        Power p = 2;
        Direction d = LEFTUP;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 2);
        assert(c2.second == 1);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 2";
        Size s{4, 7};
        Coord c1{3, 6};
        Power p = 5;
        Direction d = LEFTUP;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 3);
        assert(c2.second == 1);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 3";
        Size s{4, 7};
        Coord c1{3, 6};
        Power p = 4;
        Direction d = LEFTDOWN;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 2);
        assert(c2.second == 2);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 4";
        Size s{4, 7};
        Coord c1{3, 6};
        Power p = 1;
        Direction d = RIGHTDOWN;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 4);
        assert(c2.second == 7);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 5";
        Size s{4, 7};
        Coord c1{2, 4};
        Power p = 3;
        Direction d = RIGHTDOWN;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 4);
        assert(c2.second == 7);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 6";
        Size s{4, 7};
        Coord c1{1, 3};
        Power p = 10;
        Direction d = RIGHTDOWN;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 3);
        assert(c2.second == 2);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 7";
        Size s{4, 7};
        Coord c1{2, 4};
        Power p = 5;
        Direction d = RIGHTDOWN;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 2);
        assert(c2.second == 6);
        cout<<" success" << endl;
    }
    {
        cout<<"Test 8";
        Size s{4, 7};
        Coord c1{1, 2};
        Power p = 2;
        Direction d = LEFTUP;
        Coord c2 = newCoord(s, c1, p, d);
        cout << ":" << c2.first << c2.second;
        assert(c2.first == 2);
        assert(c2.second == 1);
        cout<<" success" << endl;
    }
    cout <<endl;
}