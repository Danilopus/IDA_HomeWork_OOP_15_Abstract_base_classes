// HomeWork template project v 6.0 // 27.06.2023 //

/*

Наследование - абстрактные классы

Задание

Cоздать базовые классы для растений(Plants) и плодов(Harvest) 

Класс плода должен предоставлять возможность пользователю:
- узнавать своё название(задаётся при создании)
- узнавать свой вес и цвет(также можно задать при создании)

Базовый класс растения должен знать какой у него
- размер (большой, маленький, средний), 
- цвет, 
- сколько на нём может быть плодов.

Создайте конкретных наследников для класса растения. Пример (яблоня, груша, малина,
ежевика). Которые связаны со своими наследниками класса плод и которые возвращают
плоды пока они есть на дереве через виртуальный метод базового класса (модель паттерна
фабричный метод)

В функции main продемонстрировать возможность работы с классами.
``` задание сдаётся в виде текстового документа с иллюстрациями либо в виде файла -
изображения диаграммы, с пояснениями

*/

#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include <conio.h>
//My own headers
#include "Service functions.h"
#include "MainMenu.h"
#include "Location.h"
#include "BackPack.h"



// Homework OOP 15 ----------------------------------------------------	


//Task 1 Base_MotherPlant
void Task_1(std::string name_of_task)
{	
	do
	{		
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";					
	
		//Функции фабрики выполняет класс TreeLocation через:
		//  1. TreeLocation(int trees_number) - конструктор создания контейнера с рандомными деревьями
		//	2. void Get_fruit(int tree_index, BackPack_Player_Interface* back_pack) - метод сбора плодов, связывающий Классы Fruit, MohterPlant и BackPack


		//создаем локацию с 5 рандомными деревьями		
		TreeLocation Location_1(5);
		//также создаем рюкзак, потому что логика функции сбора фруктов подразумевает
		//обязательное наличие рюкзака, в который перемещаются собранные фрукты:
		//void Get_fruit(int tree_index, BackPack_Player_Interface * back_pack)
		BackPack main_back_pack;
						
		
		//Осмотримся методами непосредственно объекта (используя сокращенное описание локации)
		std::cout << "\n--- Location_1.ShowTrees():";
		Location_1.ShowTrees();
						
		//Теперь осмотримся виртуальными методами, унаследованными от Base_MotherPlant
		std::cout << "\n\n\n--- Show methods through Base_MotherPlant* pointer:";
		for (int tree_index = 0; tree_index < Location_1.size(); ++tree_index)
		{
			//задаем указатель по очереди на каждое дерево в локации
			Base_MotherPlant* tree_ptr = &Location_1[tree_index];
			//Воспользуемся всеми методами, которые предоставляет Base_MotherPlant:
			//может показаться странным, но по заданию в базовом классе не предусмотрен Get_name() - поэтому названий нет
			std::cout << "\n\nTree: " << tree_index + 1;
			std::cout << "\n     Color: " << tree_ptr->Get_color();
			std::cout << "\n      Size: " << tree_ptr->Get_size();
			std::cout << "\nMax fruits: " << tree_ptr->Get_max_fruits();
		}

		std::cout << "\n\nEsc - exit | any key to continue";
	} while (_getch() != 27);
}

//Task 2 Base_Friut
void Task_2(std::string name_of_task)

{
	do
	{
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";

		
		BackPack main_back_pack;
		TreeLocation Location_2(5);

		std::cout << "\n--- Location_2.ShowTrees():";
		Location_2.ShowTrees();
		

		Base_MotherPlant* tree_ptr = &Location_2[0];
		//Сорвем с Дерева 1 плод: 
		Base_Fruit* base_fruit_ptr = tree_ptr->Get_fruit();
		//опросим его методами класса Base_Fruit
		std::cout << "\n\n--- Base_Fruit methods through class pointer";
		std::cout << "\n\nName: " << base_fruit_ptr->Get_name();
		std::cout << "\nweight: " << base_fruit_ptr->Get_weight();
		std::cout << "\n color: " << base_fruit_ptr->Get_color();
		//Уберем сорванный плод в рюкзак (используя dynamic_cast, потому что backpack хранит указатели Fruit* и не принимает указатель Base_Fruit*)
		//main_back_pack.AddItem(base_fruit_ptr); // Error(active)	E0167	argument of type "Base_Fruit *" is incompatible with parameter of type "Fruit *"
		Fruit* fruit_ptr = dynamic_cast<Fruit*>(base_fruit_ptr);
		main_back_pack.AddItem(fruit_ptr);


		//Переходим к сбору урожая
		//соберем все плоды с дерева 1 и дерева 2 и 100 (или все) с дерева 3
		std::cout << "\n\nTree 1 & Tree 2 full harvesting, Tree 3 - 100 fruit (or all) harvesting";

		//Собираем все плоды с Деревьев 1 и 2. 
		//Вообще в классе TreeLocation есть метод Get_fruit(tree_index, &back_pack) который делает сбор плодов и укладку в рюкзак
		//но в целях демонстрации работы через виртуальные методы абстрактных базовых классов сделан этот код ниже:
		int tree_index = 1;		
		while (tree_index>=0)
		{
			tree_ptr = &Location_2[tree_index];
			for (int i = 0; i < Location_2[tree_index].Get_max_fruits(); ++i)
			{
				base_fruit_ptr = tree_ptr->Get_fruit();
				main_back_pack.AddItem(dynamic_cast<Fruit*>(base_fruit_ptr));
			}
			--tree_index;
		}
		//Собираем 100 плодов с Дерева 3
		tree_index = 2;
			tree_ptr = &Location_2[tree_index];
			for (int i = 0; i < 100; ++i)
			{
				base_fruit_ptr = tree_ptr->Get_fruit();
				main_back_pack.AddItem(dynamic_cast<Fruit*>(base_fruit_ptr));
			}
		


		//Осмотрим локацию после сбора урожая
		std::cout << "\n\n--- Location_2.ShowTrees():";
		Location_2.ShowTrees();

		//Получим короткую сводку по рюкзаку
		std::cout << "\n\n--- main_back_pack.ShortInfo():\n";
		main_back_pack.ShortInfo();


		//Получим полную сводку по рюкзаку
		std::cout << "\n\n\nGet ready to watch full BackPack info!";
		_getch();
		main_back_pack.Info();



//Fruit fruit_obj("apple", 0.2, Color::red);
//fruit_obj.Info();



//Base_Fruit* fruit_obj_ptr = &fruit_obj;
//fruit_obj_ptr->Get_name();



		std::cout << "\n\nEsc - exit | any key to continue";
	} while (_getch() != 27);
}

//Task 3 
void Task_3() {}

//Task 4
void Task_4() {}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	srand(time(NULL));
	//setlocale(LC_CTYPE, "Russian");
	//system("mode con cols=60 lines=40"); 
	Main_menu MainMenu;	
	MainMenu.AddElement("OOP Home Work 15: Abstract base classes");	// Homework name
	MainMenu.AddElement("MotherPlant and derrives classes demo through abstract Base_MotherPlant class interface");
	MainMenu.AddElement("Fruit and derrives classes demo through abstract Base_Fruit class interface");

	do 
	{		
		MainMenu.Show_menu();
		if (!MainMenu.User_Choice_Handle(_getch()))	break;
	} while (true);
	return 0;
}

