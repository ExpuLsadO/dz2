#define _CRT_SECURE_NO_WARNINGS  //для использования стандартных функций (scanf вместо scanf_s)
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

FILE* filee_students; // данные файла студентов 
char* file_name_students; // имя файла с инфой о студентах


FILE* filee; // данные файла книг 
char* file_name; //иня файла для книг


FILE* filee_usr; // данные файла юзер
char* file_name_usr; //иня файла юзер


FILE* filee_bks_st; // данные файла книги и студенты
char* file_name_bks_st; //иня файла книги и студенты


char str[] = "0 - завершить работу программы\n1 - добавить новую книгу\n2 - удалить книгу\n3 - просмотр всей информации по книге\n4 - вывести информацию по всем книгам в виде таблицы\n5 - редактировать информацию по книге\n6 - изменить количество доступных книг в библиотеке\n7 - выдать книгу студенту\n8 - принять книгу от студента\n9 - cделать бэкап\n10 - восстановить базу из файла бэкапа\n11 - поиск по фамилии автора\n12 - информация о студентах взявших книгу\n\nВведите команду: ";
char str_0[] = "-1 - сменить меню\n0 - завершить работу программы\n1 - добавить новую книгу\n2 - удалить книгу\n3 - просмотр всей информации по книге\n4 - вывести информацию по всем книгам в виде таблицы\n5 - редактировать информацию по книге\n6 - изменить количество доступных книг в библиотеке\n7 - выдать книгу студенту\n8 - принять книгу от студента\n9 - cделать бэкап\n10 - восстановить базу из файла бэкапа\n11 - поиск по фамилии автора\n12 - информация о студентах взявших книгу\n\nВведите команду: ";
char str_st[] = "0 - завершить работу программы\n1 - добавить студента\n2 - удалить студента по номеру зачетной книжки\n3 - редактировать информацию по студенту\n4 - вывести информацию по всем студентам в виде таблицы\n5 - просмотреть информацию по студенту по номеру зачетной книжки\n6 - сделать бэкап\n7 - восстановить базу из файла бэкапа\n8 - поиск по фамилии студента\n9 - информация о книгах у студента\n\nВведите команду: ";
char str_st_0[] = "-1 - сменить меню\n0 - завершить работу программы\n1 - добавить студента\n2 - удалить студента по номеру зачетной книжки\n3 - редактировать информацию по студенту\n4 - вывести информацию по всем студентам в виде таблицы\n5 - просмотреть информацию по студенту по номеру зачетной книжки\n6 - сделать бэкап\n7 - восстановить базу из файла бэкапа\n8 - поиск по фамилии студента\n9 - информация о книгах у студента\n\nВведите команду: ";
char str_admin[] = "0 - завершить работу программы\n1 - меню студентов\n2 - меню книг\n\nВведите команду: ";



struct Books 
{
	long long int ISBN;
	char autor[200];
	char book_name[200];
	int book_num_all;
	int available_books;
};

struct Students 
{
	char zachetka[20];
	char surname[100];
	char name[100];
	char patronymic[100]; //отчество
	char faculty[5];
	char specialty[100];
	
};

struct Users
{
	char login[20];
	char password[20];
	int students;
	int books;
};

