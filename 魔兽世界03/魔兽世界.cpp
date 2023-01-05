#include<iostream> 
#include<cstring> 
#include<string> 
#include<algorithm>
#include<vector>
#define MAX 10000
using namespace std;

//以下为常值变量---------------------------------------------------------------
const int warriorNum = 5;
const int weaponNum = 3;
int hour = 0;//小时
int minute = 0;//分钟
//0.dragon;1.ninja;2.iceman;3.lion;4.wolf
const string warriorName[warriorNum] = { "dragon","ninja","iceman","lion","wolf" };
const string colorname[2] = { "blue","red" };
int warriorAggressivity[warriorNum] = { 0 };
//0.sword;1.bomb;2.arrow
const string weaponName[weaponNum] = { "sword","bomb","arrow" };
//0.blue;1.red
const int workOrder[2][warriorNum] = { {3,0,1,2,4},{2,3,4,1,0} };
int cityNum, k;//城市数量；每走一步，lion的忠诚度减少k。

//以下为类的声明----------------------------------------------------------------
class headquarter;
class weapon;
class warrior;
class dragon;
class ninja;
class iceman;
class lion;
class wolf;
class city;

//以下为类的具体实现------------------------------------------------------------
class city
{
public:
	warrior* p1;//from red
	warrior* p2;//from blue
	int No;
	city(int n) :p1(NULL), p2(NULL), No(n) {};
	void setWarrior(warrior* p, int stance)
	{
		if (stance == 0) p2 = p;
		else p1 = p;
	}
	int fight();//0-平局，1-红胜，2-蓝胜
	int hasTwoWarriors()
	{
		if (p1 && p2)
			return 1;
		return 0;
	}
};
class headquarter
{
private:
	int lifeNum;//司令部生命值
	int warriorQuantity[warriorNum];//每种士兵的个数记录
	int totalWarriorNum;//士兵总数
	int Number;//士兵编号
	bool workOrNot;//司令部是否继续制造士兵
	int preProductId;
	int location;//司令部所在位置
	int destination;//目的地
	warrior* points[MAX];//士兵指针
public:
	int color;//0--blue;1--red.
	string colorName;//颜色
	friend class warrior;
	friend class iceman;
	friend void combat();
	headquarter(int n, int type);//构造函数

