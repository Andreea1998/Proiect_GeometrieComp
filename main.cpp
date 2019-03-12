#include<iostream>
using namespace std;

struct Point{
    int x, y;
};

inline float
isLeft( Point P0, Point P1, Point P2 )
{
    return (P1.x - P0.x)*(P2.y - P0.y) - (P2.x - P0.x)*(P1.y - P0.y);
}
//simpleHull_2D(): Algoritmul lui Melkman pentru un poligon simplu 2D
//    Input:  P[] = vector ce contine punctele poligonului
//            n   = numarul de puncte din V[]
//    Output: CH[] = vectorul ce contine acoperirea convexa a nodurilor
//    Return: h   = numarul de puncte din CH[]
int simpleHull_2D( Point* P, int n, Point* H )
{
    //initializare lista dublu inlantuita de jos in sus astfel incat primele 3 noduri ale lui P[] sunt un triunghi CCW
    Point* D = new Point[2*n+1];
    int bot = n-2, top = bot+3;    //indicii initiali bottom si top ai listei
    D[bot] = D[top] = P[2];        //al treilea nod este si la inceput si la sfarsit
    if (isLeft(P[0], P[1], P[2]) > 0) {
        D[bot+1] = P[0];
        D[bot+2] = P[1];           // nodurile CCW sunt: 2,0,1,2
    }
    else {
        D[bot+1] = P[1];
        D[bot+2] = P[0];           // nodurile CCW sunt: 2,1,0,2
    }
    for (int i=3; i < n; i++) {   // proceseaza restul nodurilor
                                //testeaza daca nodul urmator apartine acoperirii convexe
        if ((isLeft(D[bot], D[bot+1], P[i]) > 0) &&
            (isLeft(D[top-1], D[top], P[i]) > 0) )
                 continue;         //trece peste un nod interior

        //prin incrementare adaugam un nod exterior la lista acoperirii convexe
        //cel mai din dreapta de la sfarsitul listei
        while (isLeft(D[bot], D[bot+1], P[i]) <= 0)
            ++bot;                 //scoatere final al listei
        D[--bot] = P[i];           //adaugare P[i] la sfarsitul listei

        //cel mai din stanga de la inceputul listei
        while (isLeft(D[top-1], D[top], P[i]) <= 0)
            --top;                 //scoatere inceput al listei
        D[++top] = P[i];           //adaugare P[i] la inceputul listei
    }

    //transcriere lista D[] la outputul vectorului acoperirii convexe CH[]
    int h;        // numarare nodurile acoperirii convexe
    for (h=0; h <= (top-bot); h++)
        H[h] = D[bot + h];

    delete D;
    return h-1;
}

int main(){
    Point points[] = {{0,0},{2,2}, {4,0}, {2,4}};
    int n = sizeof(points)/sizeof(points[0]);
    Point ch[n+1];
    int hull=simpleHull_2D(points, n, ch);
    for (int i=0; i < hull; i++)
            cout<<ch[i].x<<" "<<ch[i].y<<endl;
return 0;
}
