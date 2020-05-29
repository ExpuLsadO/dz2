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
char str[500] = "0 - завершить работу программы\n1 - добавить новую книгу\n2 - удалить книгу\n3 - просмотр всей информации по книге\n4 - вывести информацию по всем книгам в виде таблицы\n5 - редактировать информацию по книге\n6 - изменить количество доступных книг в библиотеке\n7 - выдать книгу студенту\n8 - принять книгу от студента\n9 - cделать бэкап\n10 - восстановить базу из файла бэкапа\n11 - поиск по фамилии автора\n\nВведите команду: ";


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

Books* start(int* lines)
{
	

	

	// открываем файл (если не открылся - завершаем прогу)
	if (!(filee = fopen(file_name, "r+")))
	{
		perror("fopen");
		system("pause");
		return NULL;
	}


	// кол-во строк в файле
	int liness = str_count(filee);
	*lines = liness;


	// выделяем память под массив структур по кол-ву строк в файле
	Books* books = (Books*)malloc(sizeof(Books) * liness);



	//считываем данные из файла в структуру
	for (int i = 0; i < liness; ++i)
	{
		fscanf(filee, "%d;%[^;];%[^;];%d;%d", &(books[i].ISBN), books[i].autor, books[i].book_name, &(books[i].book_num_all), &(books[i].available_books));

		//удалить на релизе 
		//printf("%d\n%s\n%s\n%d\n%d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
	}
	fseek(filee, 0, 0); //перемещаем курсор в начало строки

	return books;
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

	for (int i = 0; i < *lines && books[i].ISBN > 0; ++i)// books[i].ISBN > 0 - если менять файл в exel, то появляется невидимая строка, из-за которой *lines получается на 1 больше действительного
	{
		if (*lines - i - 1 && books[i+1].ISBN > 0)
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
	printf(str);

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

void change_book(Books* books, int* liness, int isbn)
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
		printf("\n\nКниги c ISBN = %d не существует\n\n", isbn);
	}
}

void new_av_book(Books* books, int* liness, int isbn)
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
		printf("\n\nКниги c ISBN = %d не существует\n\n", isbn);
	}
}

void give_book(Books* books, int* liness, int isbn)
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
		if (books[i].available_books)
		{
			books[i].available_books--; //если кол-во доступных книг больше 0, то выдаем книгу

			rewriting(books, liness);
			printf("\n\nКнига успешно выдана!\n\n");
		}
		else
		{
			printf("\n\nКниги c ISBN = %d нет в наличии\n\n", isbn);
		}

	}
	else
	{
		printf("\n\nКниги c ISBN = %d не существует\n\n", isbn);
	}
}

void take_book(Books* books, int* liness, int isbn)
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
		if (books[i].available_books + 1 <= books[i].book_num_all)
		{
			books[i].available_books++; // если доступных книг меньше или столько же сколько всего в библиотеке, то принимаем книгу

			rewriting(books, liness);
			printf("\n\nКнига успешно принята!\n\n");
		}
		else
		{
			printf("\n\nВсе книги c ISBN = %d в наличии\n\n", isbn);
		}

	}
	else
	{
		printf("\n\nКниги c ISBN = %d не существует\n\n", isbn);
	}
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
			fprintf(backupp, "%d;%s;%s;%d;%d\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
		else
			fprintf(backupp, "%d;%s;%s;%d;%d", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);


	}

	fclose(backupp);
	printf("\nБэкап выполнен успешно!\n\nПуть к файлу бэкапа: %s\n\n", backup_name);
}

void restore_backup(Books* books, int* liness)
{
	char* temp_name = file_name;
	file_name = get_strng();
	books = start(liness);

	file_name = temp_name;
	rewriting(books, liness);

	printf("\nБэкап успешно выполнен!\n\n");
}

int str_cmp(char* a, char* b)
{
	int k = 1;
	for(int i = 0; a[i] != '\0' || b[i] != '\0'; ++i)
	{
		if (a[i] != b[i]) 
		{
			k = 0;
			break;
		}
	}
	return k;
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
		printf("\n_________________________________________\nISBN - %d\n\nАвтор книги - %s\n\nНазвание книги - %s\n\nВсего книг - %d\n\nКниг доступно - %d\n\n", books[i].ISBN, books[i].autor, books[i].book_name, books[i].book_num_all, books[i].available_books);
		find_autor(books, lines, i + 1, autor);// i + 1, тк нужно продолжить поиск со след элемента
	}
	else if(!z)
	{
		printf("\n\nКниги c автором = %s не существует\n\n", autor);
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
	else if (command == 5)
	{
		printf("\nВведите ISBN для редактирования информации информации о книге: ");
		int isbn;
		scanf("%d", &isbn);
		change_book(books, lines, isbn);


		return new_command();
	}
	else if (command == 6)
	{
		printf("\nВведите ISBN для редактирования информации информации о книге: ");
		int isbn;
		scanf("%d", &isbn);
		new_av_book(books, lines, isbn);



		return new_command();
	}
	else if (command == 7)
	{
		printf("\nВведите ISBN для выдачи книги: ");
		int isbn;
		scanf("%d", &isbn);
		give_book(books, lines, isbn);


		return new_command();
	}
	else if (command == 8)
	{
		printf("\nВведите ISBN для сдачи книги: ");
		int isbn;
		scanf("%d", &isbn);
		take_book(books, lines, isbn);


		return new_command();
	}
	else if (command == 9)
	{
		backup(books, lines);


		return new_command();
	}
	else if (command == 10)
	{
		printf("\nВведите путь к файлу бэкапа: ");
		restore_backup(books, lines);
		


		return new_command();
	}
	else if (command == 11)
	{
		printf("\nВведите автора/авторов книги: ");
		find_autor(books, lines);



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
	

	
	 
	
	


	printf("Введите имя файла : ");
	file_name = get_strng();


	/*КУЧА КОДА ИЗ МЭЙНА, КОТОРАЯ НУЖНА ДЛЯ 10Й КОМАНДЫ*/
	int* lines = (int*)malloc(sizeof(int));
	Books* books = start(lines);


	//считыавем команду
	int command = new_command();

	while (command) { command = Command(command, books, lines); }
	

	_putch('\n');
	system("pause");
	return 0;
}
