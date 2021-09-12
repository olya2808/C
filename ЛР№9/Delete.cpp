#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//библиотека для ввода и вывода
#include<stdlib.h>//библиотека для работы со строками
#include<malloc.h>//библиотека для работы функции malloc
#include"Player.h"//заголовочный файл со структурой
#include"N.h"//заголовочный файл с глобальными переменными
void move(int poz)//функция для сдвига после удаления
{
	int i;//объявление целой переменной
	for (i = poz; i < n-1; i++)//цикл для сдвига
	{
		data[i] = data[i + 1];//записываем а данный элемент следующий
	}
	return;//завершаем выполнение функции
}
void write(int count, FILE*f, const char*name)//функция записи в файл
{
	int i;//объявление целой переменной
	f = fopen(name, "wb");//открытие файла для записи заново
	for (i = 0; i < n - count; i++)//цикл для записи
	{
		fwrite(&data[i], sizeof(player), 1, f);//запись в файл
	}
	return;//завершение выполнения функции
}
void delets(const char*name)//функция для удаления
{
	int task, i,am;//объявление целых переменных
	am = n;//инициализация переменной
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
	data = (player*)malloc(n * sizeof(player));//выделение памяти для структуры
	for (i = 0; i < n; i++)//цикл для записи данных из файла в структуру
	{
		fread(&data[i], sizeof(player), 1, f);//записываем в структуру данные, которые лежат в файле
	}
	fclose(f);//закрытие файла
	am = n;//инициализация переменной
	printf("By which parameter do you want to delete player?\n1)Name\n2)Surname\n3)Father's name\n4)Player's club\n5)Amplua\n6)Player's age\n7)Number of Plyer's plays\n8)Number of player's goals\n");//просим ввести параметр, по которому надо удалять
	scanf("%d", &task);//считываем параметр для удаления
	switch (task)//функция для удаления по различным параметрам
	{
		case 1://случай для удаления по имени
		{
			int i, count = 0;//объявление целых переменных
			char imya[10];//объявление переменной, по которой идет удаление
			printf("input name that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", imya);//считываем данные, по которым пойдет удаление
			for (i = 0; i < am; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(imya, data[i].fio.imya) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i --;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
		case 2://случай для удаления по фамилии
		{
			int i, count = 0;//объявление целых переменных
			char familia[10];//объявление переменной, по которой идет удаление
			printf("input surname that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", familia);//считываем данные, по которым пойдет удаление
			for (i = 0; i < am; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(familia, data[i].fio.familia) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i--;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
		case 3://случай для удаления по отчеству
		{
			int i, count = 0;//объявление целых переменных
			char otchestvo[10];//объявление переменной, по которой идет удаление
			printf("input father's name that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", otchestvo);//считываем данные, по которым пойдет удаление
			for (i = 0; i < am; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(otchestvo, data[i].fio.otchestvo) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i--;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
		case 4://случай для удаления по клубу
		{
			int i, count = 0;//объявление целых переменных
			char club[10];//объявление переменной, по которой идет удаление
			printf("input club that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", club);//считываем данные, по которым пойдет удаление
			for (i = 0; i < am; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(club, data[i].club) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i--;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
		case 5://случай для удаления по амплуа
		{
			int i, count = 0;//объявление целых переменных
			char amplua[10];//объявление переменной, по которой идет удаление
			printf("input amplua that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", amplua);//считываем данные, по которым пойдет удаление
			for (i = 0; i < n; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(amplua, data[i].amplua) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i--;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
		case 6://случай для удаления по возрасту
		{
			int i, count = 0;//объявление целых переменных
			char age[3];//объявление переменной, по которой идет удаление
			printf("input age that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", age);//считываем данные, по которым пойдет удаление
			for (i = 0; i < am; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(age, data[i].age) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i--;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
		case 7://случай для удаления по количеству матчей
		{
			int i, count = 0;//объявление целых переменных
			char plays[5];//объявление переменной, по которой идет удаление
			printf("input number of plays that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", plays);//считываем данные, по которым пойдет удаление
			for (i = 0; i <am; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(plays, data[i].plays) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i--;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
		case 8://случай для удаления по количеству забитых голов
		{
			int i, count = 0;//объявление целых переменных
			char goals[6];//объявление переменной, по которой идет удаление
			printf("input number of goals that you need\n");//просим ввести данные, по которым пойдет удаление
			scanf("%s", goals);//считываем данные, по которым пойдет удаление
			for (i = 0; i < am; i++)//цикл для поиска данных для удаления
			{
				if (strcmp(goals, data[i].goals) == 0)//сравниваем данные в структуре с данными для удаления
				{
					count++;//увеличиваем счетчик
					move(i);//вызываем функцию для сдвига
					i--;//уменьшаем счетчик
					am--;//уменьшаем счетчик
				}
			}
			write(count, f, name);//вызываем функцию для записи в файл
			break;//завершаем выполнение данного случая
		}
	}
	fclose(f);//закрытие файла
	menu(name);//вызов функции меню
}
