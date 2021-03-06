
#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std; 
int compare(const void * x1, const void * x2); // компаратор 

struct Edje
{
	char a;		
	char b;		
	int  c;		
};

class Graph
{
private:
	int size;			
	Edje *c;			

	bool way(Edje * f, Edje * cf, char beg, char end);
	bool way_to_end(char * b, Edje * cf, char beg, char end, int &min);

	void print(Edje *c, char beg);

public:
	Graph(int size, istream &in);
	~Graph();

	void print();


	void Ford_Fulkerson(char beg, char end);

};


// Конструктор
Graph::Graph(int size, istream &in) : size(size), c(size ? new Edje[size] : NULL)
{
	for (int i = 0; i < size; i++)
	{
		in >> c[i].a >> c[i].b >> c[i].c;
	}

	qsort(c, size, sizeof(Edje), compare);
}

// Деструктор
Graph::~Graph()
{
	delete[] c;
}




// Пуск Форда-Фалкрисона
void Graph::Ford_Fulkerson(char beg, char end)
{
	Edje * f = new Edje[size];		
	Edje *cf = new Edje[size];		

										
	for (int i = 0; i < size; i++)
	{
		f[i].a = cf[i].a = c[i].a;
		f[i].b = cf[i].b = c[i].b;

		f[i].c = 0;
		cf[i].c = c[i].c;
	}

	// Повторять пока не закончатся пути в сток
	while (way(f, cf, beg, end));


	print(f, beg);

	delete[] f;
	delete[] cf;
}


// Нахождение пути в остаточной сет
bool Graph::way(Edje * f, Edje * cf, char beg, char end)
{
	// Какие рёбра задействованы в найденном пути
	char *b = new char[size]();

	int r;

	int min = INT_MAX;


	if (!way_to_end(b, cf, beg, end, min))
	{
		delete[] b;
		return false;
	}

	
	for (int i = 0; i < size; i++)
	{
		// Если ребро принадлежит пути - изменяем поток по этому ребру
		if (b[i] == 1)
		{
			f[i].c += min;
			cf[i].c = c[i].c - f[i].c;
		}
	}

	delete[] b;
	return true;
}


// Нахождение пути от beg до end в остаточной сети
bool Graph::way_to_end(char * b, Edje * cf, char beg, char end, int &min)
{
	if (beg == end) return true;

	// "Адрес" начала наора ребер с истоком beg
	int r;
	for (r = 0; r < size; r++)
	{
		if (cf[r].a == beg) break;
	}

	// Если из вершины beg можем  попасть в end
	for (int i = r; i < size, cf[i].a == beg; i++)
	{
		if (cf[i].b == end && cf[i].c)
		{
			b[i] = 1;

			min = cf[i].c < min ? cf[i].c : min;
			return true;
		}
	}

	// Проверяем данный набор
	for (int i = r; i < size, cf[i].a == beg; i++)
	{
		// Если сквозь остаточное ребро ещё можно что-то пустить
		if (cf[i].c && b[i] >= 0)
		{
			// Помечаем, по каким ребрам нельзя ходить ввиду посещенности вершины 
			for (int j = 0; j < size; j++)
			{
				if (cf[j].b == cf[i].a && !b[j])
					b[j] = -1;
			}


			// Если путь с использованием этого ребра существует
			if (way_to_end(b, cf, cf[i].b, end, min))
			{
				b[i] = 1;
				min = cf[i].c < min ? cf[i].c : min;
				return true;
			}
			b[i] = -1;
		}
	}

	return false;
}

int main()
{
	ifstream fin("IN.txt");

	int c;
	char a, b;

	fin >> c >> a >> b;
	Graph qw(c, fin);
	qw.Ford_Fulkerson(a, b);
	return 0;
}
int compare(const void * x1, const void * x2)   
{
	int c = (*(Edje*)x1).a - (*(Edje*)x2).a;

	if (c)
		return c;

	return (*(Edje*)x1).b - (*(Edje*)x2).b;
}

void Graph::print()
{
	for (int i = 0; i < size; i++)
	{
		cout << c[i].a << " " << c[i].b << " " << c[i].c << "\n";
	}
}



void Graph::print(Edje *c, char beg)
{
	int qq = 0;
	int r;
	for (r = 0; r < size; r++)
	{
		if (c[r].a == beg) break;
	}


	for (int i = r; i < size; i++)
	{
		if (c[i].a != beg) break;

		qq += c[i].c;
	}

	cout << qq;

	for (int i = 0; i < size; i++)
	{
		cout << "\n" << c[i].a << " " << c[i].b << " " << c[i].c;
	}
}