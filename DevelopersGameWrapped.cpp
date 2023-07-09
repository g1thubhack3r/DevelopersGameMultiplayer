#include <iostream>
#include <cstdio>
#include <cctype>
#include <sstream>
#include "../include/conio.h"
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

enum class Weapon
{
    FIST = 5, 
    WOODEN_SWORD = 10,
    STONE_SWORD = 20,
    IRON_SWORD = 30,
    DIAMOND_SWORD = 40,
    HANDGUN = 50,
    SHOTGUN = 60,
    ASSUALT_RIFLE = 75,
    SNIPER_RIFLE = 80,
    MACHINEGUN = 90,
    LASER_GUN = 1000,
    FAT_MAN = 10000,
    MASS_POINT = 0x3f3f3f
};

string i2s(int i)
{
    string res = "";
    while (i > 0)
    {
        res += i % 10 + '0';
        i /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

class Enemy
{
public:
    string name;
    int hp;
    Weapon holding;
    Enemy()
    {
        name = "Unknown";
        holding = (Weapon)((rand() % 4 + 1) * 10);
        hp = rand() % (150 - 100 + 1) + 100;
    }
    Enemy(string sb, int sn, Weapon sth) : name(sb), hp(sn), holding(sth) {}
    virtual ~Enemy() {}
    bool check() { return hp <= 0; }
    string describe() { return name + string(" HP:") + i2s(hp) + string(" Attack Stength:") + i2s((int)holding); }
    int hurt(Enemy &target)
    {
        int val = rand() % (int)holding + 1;
        target.hp -= val;
        return val;
    }
    int heal()
    {
    	int val = rand() % 25 + 1;
    	if (hp + val > 100) val = 100 - hp;
    	hp += val;
    	return val;
	}
};

void clear_screen()
{
	#ifdef _WIN32
	system("cls");
	#else
	cout << "\33[2J";
	#endif
}

void mysleep(int ms)
{
    chrono::milliseconds t(ms);
    this_thread::sleep_for(t);
}

void say(string sentence)
{
    for (int i = 0; i < sentence.size(); i++)
    {
        cout << sentence[i] << flush;
        mysleep(1);
    }
}

string make_sayable(string s)
{
    stringstream tmp;
    tmp << s << endl;
    return tmp.str();
}

void typecode(string code)
{
    for (int i = 0; i < code.size(); i++)
    {
        char c;
        do
        {
            c = getch();
        }
        while (c != code[i]);
        cout << c;
    }
}


void pmove(Enemy &me, Enemy &target)
{
	int c;
	cin >> c;
	int hurtval;
	int healval;
	switch (c)
	{
		case 1:
			hurtval = me.hurt(target);
            cout << hurtval << endl;
            break;
        case 2:
            healval = me.heal();
            cout << healval;
            break;
	}
}


bool pvp(Enemy &p1, Enemy &p2)
{
	while (true)
	{
		if (p1.check())
		{
			cout << "d 1" << endl;
			return false;
		}
		cout << p1.hp << endl;
		pmove(p1, p2);
		if (p2.check())
		{
			cout << "d 2" << endl;
			return true;
		}
		cout << p2.hp << endl;
		pmove(p2, p1);
	}
}


int main(int argc, char **argv)
{
	Enemy p1("", 100, Weapon::FIST);
	Enemy p2("", 100, Weapon::FIST);
	string p1name, p2name;
	getline(cin, p1name);
	getline(cin, p2name);
	p1.name = p1name;
	p2.name = p2name;
	int w;
	cin >> w;
	p1.holding = (Weapon)w;
	p2.holding = (Weapon)w;
	pvp(p1, p2);
    return 0;
}
