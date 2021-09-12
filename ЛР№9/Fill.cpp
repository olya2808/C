#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//библиотека для ввода и вывода
#include<stdlib.h>//библиотека для работы со строками
#include<malloc.h>//библиотека для работы функции malloc
#include"Player.h"//заголовочный файл со структурой
#include"N.h"//заголовочный файл с глобальными переменными
void fill(const char*name)//функция для заполнения файла
{
	int i;//объявление счетчика
	printf("How many football players do you want to input?\n");//вывод вопроса о количестве элементов для ввода
	scanf("%d", &n);//записываем количество элементов в глобальную переменную
	if (data  != NULL)//проверка для очистки структуры
	{
		free(data);//очищение структуры
	}
	FILE*f = fopen(name, "wb");//открытие файла
	if (!f)//проверка открытия файла
	{
		printf("file can't be opened\n");//сообщение об ошибке
		return 0;//завершение программы
	}
	data = (player*)malloc(n * sizeof(player));//выделение памяти для структуры
	for (i = 0; i < n; i++)//цикл для записы в структуру
	{
		printf("input %d player's name\n", i+1);//просьба вывести имя игрока
		scanf("%s", &data[i].fio.imya);//запись в структуру
		printf("input %d player's surname\n", i+1);//просьба вывести фамилию игрока
		scanf("%s", &data[i].fio.familia);//запись в структуру
		printf("input %d player's father's name\n", i+1);//просьба вывести отчество игрока
		scanf("%s", &data[i].fio.otchestvo);//запись в структуру
		printf("input %d player's club\n", i+1);//просьба вывести клуб игрока
		scanf("%s", &data[i].club);//запись в структуру
		printf("input %d player's amplua\n", i+1);//просьба вывести амплуа игрока
		scanf("%s", &data[i].amplua);//запись в структуру
		printf("input %d player's age\n", i+1);//просьба вывести возраст игрока
		scanf("%s", &data[i].age);//запись в структуру
		printf("input number of plays of %d player\n", i+1);//просьба вывести количество игр игрока
		scanf("%s", &data[i].plays);//запись в структуру
		printf("input number of goals of %d player\n", i+1);//просьба вывести количество голов игрока
		scanf("%s", &data[i].goals);//запись в структуру
		printf("\n");
	}
	for (i = 0; i < n; i++)//цикл для записи в файл
	{
		fwrite(&data[i], sizeof(player), 1, f);//запись в файл
	}
	fclose(f);//закрытие файла
	return;//завершение выполнения функции
}