	int produceWarrior();
	int getLifeNum() { return lifeNum; }
	int getLocation() { return location; }
	int getColor() { return color; }
	void warriorescape();
	void warriorMatch();
	void warriorloot();
	void reportLifePoints();
	int win();
};
city cities[22] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
class warrior
{
public:
	headquarter* stance;//阵营
	city* loc;//位置
	friend class headquarter;
	friend class city;
	int No;//编号
	int kind;//种类，0.dragon;1.ninja;2.iceman;3.lion;4.wolf
	int lifePoint;//生命值
	int aggressivity;//攻击力
	int location;//所在位置
	int NumofWeapons;//武器数量
	int temp;//临时记录武器数量的变量
	bool canWeaponUse[10];
	vector<weapon> Weapon;
	int weaponKindNumber[3];
	static int birthData[warriorNum];//初始生命值
	warrior(int n, headquarter* p);//构造函数
	static bool Mycompare1(weapon& p1, weapon& p2);//第一个参数需要排在第二个参数前面时返回true
	static bool Mycompare2(weapon& p1, weapon& p2);//第一个参数需要排在第二个参数前面时返回true
	virtual void printState() = 0;//打印武士生成
	void printNow(int n)
	{
		cout << " " << stance->colorName << " " << warriorName[n] << " " << No << " born" << endl;
	}
	void everyWeapons();//统计武器数量
	virtual int escape() { return 0; }//狮子逃跑
	virtual void match()
	{
		if (stance->colorName == "red")
		{
			location++;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
		else
		{
			location--;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
	}//行军
	virtual void loot(warrior* opponent) {}//狼抢夺武器
	void weaponSort()
	{
		sort(Weapon.begin(), (Weapon.begin() + NumofWeapons), Mycompare1);
	}//武器排序（用于战斗开始前）
	void weaponSort1()
	{
		sort(Weapon.begin(), (Weapon.begin() + NumofWeapons), Mycompare2);
	}//武器排序（用于缴获武器时)
	void seizeWeapon(warrior* opponent);//缴获武器
	int fight(warrior* opponent, int round);//round--回合数//战斗
	virtual int yell() { return 0; }//欢呼
	void clearWeapon();//处理武器
};
class weapon
{
private:
	int No;//编号
	int aggressivity;//攻击力
	int durability;//耐久度
public:
	friend class warrior;
	friend class dragon;
	friend class ninja;
	friend class iceman;
	friend class wolf;
	friend class lion;
	void setAggressivity(warrior* pWorrior)
	{
		switch (No)
		{
		case 0:
			aggressivity = pWorrior->aggressivity * 2 / 10; break;
		case 1:
			aggressivity = pWorrior->aggressivity * 4 / 10; break;
		case 2:
			aggressivity = pWorrior->aggressivity * 3 / 10; break;
		}
	}
	void setDurability()
	{
		switch (No)
		{
		case 0:
			durability = MAX; break;
		case 1:
			durability = 1; break;
		case 2:
			durability = 2; break;
		}
	}
};
class dragon :public warrior
{
private:
	int morale;
public:
	dragon(int n, headquarter* p) :warrior(n, p)
	{
		Weapon[0].No = No % weaponNum;
		NumofWeapons = 1;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[0];
		Weapon[0].setAggressivity(this);
		Weapon[0].setDurability();
		kind = 0;
		lifePoint = birthData[0];
		morale = (p->getLifeNum()) / (double)birthData[0];
	}
	void printState()
	{
		warrior::printNow(0);
	}
	int yell()
	{
		printf("%03d:%02d", hour, minute % 60);
		cout << ' ' << colorname[stance->getColor()] << " dragon " << No << " yelled in city ";
		return 1;
	}
};
class ninja :public warrior
{
public:
	ninja(int n, headquarter* p) :warrior(n, p)
	{
		Weapon[0].No = No % weaponNum;
		Weapon[1].No = (No + 1) % weaponNum;
		NumofWeapons = 2;
		kind = 1;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[1];
		lifePoint = birthData[1];
		Weapon[0].setAggressivity(this);
		Weapon[1].setAggressivity(this);
		Weapon[0].setDurability();
		Weapon[1].setDurability();
	}
	void printState()
	{
		warrior::printNow(1);
	}
};
class iceman :public warrior
{
public:
	iceman(int n, headquarter* p) :warrior(n, p)
	{
		Weapon[0].No = No % weaponNum;
		NumofWeapons = 1;
		kind = 2;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[2];
		Weapon[0].setAggressivity(this);
		lifePoint = birthData[2];
		Weapon[0].setDurability();
	}
	void printState()
	{
		warrior::printNow(2);
	}
	virtual void match()
	{
		if (stance->colorName == "red")
		{
			location++;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
		else
		{
			location--;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
		lifePoint -= lifePoint * 1 / 10;
		if (lifePoint <= 0)
		{
			stance->totalWarriorNum--;
			stance->points[No - 1] = NULL;
		}
	}
};
class lion :public warrior
{
private:
	int loyalty;
public:
	lion(int n, headquarter* p) :warrior(n, p)
	{
		kind = 3;
		Weapon[0].No = No % weaponNum;
		NumofWeapons = 1;
		temp = NumofWeapons;
		lifePoint = birthData[3];
		aggressivity = warriorAggressivity[3];
		Weapon[0].setAggressivity(this);
		Weapon[0].setDurability();
		loyalty = p->getLifeNum();
	}
	void printState()
	{
		warrior::printNow(3);
		printf("Its loyalty is %d\n", loyalty);
	}
	int escape()//1-escape;0-not escape
	{
		if (loyalty <= 0 && location != stance->getLocation())
			return 1;
		return 0;
	}
	virtual void match()
	{
		if (stance->getColor() == 1)
		{
			location++;
			loc = &cities[location ];
			cities[location ].setWarrior(this, stance->getColor());
		}
		else
		{
			location--;
			loc = &cities[location ];
			cities[location ].setWarrior(this, stance->getColor());
		}
		loyalty -= k;
	}
};
class wolf :public warrior
{
public:
	wolf(int n, headquarter* p) :warrior(n, p) 
	{
		kind = 4;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[4];
		lifePoint = birthData[4];
	}
	void printState()
	{
		warrior::printNow(4);
	}
	void loot(warrior* opponent)
	{
		if (opponent->kind == 4)
			return;
		if (opponent->NumofWeapons == 0)
			return;
		opponent->weaponSort1();
		int temp = 0;//临时记录的变量
		int took = -1;//0,sword;1,bomb;2,arrow
		int tt = NumofWeapons;
		for (int i = NumofWeapons; i < 10 && (i-tt) < opponent->NumofWeapons; i++)
		{
			if (i > tt && opponent->Weapon[i - tt].No != took)
				break;
			Weapon[i] = opponent->Weapon[temp];
			temp++;
			Weapon[i].setAggressivity(this);
			took = Weapon[i].No;
			NumofWeapons++;
			warrior::temp++;
		}
		if (took == -1)return;
		printf("%03d:%02d", hour, minute % 60);
		cout << ' ' << colorname[stance->getColor()] << " wolf " << No << " took " 
			<< temp << ' ' << weaponName[took] << " from " << colorname[opponent->stance->getColor()] 
			<< " " << warriorName[opponent->kind] << " " << opponent->No << " in city " << location << endl;
		opponent->Weapon.erase(opponent->Weapon.begin(), opponent->Weapon.begin() + temp);
		opponent->Weapon.resize(10);
		opponent->NumofWeapons -= temp;
		opponent->temp -= temp;
	}
};

//以下为函数的具体实现----------------------------------------------------------
headquarter::headquarter(int n, int type) :color(type), lifeNum(n), totalWarriorNum(0),
workOrNot(true), preProductId(4), Number(0)//构造函数
{
	for (int i = 0; i < MAX; i++)
		points[i] = NULL;
	memset(warriorQuantity, 0, sizeof(warriorQuantity));
	if (type == 0) { colorName = "blue"; location = cityNum + 1; destination = 0; }
	else { colorName = "red"; location = 0; destination = cityNum + 1; }
}
int headquarter::produceWarrior()
{
	int searchingNum = 0;
	bool check = false;
	int temp = 1;
	if (!workOrNot)
		return 0;
	while (searchingNum < 1)
	{
		if (lifeNum >= warrior::birthData[workOrder[color][(preProductId + temp) % 5]])
		{
			lifeNum -= warrior::birthData[workOrder[color][(preProductId + temp) % 5]];
			warriorQuantity[workOrder[color][(preProductId + temp) % 5]]++;
			switch (workOrder[color][(preProductId + temp) % 5])
			{
			case 0:
				points[Number] = new dragon(Number + 1, this);
				break;
			case 1:
				points[Number] = new ninja(Number + 1, this);
				break;
			case 2:
				points[Number] = new iceman(Number + 1, this);
				break;
			case 3:
				points[Number] = new lion(Number + 1, this);
				break;
			case 4:
				points[Number] = new wolf(Number + 1, this);
				break;
			}
			printf("%03d:%02d", hour, minute % 60);
			points[Number]->printState();
			totalWarriorNum++;
			Number++;
			check = true;
			preProductId += temp;
			break;
		}
		searchingNum++;
		temp++;
	}
	if (check == false)
	{
		workOrNot = false;
		return 0;
	}
	return 1;
}
void headquarter::warriorescape()
{
	int te = 0;
	for (int i = 0; i < totalWarriorNum+te; i++)
	{
		if (points[i] == NULL)
		{
			te++;
			continue;
		}
		int x = points[i]->escape();
		if (x == 1)
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << colorName << ' ' << warriorName[points[i]->kind] 
				<< ' ' << points[i]->No << " ran away" << endl;
			if (color == 0)
				points[i]->loc->p2 = NULL;
			else
				points[i]->loc->p1 = NULL;
			points[i] = NULL;
			totalWarriorNum--;
		}
	}
}
void headquarter::warriorMatch()
{
	int te = 0;
	for (int i = 0; i < totalWarriorNum + te; i++)
	{
		if (points[i] == NULL)
		{
			te++;
			continue;
		}
		points[i]->match();
	}
}
warrior::warrior(int n, headquarter* p) : No(n), stance(p), Weapon(10)//构造函数
{
	if (stance->color == 1)
	{
		location = 0;
		loc = &cities[0];
	}
	else
	{
		location = cityNum + 1;
		loc = &cities[cityNum + 1];
	}
	for (int i = 0; i < 10; i++)
		canWeaponUse[i] = true;
}
bool warrior::Mycompare1(weapon& p1, weapon& p2)//第一个参数需要排在第二个参数前面时返回true
{
	if (p1.No < p2.No)
		return true;
	else if (p1.No > p2.No)
		return false;
	else if (p1.No == 2 && p2.No == 2)
	{
		if (p1.durability < p2.durability)
			return true;
		else return false;
	}
	else return false;
}
bool warrior::Mycompare2(weapon& p1, weapon& p2)//第一个参数需要排在第二个参数前面时返回true
{
	if (p1.No < p2.No)
		return true;
	else if (p1.No > p2.No)
		return false;
	else if (p1.No == 2 && p2.No == 2)
	{
		if (p1.durability > p2.durability)
			return true;
		else return false;
	}
	else return false;
}
void warrior::seizeWeapon(warrior* opponent)
{
	opponent->weaponSort1();
	int temp = 0;
	for (int i = NumofWeapons; i < 10 && temp < opponent->NumofWeapons; i++)
	{
		Weapon[i] = opponent->Weapon[temp++];
		Weapon[i].setAggressivity(this);
		NumofWeapons++;
	}
	warrior::temp = NumofWeapons;
	opponent->Weapon.erase(opponent->Weapon.begin(), opponent->Weapon.begin() + temp);
	opponent->NumofWeapons -= temp;
}
int warrior::fight(warrior* opponent, int round)//round--回合数
{
	
	int weaponStateChange = false;
	if (NumofWeapons == 0)return false;
	if ((round - 1) % NumofWeapons == 0)//处理耐久度是0的武器
	{
		NumofWeapons = temp;
		for (int i = 0; i < 10; i++)
			if (canWeaponUse[i] == false)
			{
				Weapon.erase(Weapon.begin() + i, Weapon.begin() + (i + 1));
				Weapon.resize(10);
				canWeaponUse[i] = true;
			}
	}
	if (temp == 0)return false;
	if (opponent->lifePoint <= 0)return false;
	opponent->lifePoint -= Weapon[(round - 1) % NumofWeapons].aggressivity;
	if (Weapon[(round - 1) % NumofWeapons].No == 1 && this->kind != 1)
		this->lifePoint -= Weapon[(round - 1) % NumofWeapons].aggressivity * 1 / 2;
	Weapon[(round - 1) % NumofWeapons].durability -= 1;
	if (Weapon[(round - 1) % NumofWeapons].durability <= 0)
	{
		canWeaponUse[(round - 1) % NumofWeapons] = false;
		temp = NumofWeapons - 1;
		weaponStateChange = true;
	}
	return weaponStateChange;
}
void warrior::everyWeapons()
{
	weaponKindNumber[0] = weaponKindNumber[1] = weaponKindNumber[2] = 0;
	for (int i = 0; i < NumofWeapons; i++)
		weaponKindNumber[Weapon[i].No]++;
}
int city::fight()//0-都活了，1-红胜，2-蓝胜,-1-都死了
{
	if (p1 && p2)
	{
		int cc = 0;
		p1->weaponSort();
		p2->weaponSort();
		if (No % 2)//红武士先攻击
		{
			int round = 1;
			while (1)
			{
				int life1 = p1->lifePoint, life2 = p2->lifePoint;
				int a = p1->fight(p2, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				if (p2->lifePoint <= 0)
					return 1;
				int b = p2->fight(p1, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				int judge1 = life1 - p1->lifePoint, judge2 = life2 - p2->lifePoint;
				if (cc == 2)
					return 0;
				if (!a && !b && !judge1 && !judge2)
					cc += 1;
				if (p1->lifePoint <= 0)
					return 2;
				round++;
			}
		}
		else//蓝武士先攻击
		{
			int round = 1;
			while (1)
			{
				int life1 = p1->lifePoint, life2 = p2->lifePoint;
				int b = p2->fight(p1, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				if (p1->lifePoint <= 0)
					return 2;
				int a = p1->fight(p2, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				int judge1 = life1 - p1->lifePoint, judge2 = life2 - p2->lifePoint;
				if (p2->lifePoint <= 0)
					return 1;
				if (cc == 2)
					return 0;
				if (!a && !b && !judge1 && !judge2)
					cc += 1;
				round++;
			}
		}
	}
}
void warrior::clearWeapon()//处理耐久度是0的武器
{
	NumofWeapons = temp;
	for (int i = 0; i < 10; i++)
		if (canWeaponUse[i] == false)
		{
			Weapon.erase(Weapon.begin() + i, Weapon.begin() + (i + 1));
			Weapon.resize(10);
			canWeaponUse[i] = true;
		}
}
void headquarter::reportLifePoints()
{
	printf("%03d:%02d ", hour, minute % 60);
	cout << lifeNum << " elements in " << colorName << " headquarter" << endl;
}
int headquarter::win()
{
	int te = 0;
	for (int i = 0; i < totalWarriorNum + te; i++)
	{
		if (points[i] == NULL)
		{
			te++;
			continue;
		}
		if (points[i]->location == destination)
		{
			int opponent = (color == 0) ? 1 : 0;
			printf("%03d:%02d ", hour, minute % 60);
			cout << colorName << " " << warriorName[points[i]->kind] << " " << 
				points[i]->No << " reached " << colorname[opponent] << " headquarter with " 
				<< points[i]->lifePoint << " elements and force " << points[i]->aggressivity << endl;
			printf("%03d:%02d ", hour, minute % 60);
			cout << colorname[opponent] << " headquarter was taken" << endl;
			return 1;
		}
	}
	return 0;
}
int warrior::birthData[warriorNum];
void warriorloot()
{
	for (int i = 1; i <= cityNum; i++)
		if (cities[i].hasTwoWarriors())
		{
			if (cities[i].p1->location != i || cities[i].p2->location != i)continue;
				cities[i].p1->loot(cities[i].p2);
				cities[i].p2->loot(cities[i].p1);
		}
}
void match()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].p1 != NULL && cities[i].p1->location == i)
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << " " << "red" << ' ' << warriorName[cities[i].p1->kind] <<
				' ' << cities[i].p1->No << " marched to city " << cities[i].p1->location
				<< " with " << cities[i].p1->lifePoint << " elements and force " <<
				cities[i].p1->aggressivity << endl;
		}
		if (cities[i].p2 != NULL && cities[i].p2->location == i)
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << " " << "blue" << ' ' << warriorName[cities[i].p2->kind] <<
				' ' << cities[i].p2->No << " marched to city " << cities[i].p2->location
				<< " with " << cities[i].p2->lifePoint << " elements and force " <<
				cities[i].p2->aggressivity << endl;
		}
	}
}
void combat()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].hasTwoWarriors())
		{
			if (cities[i].p1->location != i || cities[i].p2->location != i)continue;
			printf("%03d:%02d", hour, minute % 60);
			int result = cities[i].fight();
			cities[i].p1->clearWeapon();
			cities[i].p2->clearWeapon();
			if (result == 1)//红胜
			{
				cities[i].p2->stance->points[cities[i].p2->No - 1] = NULL;
				cities[i].p2->stance->totalWarriorNum--;
				cout << " red " << warriorName[cities[i].p1->kind] << " " << cities[i].p1->No <<
					" killed blue " << warriorName[cities[i].p2->kind] << " "
					<< cities[i].p2->No << " in city " << i << " remaining " << cities[i].p1->lifePoint
					<< " elements" << endl;
				cities[i].p1->seizeWeapon(cities[i].p2);
				if (cities[i].p1->yell())
					cout << i << endl;
				cities[i].p2 = NULL;
			}
			else if (result == 2)//蓝胜
			{
				cities[i].p1->stance->points[cities[i].p1->No - 1] = NULL;
				cities[i].p1->stance->totalWarriorNum--;
				cout << " blue " << warriorName[cities[i].p2->kind] << " " << cities[i].p2->No <<
					" killed red " << warriorName[cities[i].p1->kind] << " "
					<< cities[i].p1->No << " in city " << i << " remaining " << cities[i].p2->lifePoint
					<< " elements" << endl;
				cities[i].p2->seizeWeapon(cities[i].p1);
				if (cities[i].p2->yell())
					cout << i << endl;
				cities[i].p1 = NULL;
			}
			else if (result == 0)//都活了
			{
				cout << " both red " << warriorName[cities[i].p1->kind] <<
					" " << cities[i].p1->No << " and blue " << warriorName[cities[i].p2->kind] << ' '
					<< cities[i].p2->No << " were alive in city " << i << endl;
				if (cities[i].p1->yell())
					cout << i << endl;
				if (cities[i].p2->yell())
					cout << i << endl;
			}
			else//都死了
			{
				cities[i].p1->stance->points[cities[i].p1->No - 1] = NULL;
				cities[i].p1->stance->totalWarriorNum--;
				cities[i].p2->stance->points[cities[i].p2->No - 1] = NULL;
				cities[i].p2->stance->totalWarriorNum--;
				cout << " both red " << warriorName[cities[i].p1->kind] <<
					" " << cities[i].p1->No << " and blue " << warriorName[cities[i].p2->kind] << ' '
					<< cities[i].p2->No << " died in city " << i << endl;
				cities[i].p1 = NULL;
				cities[i].p2 = NULL;
			}

		}
	}
}
void reportWeapon()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].p1 != NULL && cities[i].p1->location == i)
		{
			cities[i].p1->everyWeapons();
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << "red" << " " << warriorName[cities[i].p1->kind]
				<< " " << cities[i].p1->No << " has " << cities[i].p1->weaponKindNumber[0]
				<< " sword " << cities[i].p1->weaponKindNumber[1] << " bomb " <<
				cities[i].p1->weaponKindNumber[2] << " arrow"
				<< " and " << cities[i].p1->lifePoint << " elements" << endl;
		}
		if (cities[i].p2 != NULL && cities[i].p2->location == i)
		{
			cities[i].p2->everyWeapons();
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << "blue" << " " << warriorName[cities[i].p2->kind]
				<< " " << cities[i].p2->No << " has " << cities[i].p2->weaponKindNumber[0]
				<< " sword " << cities[i].p2->weaponKindNumber[1] << " bomb " <<
				cities[i].p2->weaponKindNumber[2] << " arrow"
				<< " and " << cities[i].p2->lifePoint << " elements" << endl;
		}
	}
}

