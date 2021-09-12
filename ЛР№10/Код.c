#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
void print(node *l, int n)//функция для печати списка
{
	int i = 0;
	if (!l)
	{
		printf("List is empty so task can't be solved\n");//сообщение об ошибке
		exit(1);
	}
	while (l)
	{
		if (l->coe == 1)
		{
			printf("X^%d", l->deg);
		}
		else if (l->deg == 0)
			printf("%d", l->coe);
		else if (l->deg == 1)
			printf("%dX", l->coe);
		else
		{
			printf("%-dX^", l->coe);
			printf("%d", l->deg);
		}

		if (l->next != NULL)
		{
			printf(" + ");
		}
		l = l->next;
		i++;
	}
	printf("\n");
	return;
}
void add(node **l, int coef, int degr)//функция для добавления элементов в список
{
	node *h = (node*)malloc(sizeof(node));
	h->coe = coef;
	h->deg = degr;
	h->next = (*l);
	(*l) = h;
	return;
}
void sort(int *d, int*c, int n)//функция для сортировки массива для красивого вывода
{
	int tmp1, tmp2;
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (d[j] > d[j + 1])
			{
				int tmp1 = d[j];
				d[j] = d[j + 1];
				d[j + 1] = tmp1;
				int tmp2 = c[j];
				c[j] = c[j + 1];
				c[j + 1] = tmp2;
			}
		}
	}
	return;
}
node* input(node *l, int n )//функция для получения данных для последующей записи в список
{
	int i = 0, j = 0, m = 0, w = 0,k=0;
	int*c, *d;
	c = (int*)malloc(n * sizeof(int));
	d = (int*)malloc(n * sizeof(int));
	printf("Input your degrees\n");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	printf("Input your coefficients\n");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &c[i]);
	}
	//далее идет устранение всех крайних ситуаций
	for (i = 0; i < n - m - 1; i++)
	{
		if (c[i] == 0)
		{
			for (i; i < n - m- 1; i++)
			{
				c[i] = c[i + 1];
				d[i] = d[i + 1];
			}

			m++;
			d = (int*)realloc(d, (n - m) * sizeof(int));
			c = (int*)realloc(c, (n - m) * sizeof(int));
		}
	}
	if (c[n - m - 1] == 0)
	{
		m++;
		d = (int*)realloc(d, (n - m) * sizeof(int));
		c = (int*)realloc(c, (n - m) * sizeof(int));
	}
	for (i = 0; i < n - m - 1; i++)
	{
		j = i;
		while (j < n - m - 1)
		{
			if (w >= 1)
			{
				if (d[j] == d[j - 1])
				{
					w++;
					c[j - 1]+= c[j];
					for (k = j; k < n - m - 1; k++)
					{
						c[k] = c[k + 1];
						d[k] = d[k + 1];
					}
					d = (int*)realloc(d, (n - m- w) * sizeof(int));
					c = (int*)realloc(c, (n - m - w) * sizeof(int));
				}
				else
				{
					if (d[i] == d[j + 1])
					{
						w++;
						c[j - 1]+= c[j + 1];

						for (k = j + 1; k < n - m - 1; k++)
						{
							c[k] = c[k + 1];
							d[k] = d[k + 1];
						}
						d = (int*)realloc(d, (n - m - w) * sizeof(int));
						c = (int*)realloc(c, (n - m - w) * sizeof(int));
					}
				}
			}
			else
			{
				if (d[i] == d[j + 1])
				{
					w++;

					c[i] +=c[j + 1];
					for (k = j + 1; k < n - m - 1; k++)
					{
						c[k] = c[k + 1];
						d[k] = d[k + 1];
					}
					d = (int*)realloc(d, (n - m - w) * sizeof(int));
					c = (int*)realloc(c, (n - m - w) * sizeof(int));

				}
			}
			j++;
		}
	}
	for (i = 0; i < n - m - 1; i++)
	{
		if (c[i] == 0)
		{

			for (i; i < n - m - 1; i++)
			{
				c[i] = c[i + 1];
				d[i] = d[i + 1];
			}

			m++;
			d = (int*)realloc(d, (n - m) * sizeof(int));
			c = (int*)realloc(c, (n - m) * sizeof(int));
		}
	}
	sort(d, c, n - m - w);
	i = 0;
	for (i = 0; i < n - w - m; i++)
	{
		add(&l, c[i], d[i]);
	}
	return l;
}
void deletel(node **head)//функция для удаления списка
{
	node* next, *tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*head = NULL;
	return;
}
void task(node* l1, node* l2, int n1, int n2)//функция для выполнения задания
{
	int i,j,n=0;
	node *l3=NULL,*tmp=l2;
	//сравнение степеней и коэффициентов в многочленах
	for (i = 0; i < n1; i++)
	{
		l2 = tmp;
		for (j = 0; j < n2; j++)
		{
			if ((l1->deg) == (l2->deg))
			{
				n++;
				if (l1->coe > l2->coe)
				{
					add(&l3, l1->coe, l1 -> deg);
				}
				else
				{
					add(&l3, l2->coe, l2->deg);
				}
				
			}
			l2 = l2->next;
		}
		l1 = l1->next;
	}
	if (n == 0)
	{
		printf("Final list is empty\n");//сообщение об ошибке
		exit(1);
	}
	print(l3, n);
	deletel(&l1);
	deletel(&l2);
	deletel(&l3);
	return;
}
int main()
{
	node *l1 = NULL;
	node *l2 = NULL;
	int n1, n2;
	//считывание данных, необходимых для выполнения функций
	printf("Input number of elements in the first polynominal\n");
	scanf("%d", &n1);
	printf("Input number of elements in the second polynominal\n");
	scanf("%d", &n2);
	printf("Input the first polynominal\n ");
	l1 = input(l1, n1);
	printf("Input the second polynominal\n ");
	l2= input(l2, n2);
	printf("L1: ");
	print(l1, n1);
	printf("L2: ");
	print(l2, n2);
	printf("L: ");
	task(l1, l2, n1, n2);//вызов функции, которая выполняет задание
	deletel(&l1);//удаление 1 списка
	deletel(&l2);//удаление 2 списка
	return 0;
}
