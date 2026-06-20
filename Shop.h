#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include<fstream>

using namespace std;

class Shop {
private:
	string username1;
	string username2;
	int items1[5];
	int items2[5];
	int gems1;
	int gems2;
	int price[5];
	bool multi;
public:

	Shop(string user1, int g1, string user2 = "", int g2 = 0);
	bool affording(int itemI, int playerNum); 
	bool purchaseItem(int itemI, int player);  
	void saveToFile();
	void loadFromFile();
	int getItemCount(int itemI, int player);  
	int getGems(int player); 
	int getPrice(int itemI);
	void setGems(int g, int player);  
	void setItem(int itemI, int player);
	void useItem(int itemI, int player);
};