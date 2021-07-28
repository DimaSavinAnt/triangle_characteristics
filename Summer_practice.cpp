﻿#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct triangle {
	double a, b, c, A, B, C, ha, hb, hc, ma, mb, mc, S, p;
	double ax, ay, bx, by, cx, cy;
}tr;

void error_message();
void calculation_other();
void output();
double two_side_one_angle_inside(double, double, double);
double two_angle_one_side(double, double, double);
void coordinates_work();

void main()
{
	setlocale(LC_ALL, "rus");

	/*При вводе стоит учитывать, что приоритетныс для программы является хар-ка треугольника по трем сторонам
и в случае неверного ввода углов, но верного ввода сторон - программа изменит значения углов в соответствии с
введенными сторонами*/
	int choice;
	printf("Введите данные, которые вы знаете, остальное заполните нулями\n");

	printf("Координаты вершин (0/1): ");
	scanf_s("%i", &choice);
	if (choice) {
		coordinates_work();
		exit(0);
	}

	printf("Сторона а: ");
	scanf_s("%lg", &tr.a);
	printf("Сторона b: ");
	scanf_s("%lg", &tr.b);
	printf("Сторона c: ");
	scanf_s("%lg", &tr.c);
	printf("Угол А: ");
	scanf_s("%lg", &tr.A);
	printf("Угол В: ");
	scanf_s("%lg", &tr.B);
	printf("Угол С: ");
	scanf_s("%lg", &tr.C);

	if (tr.a && tr.b && tr.c)

		if (tr.a + tr.b < tr.c || tr.b + tr.c < tr.a || tr.a + tr.c < tr.b)
		{
			error_message();
			exit(0);
		}

	if (tr.A && tr.B && tr.C)
		if (tr.A + tr.B + tr.C > 180) {
			error_message();
			exit(0);
		}

	//блок вычисления неизвестных элементов
	for (;;) {

		if (tr.b && tr.c && tr.a)
		{
			calculation_other();
			exit(0);
		}

		else if (tr.b && tr.c && tr.A)
			tr.a = two_side_one_angle_inside(tr.b, tr.c, tr.A);
		else if (tr.a && tr.b && tr.C)
			tr.c = two_side_one_angle_inside(tr.a, tr.b, tr.C);
		else if (tr.a && tr.c && tr.B)
			tr.b = two_side_one_angle_inside(tr.a, tr.c, tr.B);

		else if (tr.a && tr.C && tr.B)
			tr.c = two_angle_one_side(tr.a, tr.B, tr.C);
		else if (tr.b && tr.A && tr.C)
			tr.a = two_angle_one_side(tr.b, tr.C, tr.A);
		else if (tr.c && tr.A && tr.B)
			tr.b = two_angle_one_side(tr.c, tr.A, tr.B);
		else { error_message(); exit(0); }
	}
}

void coordinates_work()
{
	printf("Введите координаты X и Y вершины A через пробел: ");
	scanf_s("%lg %lg", &tr.ax, &tr.ay);
	printf("Введите координаты X и Y вершины B через пробел: ");
	scanf_s("%lg %lg", &tr.bx, &tr.by);
	printf("Введите координаты X и Y вершины C через пробел: ");
	scanf_s("%lg %lg", &tr.cx, &tr.cy);
	tr.c = fabs(sqrt(pow(tr.ax - tr.bx, 2) + pow(tr.ay - tr.by, 2)));
	tr.b = fabs(sqrt(pow(tr.ax - tr.cx, 2) + pow(tr.ay - tr.cy, 2)));
	tr.a = fabs(sqrt(pow(tr.bx - tr.cx, 2) + pow(tr.by - tr.cy, 2)));
	calculation_other();
}

//функция подсчета третьей стороны по 2-ум сторонам и углу между ними
double two_side_one_angle_inside(double b, double c, double A)
{
	double a = sqrt(pow(b, 2) + pow(c, 2) - (2 * b * c * cos(A * M_PI / 180)));
	return a;
}

//функция подсчета стороны по стороне и смежным с ней углами
double two_angle_one_side(double a, double B, double C)
{
	double A = 180 - (B + C);
	double c = a * sin(C * M_PI / 180) / sin(A * M_PI / 180);
	return c;
}

//опорная функция подсчета треугольника по трем сторонам
void calculation_other()
{
	tr.C = (180 / M_PI) * acos((pow(tr.a, 2.0) + pow(tr.b, 2.0) - pow(tr.c, 2.0)) / (2 * tr.a * tr.b));
	tr.B = (180 / M_PI) * acos((pow(tr.a, 2) + pow(tr.c, 2) - pow(tr.b, 2)) / (2 * tr.a * tr.c));
	tr.A = (180 / M_PI) * acos((pow(tr.b, 2) + pow(tr.c, 2) - pow(tr.a, 2)) / (2 * tr.b * tr.c));

	tr.ha = tr.b * sin(tr.C * M_PI / 180);
	tr.hb = tr.a * sin(tr.C * M_PI / 180);
	tr.hc = tr.a * sin(tr.B * M_PI / 180);
	tr.ma = sqrt(((pow(tr.b, 2) + pow(tr.c, 2)) / 2) - (pow(tr.a, 2) / 4));
	tr.mb = sqrt(((pow(tr.a, 2) + pow(tr.c, 2)) / 2) - (pow(tr.b, 2) / 4));
	tr.mc = sqrt(((pow(tr.a, 2) + pow(tr.b, 2)) / 2) - (pow(tr.c, 2) / 4));
	tr.p = (tr.a + tr.b + tr.c) / 2;
	tr.S = sqrt(tr.p * (tr.p - tr.a) * (tr.p - tr.b) * (tr.p - tr.c));
	output();
}

void output()
{
	system("cls");
	printf("Сторона а: %lg\nСторона b: %lg\nСторона с: %lg\n", tr.a, tr.b, tr.c);
	printf("Угол A: %lg\nУгол В: %lg\nУгол С: %lg\n", tr.A, tr.B, tr.C);
	printf("Высота ha: %lg\nВысота hb: %lg\nВысота hc: %lg\n", tr.ha, tr.hb, tr.hc);
	printf("Высота ma: %lg\nВысота mb: %lg\nВысота mc: %lg\n", tr.ma, tr.mb, tr.mc);
	printf("Полупериметр треугольника: %lg\nПлощадь треугольника: %lg\n\n", tr.p, tr.S);
	if (tr.ax || tr.bx || tr.cx)
	{
		printf("Координаты точки A: %lg %lg\n", tr.ax, tr.ay);
		printf("Координаты точки B: %lg %lg\n", tr.bx, tr.by);
		printf("Координаты точки C: %lg %lg\n\n", tr.cx, tr.cy, tr.cx, tr.cy);
	}
}

void error_message()
{
	printf("Вы ввели недостаточно данных или они были не верны\n\n");
}