struct Books_St
{
	long long int ISBN;
	char zachetka[20];
	char date[15];
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

int str_cmp(char* a, char* b)
{
	int k = 1;
	for (int i = 0; a[i] != '\0' || b[i] != '\0'; ++i)
	{
		if (a[i] != b[i])
		{
			k = 0;
			break;
		}
	}
	return k;
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

Books* start(int* lines)
{
	

	

	// открываем файл (если не открылся - завершаем прогу)
	if (!(filee = fopen(file_name, "r+")))
	{
		perror("fopen");
		system("pause");
		system("cls");
		return NULL;
	}


	// кол-во строк в файле
	


	// выделяем память под массив структур 
	Books* books = (Books*)malloc(sizeof(Books));


	int i = 0;
	fscanf(filee, "%lld;%[^;];%[^;];%d;%d", &(books[i].ISBN), books[i].autor, books[i].book_name, &(books[i].book_num_all), &(books[i].available_books));
	//считываем данные из файла в структуру
	
	for (++i; books[i - 1].ISBN > 0; ++i)
	{
		books = (Books*)realloc(books, sizeof(Books) * (i + 1));
		fscanf(filee, "%lld;%[^;];%[^;];%d;%d", &(books[i].ISBN), books[i].autor, books[i].book_name, &(books[i].book_num_all), &(books[i].available_books));
		
		//удалить на релизе 
		//printf("%d\n%s\n%s\n%d\n%d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
	}
	*lines = i - 1;
	fseek(filee, 0, 0); //перемещаем курсор в начало файла

	return books;
}

Students* start_st(int* lines_st)
{
	

	

	

	// открываем файл (если не открылся - завершаем прогу)
	if (!(filee_students = fopen(file_name_students, "r+")))
	{
		perror("fopen");
		system("pause");
		system("cls");
		return NULL;
	}


	// кол-во строк в файле
	


	// выделяем память под массив структур 
	Students* students = (Students*)malloc(sizeof(Students));


	int i = 0;
	fscanf(filee_students, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);
	//считываем данные из файла в структуру
	
	for (++i; students[i - 1].zachetka[0] > 0; ++i) // если первым символом в номере зачетной книжки идет не число, значит строки в файле кончились
	{
		students = (Students*)realloc(students, sizeof(Students) * (i + 1));
		fscanf(filee_students, "\n%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);

		//удалить на релизе 
		//printf("%d\n%s\n%s\n%d\n%d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
	}
	*lines_st = i - 1;
	fseek(filee_students, 0, 0); //перемещаем курсор в начало файла

	return students;

}

Users* start_usr(int* lines_usr)
{
	// открываем файл (если не открылся - завершаем прогу)
	if (!(filee_usr = fopen(file_name_usr, "r+")))
	{
		perror("fopen");
		system("pause");
		system("cls");
		return NULL;
	}


	// кол-во строк в файле



	// выделяем память под массив структур 
	Users* users = (Users*)malloc(sizeof(Users));


	int i = 0;
	fscanf(filee_usr, "%[^;];%[^;];%d;%d", users[i].login, users[i].password, &(users[i].students), &(users[i].books));

	for (++i; users[i].students > -1; ++i) // если первым символом в номере зачетной книжки идет не число, значит строки в файле кончились
	{
		users = (Users*)realloc(users, sizeof(Users) * (i + 1));
		fscanf(filee_usr, "\n%[^;];%[^;];%d;%d", users[i].login, users[i].password, &(users[i].students), &(users[i].books));

		//удалить на релизе 
		//printf("%d\n%s\n%s\n%d\n%d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
	}
	*lines_usr = i - 1;
	fseek(filee_usr, 0, 0); //перемещаем курсор в начало файла

	return users;
}

Books_St* start_bks_st(int* lines_bks_st)
{
	// открываем файл (если не открылся - завершаем прогу)
	if (!(filee_bks_st = fopen(file_name_bks_st, "r+")))
	{
		perror("fopen");
		system("pause");
		system("cls");
		return NULL;
	}


	// кол-во строк в файле



	// выделяем память под массив структур 
	Books_St* books_st = (Books_St*)malloc(sizeof(Books_St));


	int i = 0;
	fscanf(filee_bks_st, "%lld;%[^;];%[^\n]", &(books_st[i].ISBN), books_st[i].zachetka, books_st[i].date);

	for (++i; books_st[i - 1].ISBN > -1; ++i) // если первым символом в номере книжки идет не число, значит строки в файле кончились
	{
		books_st = (Books_St*)realloc(books_st, sizeof(Books_St) * (i + 1));
		fscanf(filee_bks_st, "\n%lld;%[^;];%[^\n]", &(books_st[i].ISBN), books_st[i].zachetka, books_st[i].date);
		//удалить на релизе 
		//printf("%d\n%s\n%s\n%d\n%d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
	}
	*lines_bks_st = i - 1;
	fseek(filee_bks_st, 0, 0); //перемещаем курсор в начало файла

	return books_st;
}

long long int isbn_exist(Books* book, int liness, long long int isbn)
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

int zachetka_exist(Students* students, int liness, char* zachetka)
{
	int k = 1;
	for (int i = 0; i < liness; ++i)
	{
		if (str_cmp(students[i].zachetka, zachetka))
		{
			k = 0;
		}
	}

	if (k)
	{

		return 1;
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

	for (int i = 0; i < *lines && books[i].ISBN > 0; ++i)// books[i].ISBN > 0 - если менять файл в exel, то появляется невидимая строка, из-за которой *lines получается на 1 больше действительного
	{
		if (*lines - i - 1 && books[i+1].ISBN > 0)
			fprintf(filee, "%lld;%s;%s;%d;%d\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
		else
			fprintf(filee, "%lld;%s;%s;%d;%d", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);


	}
}

void rewriting_st(Students* students, int* lines)
{

	fclose(filee_students);
	filee_students = fopen(file_name_students, "w");

	for (int i = 0; i < *lines && students[i].zachetka[0] > 0; ++i)// books[i].ISBN > 0 - если менять файл в exel, то появляется невидимая строка, из-за которой *lines получается на 1 больше действительного
	{
		if (*lines - i - 1 && students[i + 1].zachetka[0] > 0)
			fprintf(filee_students, "%s;%s;%s;%s;%s;%s\n", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);
		else
			fprintf(filee_students, "%s;%s;%s;%s;%s;%s", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);


	}
}

void rewriting_bks_st(Books_St* bks_st, int* lines) 
{
	fclose(filee_bks_st);
	filee_bks_st = fopen(file_name_bks_st, "w");

	for (int i = 0; i < *lines && bks_st[i].ISBN > -1; ++i)// books[i].ISBN > 0 - если менять файл в exel, то появляется невидимая строка, из-за которой *lines получается на 1 больше действительного
	{
		if (*lines - i - 1 && bks_st[i + 1].ISBN > 0)
			fprintf(filee_bks_st, "%lld;%s;%s\n", bks_st[i].ISBN, bks_st[i].zachetka, bks_st[i].date);
		else
			fprintf(filee_bks_st, "%lld;%s;%s", bks_st[i].ISBN, bks_st[i].zachetka, bks_st[i].date);


	}
}

void isbn_new(Books* books, int* lines, long long int ibsn)
{
	long long int new_isbn = isbn_exist(books, *lines, ibsn);

	if (new_isbn)
	{
		++* lines;
		int z = *lines;
		books = (Books*)realloc(books, sizeof(Books) * z);//выделям память на новую структуру для книги
		books[--z].ISBN = new_isbn;
		printf("\nВведите данные книги:\n");
		printf("\nВведите автора: ");
		char* temp = get_strng();
		strcpy(books[z].autor, temp);

		printf("\nВведите название книги: ");
		temp = get_strng();
		strcpy(books[z].book_name, temp);

		printf("\nВведите общее количество книг: ");
		scanf("%d", &(books[z].book_num_all));

		printf("\nВведите количество доступных книг: ");
		scanf("%d", &(books[z].available_books));

		rewriting(books, lines);
		printf("\nКнига успешно добавлена!\n\n");


	}
	else
	{
		printf("\nКнига с таким ISBN = %d уже существует\n", ibsn);
	}
}

void zachetka_new(Students* students, int* lines, char* zachetka)
{
	 

	if (zachetka_exist(students, *lines, zachetka))
	{
		++* lines;
		int z = *lines;
		students = (Students*)realloc(students, sizeof(Students) * z);//выделям память на новую структуру для книги
		
		strcpy(students[--z].zachetka, zachetka);

		printf("\nВведите данные студента:\n");
		printf("\nВведите фамилию: ");
		char* temp = get_strng();
		strcpy(students[z].surname, temp);
		
		printf("\nВведите имя: ");
		temp = get_strng();
		strcpy(students[z].name, temp);

		printf("\nВведите отчество: ");
		temp = get_strng();
		strcpy(students[z].patronymic, temp);

		printf("\nВведите факультет: ");
		temp = get_strng();
		strcpy(students[z].faculty, temp);

		printf("\nВведите специальность: ");
		temp = get_strng();
		strcpy(students[z].specialty, temp);


		rewriting_st(students, lines);
		printf("\nСтудент успешно добавлен!\n\n");


	}
	else
	{
		printf("\nСтудент с номером зачетки = %s уже существует\n", zachetka);
	}
}

void delete_book(Books* book, Books_St* bks_st, int* lines_bks_st, int* liness, long long int isbn)
{
	int z = 1;// проверка на то, есть ли книга в файле с студентами и книгами (можно удалить книгу если ее нет у студентов)
	for (int a = 0; a < *lines_bks_st; ++a)
	{
		if (bks_st[a].ISBN == isbn)
		{

			z = 0;
			break;
		}
	}

	if (z)
	{
		// проверка на то есть ли книга в файле с книгами
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
				book[i].ISBN = book[i + 1].ISBN; //1
				book[i].book_num_all = book[i + 1].book_num_all;//4
				book[i].available_books = book[i + 1].available_books;//5

				strcpy(book[i].autor, book[i + 1].autor);//2
				strcpy(book[i].book_name, book[i + 1].book_name);//3
			}
			--* liness;
			rewriting(book, liness);
			printf("\nКнига успешно удалена!\n\n");
		}
		else
		{
			printf("\nКниги c ISBN = %lld не существует\n\n", isbn);
		}
	}
	else
	{
		printf("\nКнига c ISBN = %lld есть у студента/ов\n\n", isbn);
	}
}

void delete_student(Students* students, Books_St* bks_st, int* lines_bks_st, int* liness, char* zachetka)
{
	int z = 1;// проверка на то, есть ли студент в файле с студентами и книгами (можно удалить студента если у него нет книг)
	for (int a = 0; a < *lines_bks_st; ++a)
	{
		if (str_cmp(bks_st[a].zachetka, zachetka))
		{

			z = 0;
			break;
		}
	}
	
	if (z)
	{
		// проверка на то, есть ли зачетка в файле со студентами
		int k = 0;
		int i = 0;
		for (i; i < *liness; ++i)
		{
			if (str_cmp(students[i].zachetka, zachetka))
			{

				k = 1;
				break;
			}
		}

		if (k)
		{
			for (i; i < *liness - 1; ++i)
			{


				strcpy(students[i].zachetka, students[i + 1].zachetka);
				strcpy(students[i].surname, students[i + 1].surname);
				strcpy(students[i].name, students[i + 1].name);
				strcpy(students[i].patronymic, students[i + 1].patronymic);
				strcpy(students[i].faculty, students[i + 1].faculty);
				strcpy(students[i].specialty, students[i + 1].specialty);
			}
			--* liness;

			rewriting_st(students, liness);
			printf("\nСтудент успешно удален!\n\n");
		}
		else
		{
			printf("\nСтудента c номером зачетки = %s не существует в файле = %s\n\n", zachetka, file_name_students);
		}
	}
	else
	{
		printf("\nУ студента c номером зачетки = %s есть книги\n\n", zachetka);
	}
}

int new_command(int i = 1)
{
	if (i)
	{
		system("pause");
		system("cls");
		printf(str);

		// запрашиваем новую команду
		int commandd;
		scanf("%d", &commandd);
		return commandd;
	}
	else
	{
		system("pause");
		system("cls");
		printf(str_0);

		// запрашиваем новую команду
		int commandd;
		scanf("%d", &commandd);
		return commandd;
	}
}

int new_command_st(int i = 1)
{
	if (i)
	{
		system("pause");
		system("cls");
		printf(str_st);

		// запрашиваем новую команду
		int commandd;
		scanf("%d", &commandd);
		return commandd;
	}
	else
	{
		system("pause");
		system("cls");
		printf(str_st_0);

		// запрашиваем новую команду
		int commandd;
		scanf("%d", &commandd);
		return commandd;
	}
}

int new_command_admin()
{
	system("pause");
	system("cls");
	printf(str_admin);

	// запрашиваем новую команду
	int commandd;
	scanf("%d", &commandd);
	return commandd;
}

void book_info(Books* books, int* liness, long long int isbn)
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
		
		printf("\nISBN книги\t\t - %lld\n", books[i].ISBN); 
		printf("Автор книги\t\t - %s\n", books[i].autor); 
		printf("Название книги\t\t - %s\n", books[i].book_name); 
		printf("Количество книг\t\t - %d\n", books[i].book_num_all); 
		printf("Книг у студентов\t - %d\n", books[i].available_books); 
		

		
		
		
	}
	else
	{
		printf("\nКниги c ISBN = %lld не существует\n\n", isbn);
	}
}

void student_info(Students* students, int* liness, char* zachetka)
{
	int k = 0;
	int i = 0;
	for (i; i < *liness; ++i)
	{
		if (str_cmp(students[i].zachetka, zachetka))
		{

			k = 1;
			break;
		}
	}

	if (k)
	{

		printf("\nНомер зачетки\t - %s\n", students[i].zachetka);
		printf("Фамилия\t\t - %s\n", students[i].surname);
		printf("Имя\t\t - %s\n", students[i].name);
		printf("Отчество\t - %s\n", students[i].patronymic);
		printf("Факультет\t - %s\n", students[i].faculty);
		printf("Специальность\t - %s\n", students[i].specialty);




		
	}
	else
	{
		printf("\nСтудента c номером зачетки = %s не существует\n\n", zachetka);
	}
}

void all_books_info(Books* books, int* lines)
{
	long long int* temp_arr = (long long int*)malloc(sizeof(long long int) * (*lines));
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


				printf("%9lld%30s%40s%20d%20d\n\n", books[g].ISBN, books[g].autor, books[g].book_name, books[g].book_num_all, books[g].available_books);
			}
		}

	}
}

