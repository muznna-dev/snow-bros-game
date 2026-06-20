#include "Shop.h"

Shop::Shop(string user1, int g1, string user2, int g2)
    : username1(user1), gems1(g1), username2(user2), gems2(g2) {

    multi = (user2 != "");  

    for (int i = 0; i < 5; i++) {
        items1[i] = 0;
        items2[i] = 0;
    }

    price[0] = 50;
    price[1] = 20;
    price[2] = 30;
    price[3] = 25;
    price[4] = 35;

    loadFromFile();
}

bool Shop::affording(int itemI, int player) {
    if (itemI < 0 || itemI >= 5)
        return false;

    int itemPrice = getPrice(itemI);  

    if (player == 1)
        return itemPrice <= gems1;
    else if (player == 2)
        return itemPrice <= gems2;

    return false;  
}

void Shop::saveToFile() {
    string filename1 = username1 + "_items.txt";
    ofstream file1(filename1);  
    if (file1.is_open()) {
        file1 << gems1 << endl;
        for (int i = 0; i < 5; i++)
            file1 << items1[i] << endl;
        file1.close();
    }

    if (multi) {
        string filename2 = username2 + "_items.txt";
        ofstream file2(filename2);  
        if (file2.is_open()) {
            file2 << gems2 << endl;
            for (int i = 0; i < 5; i++)
                file2 << items2[i] << endl;
            file2.close();
        }
    }
}
void Shop::useItem(int itemI, int player) {
    if (player == 1 && items1[itemI] > 0) {
        items1[itemI]--;
        saveToFile();
    }
    else if (player == 2 && multi && items2[itemI] > 0) {
        items2[itemI]--;
        saveToFile();
    }
}

void Shop::loadFromFile() {
    string filename1 = username1 + "_items.txt";
    ifstream file1(filename1); 
    if (file1.is_open()) {
        file1 >> gems1;
        for (int i = 0; i < 5; i++)
            file1 >> items1[i];
        file1.close();
    }

    if (multi) {
        string filename2 = username2 + "_items.txt";  
        ifstream file2(filename2); 
        if (file2.is_open()) {
            file2 >> gems2;
            for (int i = 0; i < 5; i++)
                file2 >> items2[i];
            file2.close();
        }
    }
}

bool Shop::purchaseItem(int itemI, int player) {
    if (itemI < 0 || itemI >= 5)
        return false;

    if (!affording(itemI, player)) 
        return false;

    if (player == 1 || !multi) {  
        gems1 -= price[itemI];
        items1[itemI]++;
        saveToFile();
        return true;
    }

    if (player == 2 && multi) {  
        gems2 -= price[itemI];
        items2[itemI]++;
        saveToFile();
        return true;
    }

    return false;
}

int Shop::getItemCount(int itemI, int player) {
    if (player == 1 || !multi) 
        return items1[itemI];

    if (player == 2 && multi)
        return items2[itemI];

    return 0;  
}

int Shop::getGems(int player) {
    if (player == 1)
        return gems1;
    else if (player == 2)  
        return gems2;

    return 0;  
}

int Shop::getPrice(int itemI) {
    return price[itemI];
}

void Shop::setGems(int g, int player) {
    if (player == 1 || !multi)
        gems1 = g;
    else if (player == 2)  
        gems2 = g;

    saveToFile();  
}

void Shop::setItem(int itemI, int player) {
    if (player == 1) {  
        items1[itemI]++;
        saveToFile();
    }

    if (player == 2 && multi) {
        items2[itemI]++;
        saveToFile();
    }
}