#pragma once//условие однократного определения структуры
#include"Maker.h"//подключение файла со структурами
#include"Parameters.h"//подключение файла со структурами
struct TV//название структуры
{
	char brand[100];//объявление строкового массива
	struct Maker maker;//объявление структуры
	struct Parameters parameters;//объявление структуры
};
void scanstr(struct TV data[20], int n);//прототип функции для ввода данных
void check(struct TV data[20], int n);//прототип функции для проверки данных
void printstr(struct TV data[20], int n);//прототип функции для вывода данных
void task(struct TV data[20], int n); //прототип функции для выполнения задания