void all_students_info(Students* students, int* lines)
{
	char z[] = "Номер зачетки";
	char fa[] = "Фамилия";
	char i[] = "Имя";
	char o[] = "Отчество";
	char f[] = "Факультет";
	char s[] = "Специальность";
	printf("\n\n%15s%15s%15s%15s%15s%50s\n\n", z, fa, i, o, f, s);
	for (int i = 0; i < *lines; ++i)
	{
		


		printf("%15s%15s%15s%15s%15s%50s\n\n", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);
			

	}
}

void change_book(Books* books, int* liness, long long int isbn)
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
		printf("\nВведите автора: ");
		char* temp = get_strng();
		strcpy(books[i].autor, temp);
		
		printf("\n\nВведите название книги: ");
		temp = get_strng();
		strcpy(books[i].book_name, temp);

		printf("\n\nВведите общее количество книг: ");
		scanf("%d", &(books[i].book_num_all));

		printf("\n\nВведите количество доступных книг: ");
		scanf("%d", &(books[i].available_books));
		
		rewriting(books, liness);
		printf("\n\nКнига успешно изменена!\n\n");
	}
	else
	{
		printf("\n\nКниги c ISBN = %lld не существует\n\n", isbn);
	}
}

void change_student(Students* students, int* liness, char* zachetka)
{
	int k = 0;
	int i = 0;
	for (i; i < *liness; ++i)
	{
		if (str_cmp(students[i].zachetka, zachetka))
		{

			k = 1;
			break;
		}
	}

	if (k)
	{
		
			printf("\nВведите фамилию: ");
			char* temp = get_strng();
			strcpy(students[i].surname, temp);
			
			printf("\nВведите имя: ");
			temp = get_strng();
			strcpy(students[i].name, temp);

			printf("\nВведите отчество: ");
			temp = get_strng();
			strcpy(students[i].patronymic, temp);

			printf("\nВведите факультет: ");
			temp = get_strng();
			strcpy(students[i].faculty, temp);

			printf("\nВведите специальность: ");
			temp = get_strng();
			strcpy(students[i].specialty, temp);
		
		


		rewriting_st(students, liness);
		printf("\nИнформация о студенте успешно изменена!\n\n");
	}
	else
	{
		printf("\nСтудента c номером зачетки = %s не существует\n\n", zachetka);
	}
}

