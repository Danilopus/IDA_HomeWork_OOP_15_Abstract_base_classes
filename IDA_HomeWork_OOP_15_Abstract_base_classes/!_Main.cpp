// HomeWork template project v 6.0 // 27.06.2023 //

/*

Наследование - абстрактные классы

Задание

Cоздать базовые классы для растений(Plants) и плодов(Harvest) 

Класс плода должен предоставлять возможность пользователю:
узнавать своё название(задаётся при создании)
узнавать свой вес и цвет(также можно задать при создании)

Базовый класс растения должен знать какой у него размер
(большой, маленький, средний), цвет, сколько на нём может быть плодов.

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


//Task 1 Friut
void Task_1(std::string name_of_task)
{	
	//*
	do
	{		
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";					
	
		TreeLocation Location_1(3);
		BackPack main_back_pack;

		Location_1.ShowTrees();

		
		
		
		
		
		
		//Функции фабрики выполняет класс TreeLocation через метод 
		//	void Get_fruit(int tree_index, BackPack_Player_Interface* back_pack)

		int tree_index = 0;

		Location_1.Get_fruit(tree_index, &main_back_pack);



		
		//Fruit fruit_obj("apple", 0.2, Color::red);
		//fruit_obj.Info();


	
		//Base_Fruit* fruit_obj_ptr = &fruit_obj;
		//fruit_obj_ptr->Get_name();



		std::cout << "\n\nEsc - exit | any key to continue";
	} while (_getch() != 27);//*/
}

//Task 2 
void Task_2(std::string name_of_task)

{
	//*
	do
	{
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";

		BackPack main_back_pack;
		TreeLocation Location_2(5);

		// Player interface
		std::cout << "\n\n\n// Player interface\n";
		BackPack_Player_Interface* BackPack_Player_Interface_ptr = &main_back_pack;

		std::cout << "\nEmpty BackPack -> Info()\n";
		BackPack_Player_Interface_ptr->Info();

		std::cout << "\n\nLocation_2.ShowTrees()";
		Location_2.ShowTrees();

		std::cout << "\n\n\nBackPack after harvesting Trees 1, 2 and 3 -> Info()";

		// почему так?
		// Error(active)	E3364	operator -> or ->*applied to "MotherPlant" instead of to a pointer type	 
		//BackPack_Player_Interface_ptr->AddItem((Location_2[0])->Get_fruit());

		BackPack_Player_Interface_ptr->AddItem(*Location_2[0].Get_fruit());
		BackPack_Player_Interface_ptr->AddItem(*Location_2[1].Get_fruit());
		BackPack_Player_Interface_ptr->AddItem(*Location_2[2].Get_fruit());
		BackPack_Player_Interface_ptr->Info();

		std::cout << "\n\n\nBackPack after deleting 1 item -> Info()";
		BackPack_Player_Interface_ptr->DeleteItem();
		BackPack_Player_Interface_ptr->Info();


		// TheGame interface
		std::cout << "\n\n\n// TheGame interface\nInfo() method only";
		BackPack_TheGame_Interface* BackPack_TheGame_Interface_ptr = &main_back_pack;

		BackPack_TheGame_Interface_ptr->Info();


		std::cout << "\n\nEsc - exit | any key to continue";
	} while (_getch() != 27);//*/
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
	MainMenu.AddElement("Fruit and derrives class demo through Base classes interfaces");
	MainMenu.AddElement("BackPack class demo through differents interfaces:\nInterface 1: Player\nInterface 2: Game");

	//MainMenu.AddElement("XXX");

	do 
	{		
		MainMenu.Show_menu();
		if (!MainMenu.User_Choice_Handle(_getch()))	break;
	} while (true);
	return 0;
}

