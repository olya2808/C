#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//библиотека для ввода и вывода
#include<stdlib.h>//библиотека для работы со строками
#include<malloc.h>//библиотека для работы функции malloc
#include"Player.h"//заголовочный файл со структурой
#include"N.h"//заголовочный файл с глобальными переменными
void add(const char*name)//функция для добавления данных
{
	int k, i,j;//объявление счетчиков
	FILE*f = fopen(name, "rb");//открытие файла
	if (!f)//проверка создания
	{
		printf("file can't be opened\n");//сообщение об ошибке
		return;//завершение программы
	}
	fseek(f, 0, SEEK_END);//перемещение каретки в конец файла
	n = (ftell(f)) / sizeof(player);//узнаем количество элементов в файле
	fseek(f, 0, SEEK_SET);//перемещение каретки в начало файла
	if (data != NULL)//проверка для очистки структуры
	{
		free(data);//очищение структуры
	}
	printf("How many players do you want to add?\n");//вывод вопроса о количестве элементов для ввода
	scanf("%d", &k);//записываем количество элементов в переменную
	data = (player*)malloc((n+k) * sizeof(player));//выделение памяти для структуры
	for (i = 0; i < n; i++)//цикл для записи данных из файла в структуру
	{
		fread(&data[i], sizeof(player), 1, f);//записываем в структуру данные, которые уже лежат в файле
	}
	j = 1;//счетчик для вывода
	for (i = n; i < n + k; i++)//цикл для добавления данных в структуру
	{

		printf("input %d player's name\n", j );//просьба вывести имя j-ого игрока
		scanf("%s", &data[i].fio.imya);//запись в структуру
		printf("input %d player's surname\n", j);//просьба вывести фамилию j-ого игрока
		scanf("%s", &data[i].fio.familia);//запись в структуру
		printf("input %d player's father's name\n", j);//просьба вывести отчество j-ого игрока
		scanf("%s", &data[i].fio.otchestvo);//запись в структуру
		printf("input %d player's club\n", j);//просьба вывести клуб j-ого игрока
		scanf("%s", &data[i].club);//запись в структуру
		printf("input %d player's amplua\n",j);//просьба вывести амплуа j-ого игрока
		scanf("%s", &data[i].amplua);//запись в структуру
		printf("input %d player's age\n",j);//просьба вывести возраст j-ого игрока
		scanf("%s", &data[i].age);//запись в структуру
		printf("input number of plays of %d player\n", j);//просьба вывести количество игр j-ого игрока
		scanf("%s", &data[i].plays);//запись в структуру
		printf("input number of goals of %d player\n", j);//просьба вывести количество голов j-ого игрока
		scanf("%s", &data[i].goals);//запись в структуру
		printf("\n");//табуляция для красивого вывода
		j++;//увеличение счетчика
	}
	fclose(f);//закрытие файла
	f = fopen(name, "wb");//открытие файла заново
	for (i = 0; i < k+n; i++)//цикл для записи в файл
	{
		fwrite(&data[i], sizeof(player), 1, f);//запись в файл
	}
	fclose(f);//закрытие файла
	menu(name);//вызов меню
	return;//завершение выполнения функции
}