void new_av_book(Books* books, int* liness, long long int isbn)
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
		printf("\nВведите новое количество доступных книг: ");
		int temp;
		scanf("%d", &(temp));
		if (temp > books[i].book_num_all)
		{
			printf("\n\nВведенное количество превышает количество книг в библиотеке\nПопробуйте еще раз!\n");
			new_av_book(books, liness, isbn);
		}
		else
		{
			books[i].available_books = temp;
			rewriting(books, liness);
			printf("\n\nКнига успешно изменена!\n\n");
		}
		
	}
	else
	{
		printf("\n\nКниги c ISBN = %lld не существует\n\n", isbn);
	}
}

Books_St* give_book(Books* books, Books_St* bks_st, Students* students, int* lines_bks_st, int* liness, int* lines_st, long long int isbn, char* zachetka)
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
		int h = 0;//есть ли студент в файле о студентах
		for (int v = 0; v < *lines_st; ++v)
		{
			if (str_cmp(students[v].zachetka, zachetka))
			{
				h = 1;
				break;
			}
		}

		int g = 1;
		int j = 0;
		for (j; j < *lines_bks_st; ++j)
		{
			if (bks_st[j].ISBN == isbn && str_cmp(bks_st[j].zachetka, zachetka))
			{

				g = 0;
				break;
			}
		}


		if (g && h) // если у студента еще нет этой книги то выдаем ее
		{
			if (books[i].available_books) //если кол-во доступных книг больше 0, то выдаем книгу
			{
				printf("\n\nВведите дату сдачи книги(дд.мм.гггг): ");
				char* date = get_strng();

				books[i].available_books--; 

				++ *lines_bks_st;
				bks_st = (Books_St*)realloc(bks_st, sizeof(Books_St) * (*lines_bks_st));
				strcpy(bks_st[*lines_bks_st - 1].zachetka, zachetka);
				strcpy(bks_st[*lines_bks_st - 1].date, date);
				bks_st[*lines_bks_st - 1].ISBN = isbn;

				rewriting_bks_st(bks_st, lines_bks_st);
				rewriting(books, liness);
				printf("\n\nКнига успешно выдана!\n\n");
			}
			else
			{
				printf("\n\nКниги c ISBN = %lld нет в наличии\n\n", isbn);// добавить дату ближайшей сдачи
			}
		}
		else
		{
			printf("\n\nУ студента с номером зачетки = %s уже есть эта книга или его не существует\n\n", zachetka);
		}
	}
	else
	{
		printf("\n\nКниги c ISBN = %lld не существует\n\n", isbn);
	}
	return bks_st;
}

