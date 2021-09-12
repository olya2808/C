#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define DEFINE_PART_SIZE 256

typedef struct NODE // Структура двусвязного списка
{
	char* word;
	struct NODE* prev;
	struct NODE* next;
} node;

int add_node(node ** head, char* str) // Функция добавления новой ноды (слова)
{
	if (!(*head)) // Если указатель нулевой, то есть нод в списке нет
	{
		(*head) = (node*)malloc(sizeof(node)); // Выделяем память на список
		if (!(*head))
			return 1;
		(*head)->next = (*head); // Говорим что следующая списка это она и есть
		(*head)->prev = (*head); // Говорим что предыдущая списка это текщая списка
		(*head)->word = str; // Присваиваем указатель на строку
		return 0;
	}
	(*head)->prev->next = (node*)malloc(sizeof(node)); // Выделяем память после последнего
	if (!(*head)->prev->next)
		return 1;
	(*head)->prev->next->next = (*head); // Говорим что следующий его элемент это первый элемент
	(*head)->prev->next->prev = (*head)->prev; // Говорим что его предыдущий элемент это последний элемент 
	(*head)->prev->next->word = str;
	(*head)->prev = (*head)->prev->next; // Говорим что у первого элемента новый предыдущий элемент (только что созданный)
	return 0;
}
int fill(node ** head)
{
	char c;
	int i;
	char * str;
	printf("Input sentence:\n");
	while (1)
	{
		while ((c = getchar()) == ' ' || c == '\n'); // Пропускаем пробелы
		if (c == '.') // Если точка через пробел
		{
			return 1;
		}
		str = (char*)malloc(DEFINE_PART_SIZE * sizeof(char)); // Выделяем память под строчку
		if (!str) // Проверка на корректность
		{
			printf("Error!\n");
			exit(1);
		}
		str[0] = c;
		i = 1;
		while ((c = getchar()) != ' ' && c != '\n' && c != ',' && c != '.') // Пока читаем символы
		{
			if ((i + 1) % DEFINE_PART_SIZE == 0) // Если конец выделенного участка памяти
			{
				str = (char*)realloc(str, (i + 1 + DEFINE_PART_SIZE) * sizeof(char)); // Перевыделяем память
				if (!str)
				{
					printf("Error!\n");
					exit(1);
				}
			}
			str[i] = c; // Записываем считанный символ
			i++; // Увеличиваем счетчик
		}
		str = (char*)realloc(str, (i + 1) * sizeof(char)); // Перевыделяем место для строки (для экономии памяти)
		if (!str)
		{
			printf("Error!\n");
			exit(1);
		}
		str[i] = '\0'; // Записываем символ конца строки
		if (add_node(head, str)) // Если не смогли выделить ноду для слова
		{
			printf("Error:!\n");
			free(str);
			if (c != '\n')
			return 1;
		}
		if (c == '.') // Если в конце или середине слова точка, то заканчиваем ввод
		{
			break;
		}
	}
	return 0;
}

void deletel(node ** head) // Функция удаления списка
{
	node * ptr;
	if (!(*head)) // Если пуст
		return;
	ptr = (*head)->next; // Переходим ко второму элементу
	while (ptr != (*head)) // Пока не дошли до головы списка
	{
		ptr = ptr->next; // Переходим на следующий элемент
		free(ptr->prev->word); // Освобождаем слово предыдущего
		free(ptr->prev); // Освобождаем предыдущую ноду
	}
	free(ptr->word);//Освобождаем от слова
	free(ptr); // Освобождаем голову
	(*head) = NULL; // Присваиваем указателю нуль
	return;
}

int change_word(char ** str, char * exp) // Функция разворота слова
{
	int i = 0;
	int len;
	while (exp[i] != '\0')
		i++;
	(*str) = (char*)malloc((i + 1) * sizeof(char)); // Выделяем память
	if (!(*str))
		return 1;
	(*str)[i] = '\0';
	len = --i;
	while (i)
	{
		(*str)[len - i] = exp[i]; // Копируем строку задом наперед
		i--;
	}
	(*str)[len] = *exp; // Копируем первый элемент
	return 0;
}

void change_list(node ** head) // Функция изменения списка
{
	char * str;
	node * min_ptr;
	node * ptr;
	if (!(*head))
		return;
	min_ptr = (*head); // Изначально максимальный элемент
	ptr = (*head)->next;
	while (ptr != (*head)) // Пока не дошли до головы
	{
		if (strcmp(ptr->word, min_ptr->word) < 0) // Если строка меньше минимальной строки
		{
			min_ptr = ptr;
		}
		ptr = ptr->next;
	}
	if (change_word(&str, min_ptr->word)) // Если не смогли развернуть слово
	{
		printf("Error: no memory for new string!\n");
		return;
	}
	ptr = min_ptr->prev; // Запоминаем предыдущий элемент
	min_ptr->prev = (node*)malloc(sizeof(node));
	if (!min_ptr) // Проверяем на корретность выделения памяти
	{
		printf("Error: no memory for new node!\n");
		free(str);
		return;
	}
	min_ptr->prev->next = min_ptr; // Говорим что у него слудующий это минимальный
	min_ptr->prev->prev = ptr; // Говорим что у нового элемента предыддущий это ранее запомненный
	ptr->next = min_ptr->prev; // Говорим запомненному элементу, что у него новый сосед справа
	min_ptr->prev->word = str;
	if (min_ptr == (*head)) // Если минимальный элемент это головной
		(*head) = min_ptr->prev; // Сдвигаем голову
	return;
}

void print_list(node * head) // Функция печати списка
{
	node * ptr = head;
	if (!head) // Если список пуст (нет слов)
	{
		printf("list is empty");
		return;
	}
	while (1)
	{
		printf("%s", ptr->word);
		ptr = ptr->next;
		if (ptr == head) // Если дошли до головы
		{
			printf(".\n");
			break; // Выход из цикла
		}
		else
			printf(" "); // Печатаем пробел
	}
	return;
}

int main()
{
	node * head = NULL; // Главный указатель на список
	if (fill(&head)) // Если функция вернула ошибку
	{
		deletel(&head); // Удаляем список
	}
	else
	{
			printf("Input:\n");
			print_list(head); // Печатаем список
			change_list(&head);
			printf("Result:\n");
			print_list(head);
			deletel(&head);
	}
return 0;
}
