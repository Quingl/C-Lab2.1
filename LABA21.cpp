//Построить такие два треугольника с вершинами в  заданном множестве  точек  на плоскости,
//из которых один лежал бы строго внутри другого.



#include <fstream>
#include <iostream>
#include <vector>
#include "C:\Users\11\source\repos\glut\glut.h"

using namespace std;

void display(void);								//вызывается при перерисовке экрана
void SetupRC(void);									//начальные установки
void ChangeSize(int, int);							//вызывается при изменении размеров окна


float x1, y11, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
GLfloat windowWidth = 500;
GLfloat windowHeight = 500;

int nmax; //макс.кол.точек, можно увеличить

const double t = 0.001; //точнсть сравнения площадей

struct point //сделаем свой тип, координаты типа longint
			 //возьмен точки в экранных координатах, при умножении вылезут за тип integer
{
	float x, y;
};
vector<point> points;

// определение площади треугольников по координатам вершин
// через скалярные произведения
double Plosh(point a, point b, point c)
{
	return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2;
}
bool Prin(point a, point b, point c, point d)
{
	double s, s1, s2, s3;
	bool f;
	s = Plosh(a, b, c); //площадь данного треугольника
	if (s < t)
		f = false;//если не треугольник - площади нет
	else //иначе вычисляем площади трех "маленьких" треугольников
		//и сравниваем их сумму с площадью большого		
	{
		s1 = Plosh(a, b, d); // 1 маленький
		s2 = Plosh(a, c, d); // 2
		s3 = Plosh(b, c, d); // 3
		f = abs(s1 + s2 + s3 - s) < t; //если площади равны с заданной точностью		
	}
	return f;
}

point SolPOne = point{ 500,500 }, SolPTwo = point{ 500,500 };

void DrawCircle(float x, float y, float R, int FillFlag) {//Координаты, радиус, флаг переключения между кругом и окружностью
	int N = 360;
	glBegin(FillFlag ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
	for (int i = 1; i <= N; i++) {
		glVertex2f(x + R * cos(2 * 3.14 / N * i), y + R * sin(2 * 3.14 / N * i));
	}
	glEnd();
}
void DrawLine(float _X1, float _Y1, float _X2, float _Y2) {
	glBegin(GL_LINES);
	glVertex2f(_X1, _Y1);
	glVertex2f(_X2, _Y2);

	glEnd();
}


void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'

	if (key == ESCAPE)
		exit(0);
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("First window!");
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(Keyboard);
	ifstream fin;
	fin.open("input6.txt");
	fin >> nmax;
	if (nmax < 6)
	{
		cout << "задано слишком мало точек";
		return 0;
	}
	for (int i = 0; i < nmax; i++)
	{
		float x, y;
		fin >> x >> y;
		points.push_back(point{ x,y });
	}
	
	int i = 0, j = 0, k = 0, p = 0, q = 0, r = 0;

	bool f;
	f = false;
	while (i <= nmax - 3 && !f)
	{
		j = i + 1;
		while (j <= nmax - 2 && !f)
		{
			k = j + 1;
			while (k <= nmax - 1 && !f)
			{
				p = k + 1;//&&&&&&&&&&&&&&&&&&&&&&&&&
				while (p <= nmax - 3 && !f)
				{
					q = p + 1;
					while (q <= nmax - 2 && !f)
					{
						r = q + 1;
						while (r <= nmax -1 && !f)
						{
							if ((!(p == i || p == j || p == k) && !(q == i || q == j || q == k) && !(r == i || r == j || r == k)) // вторая тройка точек не совпадает с первой
								&& ((Prin(points[i], points[j], points[k], points[p]) && Prin(points[i], points[j], points[k], points[q])
									&& Prin(points[i], points[j], points[k], points[r])) // и вторая тройка точек внутри первой
									|| (Prin(points[p], points[q], points[r], points[i]) && Prin(points[p], points[q], points[r], points[j])
										&& Prin(points[p], points[q], points[r], points[k])))
								)
							{
								f = true;
								x1 = points[i].x; y11 = points[i].y;								
								x2 = points[j].x; y2 = points[j].y;
								x3 = points[k].x; y3 = points[k].y;
								x4 = points[p].x; y4 = points[p].y;
								x5 = points[q].x; y5 = points[q].y;
								x6 = points[r].x; y6 = points[r].y;

							}
							if (!f)r++;
						}
						if (!f)q++;
					}
					if (!f)p++;
				}
				if (!f)k++;
			}
			if (!f)j++;
		}
		if (!f)i++;
	}
	if (!f)
	{
		cout << "Треугольников нет.";
		SetupRC();
		glutMainLoop();
	}
	else
		cout << "Треугольники построены.";

		SetupRC();
	glutMainLoop();

}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < nmax; i++) { //Рисуем точки
		DrawCircle(points[i].x, points[i].y, 1.5, 1);
	}
	glColor3f(0.0f, 1.0f, 0.0f);
	DrawLine(x1, y11, x2, y2);
	DrawLine(x2, y2, x3, y3);
	DrawLine(x1, y11, x3, y3);
	glColor3f(0.0f, 0.0f, 1.0f);
	DrawLine(x4, y4, x5, y5);
	DrawLine(x5, y5, x6, y6);
	DrawLine(x4, y4, x6, y6);


	glutSwapBuffers();
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ChangeSize(int width, int height)
{
	GLfloat aspectRatio;

	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)width / (GLfloat)height;
	if (width <= height)
	{
		windowWidth = 200;
		windowHeight = 200 / aspectRatio;
		glOrtho(-200.0, 200.0,
			-windowHeight, windowHeight, 1.0, -1.0);
	}
	else
	{
		windowWidth = 200 * aspectRatio;
		windowHeight = 200;
		glOrtho(-windowWidth, windowWidth,
			-200.0, 200.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