Books_St* take_book(Books* books, Books_St* bks_st, int* lines_bks_st, int* liness, long long int isbn, char* zachetka)
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

		int g = 0;
		int j = 0;
		for (j; j < *lines_bks_st; ++j)
		{
			if (bks_st[j].ISBN == isbn && str_cmp(bks_st[j].zachetka, zachetka))
			{

				g = 1;
				break;
			}
		}
		if (g)
		{
			if (books[i].available_books + 1 <= books[i].book_num_all)// если доступных книг меньше или столько же сколько всего в библиотеке, то принимаем книгу
			{
				books[i].available_books++; 

				-- *lines_bks_st;// убираем одну строку 
				for (j; j < *lines_bks_st; ++j)
				{

					bks_st[j].ISBN = bks_st[j + 1].ISBN;
					strcpy(bks_st[j].zachetka, bks_st[j + 1].zachetka);
					strcpy(bks_st[j].date, bks_st[j + 1].date);
				}

				rewriting_bks_st(bks_st, lines_bks_st);
				rewriting(books, liness);
				printf("\n\nКнига успешно принята!\n\n");
			}
			else
			{
				printf("\n\nВсе книги c ISBN = %lld в наличии\n\n", isbn);
			}
		}
		else
		{
			printf("\n\nУ студента с номером зачетки = %s не было книги\n\n", zachetka);
		}
	}
	else
	{
		printf("\n\nКниги c ISBN = %lld не существует\n\n", isbn);
	}
	return bks_st;
}

