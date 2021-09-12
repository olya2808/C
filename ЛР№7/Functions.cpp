#include"TV.h"//подключение файла со структурами
#include"stdio.h"//подключение файла со структурами
#include"stdlib.h"//подключение библиотеки
#include"string.h"//подключение библиотеки

void scanstr(struct TV data[20], int n)//описание переменных, которые получает функция
{
	int i;//объявление счетчика
	for (i = 0; i < n; i++)//цикл 
	{
		printf("input brand\n");//просим ввести название марки
		scanf("%s", &data[i].brand);//считываем название марки
		printf("input city\n");//просим ввести город
		scanf("%s", &data[i].maker.city);//считываем название города
		printf("input factory\n");//просим ввести название завода
		scanf("%s", &data[i].maker.factory);//считываем название завода
		printf("input year of making\n");//просим ввести год создания
		scanf("%d", &data[i].maker.year);//считываем год создания
		printf("input prise\n");//просим ввести цену
		scanf("%d", &data[i].parameters.price);//считываем цену
		printf("input size of screen\n");//просим ввести размер экрана
		scanf("%d", &data[i].parameters.sizeofscreen);//считываем размер экрана
		printf("\n");//пропуск строки
	}
	
}
void check(struct TV data[20], int n)//описание переменных, которые получает функция
{
	int i;//объявляем счетчик
	for (i = 0; i < n; i++)//цикл
	{
		if (data[i].maker.year < 1929 || data[i].parameters.price <= 0 || data[i].parameters.sizeofscreen <= 0|| data[i].maker.year >2019)//проверяем корректность введенных данных
		{
			printf("data is incorrect\n");//сообщаем об ошибке
			return;//завершаем выполнение
		}
	}
}
void printstr(struct TV data[20], int n)//описание переменных, которые получает функция
{
	int i;//объявляем счетчик
	for (i = 0; i < n; i++)//цикл
	{
		printf("TV #%d\n", i + 1);//выводим номер телевизора
		printf("Brand:%s\n", data[i].brand);//выводим марку
		printf("City:%s\n", data[i].maker.city);//выводим город
		printf("Factory:%s\n", data[i].maker.factory);//выводим завод
		printf("Year of making:%d\n", data[i].maker.year);//выводим год создания
		printf("Prise:%d\n", data[i].parameters.price);//выводим цену
		printf("Size of screen:%d\n", data[i].parameters.sizeofscreen);//выводим размер экрана
	}
	printf("\n");//пропуск строки
}
void task(struct TV data[20], int n)//описание переменных, которые получает функция
{
	int y, i, j, count, size, pos, max;//объявление целых переменных
	char* array[20];//объявление массива указателей
	char* mark[20];//объявление массива указателей
	int number[20];//объявление целочисленного массива
	printf("input year of making\n");//просим ввести год создания
	scanf_s("%d", &y);//считываем год создания
	if (y > 2019 || y < 1929)//проверяем корректность введенных данных
	{
		printf("incorrect year");//сообщаем об ошибке
		return;//завершаем выполнение
	}
	size = 0;//инициализируем переменную для размера массива
	j = 0;//инициализируем счетчик
	for (i = 0; i < n; i++)//цикл для заполнения массива
	{
		if (data[i].maker.year > y)//условие заполнения массива
		{
			array[j] = data[i].brand;//заполняем массив
			size++;//увеличиваем его размер
			j++;//увеличиваем счетчик
		}
	}
	if (size == 0)//проверяем наличие элементов в массиве
	{
		printf("task can't be solved");//сообщаем об ошибке
		return;//завершаем выполнение
	}
	for (i = 0; i < size - 1; i++)//цикл для нахождения самой популярной марки
	{
		count = 0;//переменная для подсчета повторения названия марки
		for (j = i + 1; i < size; j++)//цикл для подсчета
		{
			if (strcmp(array[i], array[j]) == 0)//условие для сравнения
			{
				count++;//увеличиваем счетчик
			}
		}
		mark[i] = array[i];//заполнение массива названиями марок
		number[i] = count;//заполнение массива числом повторений названий марок
	}
	max = number[0];//инициализация переменной максимального числа повторений названий марок
	pos = 0;//инициализация позиции самой популярной марки в массиве
	for (i = 1; i < size - 1; i++)//цикл для нахождения максимального числа повторений названий марок
	{
		if (max < number[i])//условие сравнения
		{
			max = number[i];//меняем значение максимального числа повторений названий марок
			pos = i;//запоминаем его позицию
		}
	}
	printf("%s", array[pos]);//выводим самую популярную марку
}

