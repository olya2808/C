
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	int x, y,i,ph;//описание целых переменных
	double z, a, b,numerator,denominator,sq;//описание дробных переменных
	ph = 1;//присвоим переменной ph значение 1, т.к. единица нейтральна при умножении
	printf("variant #12\n");//выводим номер варианта
	printf("insert integer x:\n");//просим ввести значение х
	scanf_s("%d", &x);//вводим значение х
	printf("insert integer y:\n");//просим ввести значение у
	scanf_s("%d", &y);//вводим значение у
	printf("insert real z:\n");//просим ввести значение z
	scanf_s("%lf",&z);//вводим значение z
	printf("x=%10d\ny=%10d\nz=%10.5e\n", x, y, z);//выводим значения x,y,z
	numerator = x * x*x + sin(pow(y, 1.0 / 3));//вычисляем числитель дроби для а
	if((2*y+1>0)&&(2*y+1!=1))//с помощью if проверяем существование дроби, если она существует, то мы ее вычисляем
	{
		denominator = log2f(2 * y + 1);//вычисляем знаменатель дроби для а
		a = sqrt(fabs(numerator / denominator));//вычисляем модуль, а затем квадратный корень из дроби для а
		printf("a=%10.4lf\n", a);//выводим а
	}
	else//если дробь не существует, то говорим, что у а нет корей
	{
		printf("a=impossible to find\n");// говорим, что у а нет корей
	}
	for (i = 1; i <= 5; i++)//с помощью цикла вычисляем 5! для знаменателя 1 слагаемого для b
	{
		ph *= i;//присваиваем переменной ее значение, умноженное на ее значение плюс 1
	}
	sq = sqrt(fabs(2 * x));//вычисляем второе слагаемое для b
	b = (x*x*x) / ph + sq;//вычисляем b
	printf("b=%10.4lf\n",b);//выводим b
	printf("x8=%10o\ny16=%10x", x,y);//выводим значения х в восьмиричной системе счисления и у в шестнадцатиричной системе счисления
 
	return 0;
}