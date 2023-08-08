#pragma once
#include <vector>
#include "MotherPlant.h"
#include "Service functions.h"
#include "AppleTree.h"
#include "Raspberry_bush.h"
#include "BackPack.h"
#include "PearTree.h"

#include "Fruit.h"




class Location_Player_Interface
{
public:
	virtual ~Location_Player_Interface() {}; // надо ли объявлять вирутальный деструктор при витруальном наследовании?
	virtual void ShowTrees() = 0;
	virtual void Get_fruit(int tree_index, BackPack_Player_Interface* back_pack) = 0;
};

class Location_TheGame_Interface
{
public:
	virtual ~Location_TheGame_Interface() {}; // надо ли объявлять вирутальный деструктор при витруальном наследовании?
	virtual MotherPlant* AddNewTree() = 0;
	virtual void DeleteTree() = 0;
};

class TreeLocation : virtual public Location_TheGame_Interface, virtual public Location_Player_Interface
{
	std::vector<MotherPlant*> _plants_list;
public:
	TreeLocation(int trees_number)
	{
		MotherPlant* new_tree = nullptr;
		for (int i = 0; i < trees_number; i++)
		{
			int size = Get_Random(0, 3);

			enum treeTypes {Apple, Raspberry, Pear, _end_of_list};

			Color parametr = static_cast<Color>(Get_Random(0,int(Color::_end_of_enum_)));
			
			double max_fruits = Get_Random(20 * (size+1), 50 * (size+1));
			
			int random_tree_choice = Get_Random(0, treeTypes(_end_of_list));

			switch (random_tree_choice)
			{
			case 0:  new_tree = new AppleTree(size, parametr, max_fruits); break;
			case 1:  new_tree = new Raspberry_bush(size, parametr, max_fruits); break;
			case 2:  new_tree = new PearTree(size, parametr, max_fruits); break;
			}

			_plants_list.push_back(new_tree);
		}
	}
	~TreeLocation()
	{
		for (int i = 0; i < _plants_list.size(); i++)
			delete _plants_list[i];
		_plants_list.clear();
	}

	MotherPlant* AddNewTree() override
	{
		MotherPlant* new_tree = nullptr;
		if (Get_Random(0, 2)) { new_tree = new AppleTree(2, Color::white, 5e2); }
		else new_tree = new Raspberry_bush(2, Color::white, 5e2);
		_plants_list.push_back(new_tree);
		return new_tree;
	}
	void DeleteTree() override
	{
		_plants_list.pop_back();
	}
	void ShowTrees() override
	{
		for (int i = 0; i < _plants_list.size(); i++)
		{
			std::cout << "\nTree " << i + 1;
			std::cout << " " << _plants_list[i]->Get_Name();
			std::cout << " Fruits remain: " << _plants_list[i]->Get_fruits_remain();			
		}				
	}
	void Get_fruit(int tree_index, BackPack_Player_Interface* back_pack) override
	{
		if (tree_index <= _plants_list.size() && tree_index >= 0)
		{
			Fruit* new_fruit = _plants_list[tree_index]->Get_fruit();
			if (new_fruit) back_pack->AddItem(new_fruit);
		}
	}
	size_t size() { return _plants_list.size(); }

	void Info()
	{
		for (int i = 0; i < _plants_list.size(); i++)
		{
			std::cout << "\n\nTree " << i + 1;
			_plants_list[i]->Info();
		}
	}
	class iterator
	{
		MotherPlant* _data_iterator;

	public:
		//iterator() = default; óêàçàíèå êîìïèëÿòîðó ñîçäàòü êîíñòðóêòîð  ïî óìîë÷àíèþ
		iterator() = delete;
		iterator(MotherPlant* data) : _data_iterator(data) {}

		iterator& operator++()
		{
			_data_iterator++;
			return *this;
		}

		iterator& operator++(int)
		{
			iterator tmp(*this);
			_data_iterator++;
			return tmp;
		}

		iterator& operator--()
		{
			_data_iterator--;
			return *this;
		}

		iterator& operator--(int)
		{
			iterator tmp(*this);
			_data_iterator--;
			return tmp;
		}

		MotherPlant& operator*()
		{
			return *_data_iterator;
		}
		bool operator != (const iterator& obj)
		{
			return (this->_data_iterator != obj._data_iterator);
		}
		bool operator == (const iterator& obj)
		{
			return this->_data_iterator == obj._data_iterator;
		}

	};

	MotherPlant& operator [ ] (int index) { return *_plants_list[index]; }
	iterator begin() { return _plants_list[0]; }
	iterator end() { return _plants_list[_plants_list.size() - 1]; }
};