void backup(Books* books, int* liness)
{
	FILE* backupp;
	char backup_name[100];

	time_t rawtime;
	struct tm* timeinfo;
	

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(backup_name, 100, "C:\\Users\\Александр\\Desktop\\books_backup\\Books  %Hч. %Mм. %Sс.  %m.%d.%Y.csv", timeinfo);
	
	
	
	
	backupp = fopen(backup_name, "w");

	for (int i = 0; i < *liness && books[i].ISBN > 0; ++i)// books[i].ISBN > 0 - если менять файл в exel, то появляется невидимая строка, из-за которой *lines получается на 1 больше действительного
	{
		if (*liness - i - 1 && books[i + 1].ISBN > 0)
			fprintf(backupp, "%lld;%s;%s;%d;%d\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
		else
			fprintf(backupp, "%lld;%s;%s;%d;%d", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);


	}

	fclose(backupp);
	printf("\nБэкап выполнен успешно!\n\nПуть к файлу бэкапа: %s\n\n", backup_name);
}

void backup_st(Students* students, int* liness)
{
	FILE* backupp;
	char backup_name[100];

	time_t rawtime;
	struct tm* timeinfo;


	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(backup_name, 100, "C:\\Users\\Александр\\Desktop\\students_backup\\Students  %Hч. %Mм. %Sс.  %m.%d.%Y.csv", timeinfo);




	backupp = fopen(backup_name, "w");

	for (int i = 0; i < *liness && students[i].zachetka[0] > 0; ++i)// books[i].ISBN > 0 - если менять файл в exel, то появляется невидимая строка, из-за которой *lines получается на 1 больше действительного
	{
		if (*liness - i - 1 && students[i + 1].zachetka[0] > -1)
			fprintf(backupp, "%s;%s;%s;%s;%s;%s\n", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);
		else
			fprintf(backupp, "%s;%s;%s;%s;%s;%s", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);


	}

	fclose(backupp);
	printf("\nБэкап выполнен успешно!\n\nПуть к файлу бэкапа: %s\n\n", backup_name);

}

Books* restore_backup( int* liness)
{
	char* temp_name = file_name;
	file_name = get_strng();
	Books* books = start(liness);//	должно возвращать указатель 

	file_name = temp_name;
	rewriting(books, liness);

	printf("\nБэкап успешно выполнен!\n\n");
	return books;
}

Students* restore_backup_st(int* liness)
{
	char* temp_name = file_name_students;
	file_name_students = get_strng();
	Students* students = start_st(liness);

	file_name_students = temp_name;
	rewriting_st(students, liness);

	printf("\nБэкап успешно выполнен!\n\n");
	return students;
}

void find_autor(Books* books, int* lines, int i = 0, char* autor = NULL)
{
	if (!i) { autor = get_strng(); }// если ф-ция вызвана 1й раз, то запрашиваем ввод автора, далее автор известен

	int k = 0;
	int z = i;// если функция вызвана впервые и автор не найден, то выведется сообщение, иначе сообщение не верно
	int res;
	for (i; i < *lines; ++i)
	{
		res = str_cmp(books[i].autor, autor);
		if (res )//books[i].autor == autor
		{

			k = 1;
			break;
		}
	}

	if (k)
	{
		printf("\n_________________________________________\nISBN - %lld\n\nАвтор книги - %s\n\nНазвание книги - %s\n\nВсего книг - %d\n\nКниг доступно - %d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
		find_autor(books, lines, i + 1, autor);// i + 1, тк нужно продолжить поиск со след элемента
	}
	else if(!z)
	{
		printf("\n\nКниги c автором = %s не существует\n\n", autor);
	}
}

void find_student(Students* students, int* lines, int i = 0, char* surname = NULL)
{
	if (!i) { surname = get_strng(); }// если ф-ция вызвана 1й раз, то запрашиваем ввод автора, далее автор известен

	int k = 0;
	int z = i;// если функция вызвана впервые и автор не найден, то выведется сообщение, иначе сообщение не верно
	int res;
	for (i; i < *lines; ++i)
	{
		res = str_cmp(students[i].surname, surname);
		if (res)//books[i].autor == autor
		{

			k = 1;
			break;
		}
	}

	if (k)
	{
		printf("\n_________________________________________\nНомер зачетки - %s\n\nФамилия - %s\n\nИмя - %s\n\nОтчетсво - %s\n\nФакультет - %s\n\nСпециальность - %s\n\n", students[i].zachetka, students[i].surname, students[i].name, students[i].patronymic, students[i].faculty, students[i].specialty);
		find_student(students, lines, i + 1, surname);// i + 1, тк нужно продолжить поиск со след элемента
	}
	else if (!z)
	{
		printf("\n\nСтудента c фамилией = %s не существует\n\n", surname);
	}
}

void student_bks_info(Books* books, Students* students, Books_St* bks_st, int* lines_bks_st, int* liness_st, int* lines, char* zachetka)
{
	if (!zachetka_exist(students, *liness_st, zachetka))
	{
		int z =	1;
		for (int i = 0; i < *lines_bks_st; ++i)
		{
			if (str_cmp(bks_st[i].zachetka, zachetka))
			{
				printf("\n______________________________________________");
				book_info(books, lines, bks_st[i].ISBN);
				printf("\nДата сдачи в библиотеку\t - %s\n\n", bks_st[i].date);
				// продолжить отсюда
				z = 0;
			}
		}
		if (z)
		{
			printf("\nКниг у этого студента не найдено\n\n");
		}
	}
	else
	{
		printf("\nСтудента с зачеткой = %s не существует\n\n", zachetka);
	}
}

void bks_student_info(Books* books, Students* students, Books_St* bks_st, int* lines_bks_st, int* liness_st, int* lines, long long int isbn)
{
	if (!isbn_exist(books, *lines, isbn))
	{
		int z = 1;
		for (int i = 0; i < *lines_bks_st; ++i)
		{
			if (bks_st[i].ISBN == isbn)
			{
				printf("\n______________________________________________");
				student_info(students, liness_st, bks_st[i].zachetka);
				printf("\nДата сдачи в библиотеку\t - %s\n\n", bks_st[i].date);
				// продолжить отсюда
				z = 0;
			}
		}
		if (z)
		{
			printf("\nСтудентов с этой книгой не найдено\n\n");
		}
	}
	else
	{
		printf("\nКниги с ISBN = %lld не существует\n\n", isbn);
	}
}

int permission(Users* users, int* liness , int* stptr, int* bksptr)
{
	system("pause");
	system("cls");
	printf("Введите логин: ");
	char* login = get_strng();
	
	


	int k = 0;
	int i = 0;
	for (i; i < *liness; ++i)
	{
		if (str_cmp(users[i].login, login))
		{

			k = 1;
			break;
		}
	}

	if (k)
	{
		
		printf("\n\nВведите пароль(если забыли, введите \"-1\"): ");
		char* password = get_strng();
		char a[] = "-1";
		while (!(str_cmp(users[i].password, password) || str_cmp(password, a)))
		{
			printf("\n\nВведенный пароль неверный, повторите попытку(если забыли, введите \"-1\"): ");
			password = get_strng();
		}

		if (str_cmp(password, a))
		{
			system("cls");
			printf("\n\nПовторите попытку авторизации\n\n ");
			permission(users, liness, stptr, bksptr);
		}
		else
		{
			system("cls");
			printf("Вы успешно авторизовались под логином \"%s\"\n\n", login);
			*stptr = users[i].students;
			*bksptr = users[i].books;

		}
		return k;
	}
	else
	{
		printf("\nПользователя с логином = \"%s\" не существует\n\nПовторите попытку...\n\n", login);
		return k;
	}
}



Books* books; // тк Command не возвращает указатель 
Students* students; // тк Command не возвращает указатель 
Users* users; // тк Command не возвращает указатель 
Books_St* bks_st;


int Command(int command, int* lines_bks_st, int* lines_st, int* lines, int i = 1)
{
	if (command == 1)
	{
		printf("\nВведите ISBN новой книги: ");
		long long int isbn;
		scanf("%lld", &isbn);
		isbn_new(books, lines, isbn);

	}
	else if (command == 2)
	{
		printf("\nВведите ISBN для удаления книги: ");
		long long int isbn;
		scanf("%lld", &isbn);
		delete_book(books,bks_st, lines_bks_st, lines, isbn);
		
			
	
			
		
	}
	else if (command == 3)
	{
		printf("\nВведите ISBN для получения информации по книге: ");
		long long int isbn;
		scanf("%lld", &isbn);
		book_info(books, lines, isbn);


		
	}
	else if (command == 4)
	{
		all_books_info(books, lines);
		


		
	}
	else if (command == 5)
	{
		printf("\nВведите ISBN для редактирования информации о книге: ");
		long long int isbn;
		scanf("%lld", &isbn);
		change_book(books, lines, isbn);


		
	}
	else if (command == 6)
	{
		printf("\nВведите ISBN для редактирования информации информации о книге: ");
		long long int isbn;
		scanf("%lld", &isbn);
		new_av_book(books, lines, isbn);



		
	}
	else if (command == 7)
	{
		printf("\nВведите ISBN для выдачи книги: ");
		long long int isbn;
		scanf("%lld", &isbn);

		printf("\nВведите номер зачетки для выдачи книги: ");
		char* zachetka = get_strng();

		bks_st = give_book(books, bks_st, students, lines_bks_st, lines, lines_st, isbn, zachetka);


		
	}
	else if (command == 8)
	{
		printf("\nВведите ISBN для cдачи книги: ");
		long long int isbn;
		scanf("%lld", &isbn);

		printf("\nВведите номер зачетки для cдачи книги: ");
		char* zachetka = get_strng();


		take_book(books, bks_st, lines_bks_st, lines, isbn, zachetka);


		
	}
	else if (command == 9)
	{
		backup(books, lines);


		
	}
	else if (command == 10)
	{
		printf("\nВведите путь к файлу бэкапа: ");
		books = restore_backup(lines);
		


	}
	else if (command == 11)
	{
		printf("\nВведите автора/авторов книги: ");
		find_autor(books, lines);



		
	}
	else if (command == 12)
	{
		printf("\nВведите номер ISBN для получении информации о студентах с этой книгой: ");
		long long int isbn;
		scanf("%lld", &isbn);

		bks_student_info(books, students, bks_st, lines_bks_st, lines_st, lines, isbn);
	}
	else
	{
		printf("\nТакой команды не существует\n");


		
		
	}

	return new_command(i);
}

int Command_st(int command, int* lines_bks_st, int* lines, int* lines_bks, int i = 1)
{
	if (command == 1)
	{
		printf("\nВведите номер зачетки нового студента: ");
		char* zachetka = get_strng();
		
		zachetka_new(students, lines, zachetka);

		
	}
	else if (command == 2)
	{
		printf("\nВведите номер зачетки для удаления студента: ");
		char* zachetka = get_strng();

		delete_student(students, bks_st, lines_bks_st, lines, zachetka);


		


	}
	else if (command == 3)
	{
		printf("\nВведите номер зачетки для редактирования информации о студенте: ");
		char* zachetka = get_strng();

		change_student(students, lines, zachetka);


		
	}
	else if (command == 4)
	{
		all_students_info(students, lines);



		
	}
	else if (command == 5)
	{
		printf("\nВведите номер зачетки для получении информации о студенте: ");
		char* zachetka = get_strng();

		student_info(students, lines, zachetka);


		
	}
	else if (command == 6)
	{
		backup_st(students, lines);
		



		
	}
	else if (command == 7)
	{
		printf("\nВведите путь к файлу бэкапа: ");
		students = restore_backup_st(lines);


		
	}
	else if (command == 8)
	{
		printf("\nВведите фамилию студента для поиска: ");
		find_student(students, lines);


		
	}
	else if (command == 9)
	{
		printf("\nВведите номер зачетки для получении информации о книгах студента: ");
		char* zachetka = get_strng();

		student_bks_info(books, students, bks_st, lines_bks_st, lines, lines_bks, zachetka);
	}
	else
	{
		printf("\nТакой команды не существует\n");



		
	}

	return new_command_st(i);
}

int Command_admin(int command, int* lines_bks_st, int* lines, int* lines_st)
{

	if (command == 1)// меню студентов
	{
		int command_st = new_command_st(0);
		if (!command_st) return 0;
		
		while (command_st != -1) 
		{ 
			command_st = Command_st(command_st, lines_bks_st, lines_st, lines, 0);
			if (!command_st) return 0;
		}
	}
	else if (command == 2) // меню книг
	{
		int commandd = new_command(0);
		if (!commandd) return 0;

		while (commandd != -1)
		{
			commandd = Command(commandd, lines_bks_st, lines_st, lines, 0);
			if (!commandd) return 0;
		}
	}
	else
	{
		printf("\n\nТакой команды не существует!");
	}
	return new_command_admin();
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	

	printf("Введите имя файла с информацией о книгах: ");
	file_name = get_strng();
	
	printf("\n\nВведите имя файла с информацией о студентах: ");
	file_name_students = get_strng();

	printf("\n\nВведите имя файла с информацией о пользователях: ");
	file_name_usr = get_strng();

	printf("\n\nВведите имя файла с информацией о студентах и книгах: ");
	file_name_bks_st = get_strng();

	int* lines = (int*)malloc(sizeof(int));// колво строк в файле о книгах

	int* lines_st = (int*)malloc(sizeof(int));// колво строк в файле о студентах

	int* lines_usr = (int*)malloc(sizeof(int));// колво строк в файле о юзерах
	
	int* lines_bks_st = (int*)malloc(sizeof(int));// колво строк в файле о студентах и книгах


	int bks, * bksptr = &bks; // права на доступ к изменению и чтению файлов
	int st, * stptr = &st;


	while ((books = start(lines)) == NULL || (students  = start_st(lines_st)) == NULL || (users = start_usr(lines_usr)) == NULL || (bks_st = start_bks_st(lines_bks_st)) == NULL)
	{
		printf("Введите имя файла : ");
		file_name = get_strng();

		printf("\n\nВведите имя файла с информацией о студентах: ");
		file_name_students = get_strng();
		
		printf("\n\nВведите имя файла с информацией о пользователях: ");
		file_name_usr = get_strng();

		printf("\n\nВведите имя файла с информацией о студентах и книгах: ");
		file_name_bks_st = get_strng();
	}
	
	
	while(!permission(users, lines_usr, stptr, bksptr)){}

	if (bks && st)
	{
		int command = new_command_admin();

		while (command) { command = Command_admin(command, lines_bks_st, lines, lines_st); }
	}
	else if (bks)
	{
		//считываем команду
		int command = new_command();

		while (command) { command = Command(command, lines_bks_st, lines_st, lines); }
	}
	else if (st)
	{
		//считываем команду
		int command_st = new_command_st();

		while (command_st) { command_st = Command_st(command_st, lines_bks_st, lines_st, lines); }
	}

	
	

	_putch('\n');
	system("pause");
	return 0;
}
