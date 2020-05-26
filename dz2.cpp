#define _CRT_SECURE_NO_WARNINGS  //для использования стандартных функций (scanf вместо scanf_s)
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

FILE* filee;
char* file_name;

struct Books {
	long int ISBN;
	char autor[200];
	char book_name[200];
	int book_num_all;
	int available_books;
};

int increment(long inc[], long size) {
	// inc[] массив, в который заносятся инкременты
	// size размерность этого массива
	int p1, p2, p3, s;

	p1 = p2 = p3 = 1;
	s = -1;
	do {// заполняем массив элементов по формуле Роберта Седжвика
		if (++s % 2) {
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else {
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
		// заполняем массив, пока текущая инкремента хотя бы в 3 раза меньше количества элементов в массиве
	} while (3 * inc[s] < size);

	return s > 0 ? --s : 0;// возвращаем количество элементов в массиве
}

template<class T>
void shellSort(T* a, long size) {
	// inc инкремент, расстояние между элементами сравнения
	// i и j стандартные переменные цикла
	// seq[40] массив, в котором хранятся инкременты
	long inc, i, j, seq[40];
	int s;//количество элементов в массиве seq[40]

	// вычисление последовательности приращений
	s = increment(seq, size);
	while (s >= 0) {
		//извлекаем из массива очередную инкременту
		inc = seq[s--];
		// сортировка вставками с инкрементами inc
		for (i = inc; i < size; i++) {
			T temp = a[i];
			// сдвигаем элементы до тех пор, пока не дойдем до конца или не упорядочим в нужном порядке
			for (j = i - inc; (j >= 0) && (a[j] > temp); j -= inc)
				a[j + inc] = a[j];
			// после всех сдвигов ставим на место j+inc элемент, который находился на i месте
			a[j + inc] = temp;
		}
	}
}




char* get_strng(char z = -1)
{
	char* strng = (char*)malloc(sizeof(char));

	if (z == -1)
	{
		char c = getchar();

		while (c == ' ' || c == '\t' || c == '\n')
		{

			c = getchar();

		}
		strng[0] = c;
	}
	else
		strng[0] = z;

	int i;
	for (i = 0; strng[i] != '\n'; ++i)
	{

		strng = (char*)realloc(strng, sizeof(char) * (i + 2));
		strng[i + 1] = getchar();

	}
	strng[i] = '\0';
	return strng;
}


char* get_strng_f(FILE* filee)
{
	char* strng = (char*)malloc(sizeof(char));


	strng[0] = fgetc(filee);

	int i;
	for (i = 0; strng[i] != '\n' && (strng[i] != -1 || strng[i - 1] != -1 || strng[i - 2] != -1); ++i)
	{

		strng = (char*)realloc(strng, sizeof(char) * (i + 2));
		strng[i + 1] = fgetc(filee);

	}

	if (strng[i] == -1 && strng[i - 1] == -1 && strng[i - 2] == -1)
	{
		strng[i] = '\0';
		strng[i - 1] = '\0';
		strng[i - 2] = '\0';
	}
	else
	{
		strng[i] = '\0';
	}
	
	return strng;
}




int str_count(FILE* filee)
{


	int lines = 0;
	int k = -1;
	while (!feof(filee))
	{

		if (fgetc(filee) == '\n')
			lines++;
		k++;
	}

	if (k)
		lines++;
	else if (!k)
	{
		printf("empty file: exit from program after pause\n\n");
		system("pause");
		exit(0);
	}

	fseek(filee, 0, 0);

	return lines;
}

int isbn_exist(Books* book, int liness, int isbn)
{
	int k = 1;
	for (int i = 0; i < liness ; ++i)
	{
		if (book[i].ISBN == isbn)
		{
			k = 0;
		}
	}

	if (k)
	{
		
		return isbn;
	}
	else
	{
		return 0;
	}
}

void rewriting(Books* books, int* lines)
{

	fclose(filee);
	filee = fopen(file_name, "w");

	for (int i = 0; i < *lines; ++i)
	{
		if (*lines - i - 1)
			fprintf(filee, "%d;%s;%s;%d;%d\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
		else
			fprintf(filee, "%d;%s;%s;%d;%d", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);


	}
}
void isbn_new(Books* books, int* lines,int ibsn)
{
	int new_isbn = isbn_exist(books, *lines, ibsn);

	if (new_isbn)
	{
		++* lines;
		int z = *lines;
		books = (Books*)realloc(books, sizeof(Books) * z);//выделям память на новую структуру для книги
		books[--z].ISBN = new_isbn;
		printf("\nВведите данные книги:\n");
		scanf("%s\n%s\n%d\n%d", books[z].autor, books[z].book_name, &(books[z].book_num_all), &(books[z].available_books));

		rewriting(books, lines);
		printf("\nКнига успешно добавлена!\n\n");


	}
	else
	{
		printf("\nКнига с таким ISBN = %d уже существует\n", ibsn);
	}
}



void delete_book(Books* book, int* liness, int isbn)
{
	int k = 0;
	int i = 0;
	for (i; i < *liness; ++i)
	{
		if (book[i].ISBN == isbn)
		{

			k = 1;
			break;
		}
	}

	if (k)
	{
		for (i; i < *liness - 1; ++i)
		{
			book[i].ISBN			= book[i + 1].ISBN; //1
			book[i].book_num_all	= book[i + 1].book_num_all;//4
			book[i].available_books	= book[i + 1].available_books;//5

			strcpy(book[i].autor, book[i + 1].autor);//2
			strcpy(book[i].book_name, book[i + 1].book_name);//3
		}
		--* liness;
		rewriting(book, liness);
		printf("\nКнига успешно удалена!\n\n");
	}
	else
	{
		printf("\nКниги c ISBN = %d не существует\n\n", isbn);
	}
}

int new_command()
{
	system("pause");
	system("cls");
	printf("0 - завершить работу программы\n1 - добавить новую книгу\n2 - удалить книгу\n3 - просмотр всей информации по книге\n4 - вывести информацию по всем книгам в виде таблицы\n5 - редактировать информацию по книге\n6 - изменить количество книг в библиотеке\n7 - выдать книгу студенту\n8 - принять книгу от студента\n9 - cделать бэкап\n10 - восстановить базу из файла бэкапа\n11 - поиск по фамилии автора\n\nВведите команду: ");

	// запрашиваем новую команду
	int commandd;
	scanf("%d", &commandd);
	return commandd;
}


void book_info(Books* books, int* liness, int isbn)
{
	int k = 0;
	int i = 0;
	for (i; i < *liness; ++i)
	{
		if (books[i].ISBN == isbn)
		{

			k = 1;
			break;
		}
	}

	if (k)
	{
		
		printf("\nISBN книги - %d\n", books[i].ISBN); 
		printf("Автор книги - %s\n", books[i].autor); 
		printf("Название книги - %s\n", books[i].book_name); 
		printf("Количество книг - %d\n", books[i].book_num_all); 
		printf("Книг у студентов - %d\n", books[i].available_books); 
		

		
		
		printf("\nИнформация по книге успешно выдана!\n\n");
	}
	else
	{
		printf("\nКниги c ISBN = %d не существует\n\n", isbn);
	}
}

void all_books_info(Books* books, int* lines)
{
	int* temp_arr = (int*)malloc(sizeof(int) * (*lines));
	for (int i = 0; i < *lines; ++i)
	{
		temp_arr[i] = books[i].ISBN;

	}
	shellSort(temp_arr, (*lines));

	char i[20] = "ISBN";
	char a[20] = "Автор";
	char n[20] = "Название книги";
	char k[20] = "Количество книг";
	char s[20] = "Книг у студентов";
	printf("\n\n%9s%30s%40s%20s%20s\n\n", i, a, n, k, s);
	for (int i = 0; i < *lines; ++i)
	{
		for (int g = 0; g < *lines; ++g)
		{
			if (books[g].ISBN == temp_arr[i])
			{


				printf("%9d%30s%40s%20d%20d\n\n", books[g].ISBN, books[g].autor, books[g].book_name, books[g].book_num_all, books[g].available_books);
			}
		}

	}
}

int Command(int command, Books* books, int* lines)
{
	if (command == 1)
	{
		printf("\nВведите ISBN новой книги: ");
		int isbn;
		scanf("%d", &isbn);
		isbn_new(books, lines, isbn);
		
		return new_command();
	}
	else if (command == 2)
	{
		printf("\nВведите ISBN для удаления книги: ");
		int isbn;
		scanf("%d", &isbn);
		delete_book(books, lines, isbn);
		
			
		return new_command();
			
		
	}
	else if (command == 3)
	{
		printf("\nВведите ISBN для получения информации по книге: ");
		int isbn;
		scanf("%d", &isbn);
		book_info(books, lines, isbn);


		return new_command();
	}
	else if (command == 4)
	{
		all_books_info(books, lines);
		


		return new_command();
	}
	else
	{
		printf("\nТакой команды не существует\n");


		
		return new_command();
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	

	printf("enter name of file1: ");


	//забираем лишние символы из потока (можно и убрать этот блок кода)
	char c = getchar();
	while (c == ' ' || c == '\t' || c == '\n') { c = getchar(); }


	
	file_name = get_strng(c);




	

	// открываем файл (если не открылся - завершаем прогу)
	if (!(filee = fopen(file_name, "r+")))
	{
		perror("fopen");
		return 1;
	}

	
	// кол-во строк в файле
	int liness = str_count(filee);
	int* lines = &liness;



	struct Books *books = (Books *)malloc(sizeof(Books) * liness);
	

	


	
	//считываем данные из файла в структуру
	for (int i = 0; i < liness ; ++i)
	{
		fscanf(filee, "%d;%[^;];%[^;];%d;%d", &(books[i].ISBN), books[i].autor, books[i].book_name, &(books[i].book_num_all), &(books[i].available_books));
		
		//удалить на релизе 
		printf("%d\n%s\n%s\n%d\n%d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
	}
	fseek(filee, 0, 0); //перемещаем курсор в начало строки 


	//считыавем команду
	system("cls");
	printf("0 - завершить работу программы\n1 - добавить новую книгу\n2 - удалить книгу\n3 - просмотр всей информации по книге\n4 - вывести информацию по всем книгам в виде таблицы\n5 - редактировать информацию по книге\n6 - изменить количество книг в библиотеке\n7 - выдать книгу студенту\n8 - принять книгу от студента\n9 - cделать бэкап\n10 - восстановить базу из файла бэкапа\n11 - поиск по фамилии автора\n\nВведите команду: ");
	int command;
	scanf("%d", &command);

	

	while (command)
	{
		command = Command(command, books, lines);
	}

	_putch('\n');
	system("pause");
	return 0;
}