//以下为main函数------------------------------------------------------------------
int main()
{
	int u = 0;
	cin >> u;
	int caseNo = 1;
	while (u--)
	{
		cout << "Case " << caseNo++ << ":" << endl;
		//输入-----------------------------------
		int life, t;//要求输出从0时0分开始，到时间t为止(包括t) 的所有事件,t以分钟为单位.
		cin >> life >> cityNum >> k >> t;
		headquarter Blue(life, 0), Red(life, 1);//0--blue,1--red
		for (int i = 0; i < warriorNum; i++)
			cin >> warrior::birthData[i];
		for (int i = 0; i < warriorNum; i++)
			cin >> warriorAggressivity[i];
		hour = 0; minute = 0;
		for (int i = 0; i < 21; i++)
		{
			cities[i].p1 = NULL;
			cities[i].p2 = NULL;
		}
		//----------------------------------------
		while (minute <= t)
		{
			//在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。
			Red.produceWarrior();
			Blue.produceWarrior();
			minute += 5;
			if (minute > t)break;
			//在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。
			Red.warriorescape();
			Blue.warriorescape();
			minute += 5;
			if (minute > t)break;
			//在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。
			//即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部。
			Red.warriorMatch();
			Blue.warriorMatch();
			int b = Blue.win(); 
			match();
			int a = Red.win();if (b == 1)break;
			if (a == 1)break;
			minute += 25;
			if (minute > t)break;
			//在每个小时的第35分：在有wolf及其敌人的城市，wolf要抢夺对方的武器。
			warriorloot();
			minute += 5;
			if (minute > t)break;
			//在每个小时的第40分：在有两个武士的城市，会发生战斗。
			combat();
			minute += 10;
			if (minute > t)break;
			//在每个小时的第50分，司令部报告它拥有的生命元数量。
			Red.reportLifePoints();
			Blue.reportLifePoints();
			minute += 5;
			if (minute > t)break;
			//在每个小时的第55分，每个武士报告其拥有的武器情况。
			reportWeapon();
			minute += 5;
			hour += 1;
		}
	}
	return 0;
}