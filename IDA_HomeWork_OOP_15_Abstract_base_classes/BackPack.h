#pragma once
#include "Fruit.h"
#include <memory>
#include <vector>
#include <cassert>

class BackPack_Player_Interface
{
public:
	virtual ~BackPack_Player_Interface() = default;
	//virtual void AddItem(const Fruit& new_fruit) = 0;
	virtual void AddItem(Fruit& new_fruit) = 0;
	virtual void DeleteItem() = 0;
	virtual void Info() = 0;
	virtual void operator << (const Fruit& new_fruit) = 0;
	virtual void operator << (Fruit& new_fruit) = 0;

};


class BackPack_TheGame_Interface
{
public:
	virtual ~BackPack_TheGame_Interface() = default;
	virtual void Info() = 0;
};


class BackPack : virtual public BackPack_Player_Interface, virtual public BackPack_TheGame_Interface
{
	std::vector<std::unique_ptr<Fruit>> _items_list;

public:

	BackPack() {};

	//void AddItem(const Fruit& new_fruit) override
	void AddItem(Fruit& new_fruit) override
	{
		//std::unique_ptr<Fruit> p_uniq = std::make_unique<Fruit>(new_fruit);
		
		std::unique_ptr<Fruit> p_uniq = std::make_unique<Fruit>(std::move(new_fruit));
		
		//std::unique_ptr<Fruit> p_uniq { std::make_unique<Fruit>(new_fruit)};
		//std::unique_ptr<Fruit> p_uniq = std::make_unique<Fruit>();
		


		//_items_list.emplace_back(p_uniq);
		//_items_list.push_back(p_uniq);
		
		_items_list.push_back(std::move(p_uniq));

		//_items_list.push_back(std::make_unique<Fruit>(std::move(new_fruit)));

	}

	void DeleteItem() override
	{
		_items_list.pop_back();
	}

	void Info() override
	{
		if (_items_list.size() == 0)
		{
			std::cout << "No items";
			return;
		}
		for (int i = 0; i < _items_list.size(); i++)
		{
			std::cout << "\n\nItem " << i + 1;
			_items_list[i]->Info();
		}
	}

	 void operator << (const Fruit& new_fruit) override
	{		 
		//_items_list.push_back(std::make_unique<Fruit>(std::move(new_fruit)));
		 assert(true);
	}
	 void operator << (Fruit& new_fruit) 
	 {
		 _items_list.push_back(std::make_unique<Fruit>(std::move(new_fruit)));
	 }

};