//魔兽世界终极版(WarCraft IV)
//最终版 2021年5月24日
//作者：陈奕阳  学号：2000013152
#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<vector>
#define MAX 10000
using namespace std;

//以下是全局变量----------------------------------------------------------
const int warriorNum = 5;//武士种类总数
const int weaponNum = 3;//武器种类总数
int hour = 0;//小时
int minute = 0;//分钟
const int RED = 0, BLUE = 1;//red-0,blue-1
int warriorAggressivity[warriorNum] = { 0 };
//0.sword;1.bomb;2.arrow
const string weaponName[weaponNum] = { "sword","bomb","arrow" };
int arrowAggressivity = 0;//arrow的攻击力
const int workOrder[2][warriorNum] = { {2,3,4,1,0} ,{3,0,1,2,4} };//制造武士的顺序
const string warriorName[warriorNum] = { "dragon","ninja","iceman","lion","wolf" };//0-dragon,1-ninja.2-iceman,3-lion,4-wolf
const string colorName[2] = { "red","blue" };//0-red,1-blue

//以下是类的声明----------------------------------------------------------
class Time;//维护时间
class Weapon;//维护武器
class Headquarter;//维护司令部
class City;//维护城市
class Warrior;//维护武士
class Dragon;//维护龙
class Ninja;//维护ninja
class Iceman;//维护iceman
class Lion;//维护狮子
class Wolf;//维护狼
class World;//维护整个魔兽世界

//以下是类的具体实现----------------------------------------------------------
class Weapon
{
private:
	int No;//编号
	int aggressivity;//攻击力
	int durability;//耐久度
public:
	void setAggressivity(Warrior* pWorrior);
	void setDurability();
	int changeAggressivity();
	friend class Dragon;
	friend class Iceman;
	friend class Ninja;
	friend class Lion;
	friend class Wolf;
};

class Headquarter
{
private:
	int lifeNum;//司令部生命值
	int warriorQuantity[warriorNum];//每种士兵的个数记录
	int Number;//士兵编号
	int stance;//立场，即红方或蓝方
	int sumWarriorNum;//制造的武士的总数
	int totalWarriorNum;//现存士兵总数
	int location;//司令部所在位置
	int reach;//到达对方司令部的武士的数量
	int nextProduce;//下一个需要制造的武士的种类
	Warrior* points[MAX];//士兵指针
	int destination;//目的地
	string colorName;//颜色
public:
	Headquarter() :sumWarriorNum(0), reach(0), nextProduce(0), totalWarriorNum(0),
		location(0), destination(0), points{ NULL }{}//构造函数
	void set(int life, int st);//设置司令部生命值和立场
	int getLifeNum() { return lifeNum; }
	int getLocation() { return location; }
	int getColor() { return stance; }
	string getColorName() { return colorName; }
	void warriorescape();//狮子逃跑
	friend class World;//声明World为友元类
	void reportLifePoints();//报告生命情况
	friend ostream& operator<<(ostream& o, Headquarter& hd);//方便输出
	friend class Weapon;
	friend class Warrior;
	friend class City;
	friend class Dragon;
	friend class Iceman;
	friend class Ninja;
	friend class Lion;
	friend class Wolf;
};

class Warrior
{
private:
	int No;//武士序号
	int kind;//武士种类
	int lifePoint;//武士生命值
	int stance;//武士立场（红或蓝）
	int aggressivity;//武士攻击力
	int temp;//临时记录武器数量的变量
	int position;//武士所处位置
	int swordNum;//武士所拥有的剑的耐久值
	int arrowNum;//武士所拥有的弓箭的数量
	int bombNum;//武士所拥有的炸弹的数量
	bool isAlive;//是否还活着
	bool hasArrived;//是否已经抵达对方司令部
	int loyalty;//忠诚
	vector<Weapon> weapon;//武器
	int NumofWeapons;//武器总数
	int weaponKindNumber[3];//武器数量
	City* loc;//位置
	Headquarter* st;//阵营
	int pace;//步伐
	bool canWeaponUse[10];//武器能否使用
	static int birthData[warriorNum];//初始生命值
	double morale;//时期

public:
	Warrior(int n, Headquarter* p);//构造函数
	Warrior() :No(0), kind(0), lifePoint(0), stance(0), aggressivity(0), position(0), swordNum(0),
		arrowNum(0), bombNum(0), isAlive(1), hasArrived(0), loyalty(0), pace(0), morale(0) {};//构造函数
	friend ostream& operator<<(ostream& o, Warrior& w);//方便输出
	virtual void printState() {};//打印武士生成
	void printNow(int n);
	void everyWeapons();//统计武器数量
	virtual int escape() { return 0; }//狮子逃跑
	void beFought(Warrior& w);//直接描述被敌人攻击
	void beFoughtBack(Warrior& w);//直接描述被敌人反击
	virtual void looting(Warrior* opponent) {}//狼抢夺武器
	void match();//行军前进
	void clearWeapon(int);//处理武器
	void set(Time& t, int st, int id, int cityNum, int kd, int life, int agg, int loy);//设置各项指标
	void setWeapon(int s, int a, int b);//设置武器指标
	void loot(Warrior* opponent);//狼抢夺武器
	void yell(Time& t, int id);//龙欢呼
	void showmarch();//输出行军
	void reachDestination();//输出抵达
	void output();//输出自身情况
	//以下是友元类的声明
	friend class City;
	friend class Weapon;
	friend class Headquarter;
	friend class World;
	friend class Dragon;
	friend class Iceman;
	friend class Ninja;
	friend class Lion;
	friend class Wolf;
};

class Dragon :public Warrior
{
private:
	float morale;//士气值
public:
	Dragon(int n, Headquarter* p);//构造函数
	void printState();//打印状态
	int yell();//欢呼
};

class Ninja :public Warrior
{
public:
	Ninja(int n, Headquarter* p);
	void printState();//状态
};

class Iceman :public Warrior
{
private:
	int matchCount;//是否前进了两步
public:
	Iceman(int n, Headquarter* p);
	void printState();//打印状态
	virtual void match();//行军（改变）
};

class Lion :public Warrior
{
private:
	int loyalty;//忠实度
public:
	Lion(int n, Headquarter* p);
	void printState();//打印状态
	int escape();//逃跑，1-escape;0-not escape
};

class Wolf :public Warrior
{
public:
	Wolf(int n, Headquarter* p);
	void printState();//打印状态
};

class Time
{
private:
	int hour;//时
	int minute;//分
	int limit;//时间限制
public:
	Time() :hour(0), minute(0), limit(0) {}//构造函数
	void setLimit(int time);//设置时间限制
	friend ostream& operator<<(ostream& o, Time& t);//方便输出
	int operator+=(int n);//方便增加时间
};

class City
{
private:
	int flag;//旗帜
	int firstAttack;//谁先攻击
	int lifeNum;//生命元
	int No;//序号
	int winner;//胜利的场数
	Warrior* warrior[2];//两个武士指针
public:
	City() :flag(0), firstAttack(0), lifeNum(0), No(-1), winner(0), warrior{ NULL }{};//构造函数
	void set(int n);//设置序号
	void setWarrior(Warrior* p, int stance);//设置武士
	void setFlag(int st, Time& t);//升旗
	int hasTwoWarriors();//是否有两个武士
	void work(Time& t, int st);//分出了胜负后，设置改变
	void change(Time& t, int k);//未分出胜负后，设置改变
	void produceElements();//产生生命元
	int simulate(Time& t, int k);//模拟开战
	int fight(Time& t, int k);//双方真正开战！
	friend class World;
	friend class Headquarter;
};

class World
{
private:
	int startLifePoint;//初始生命值
	int cityNum;//城市总数
	int arrowAttack;//弓箭的攻击力
	int loyaltyLost;//忠实度下降的数量
	int limitTime;//限制时间
	int startWarriorLifeNum[5];//初始武士的生命值
	int startWarriorAggressivity[5];//初始武士的攻击力
	Time time;//时间类
	Headquarter headquarter[2];//两个司令部
	City* cities;//多个城市
	Warrior* warrior[2];//双方多个武士
	int end;
public:
	World(int caseNum);//构造函数
	void produceWarrior(int stance);//制造武士
	void escape(int postion, int stance);//狮子逃跑
	void march();//行军
	void work();//更新信息
	void earnLifePoint(int i);//获得生命值
	void releaseArrow();//放箭！
	void releaseBomb();//放炸弹！
	void giveBonus(int stance, int position, int& bonus);//给予奖励
	void output();
	void fight();//开战！
	void operation();//整个时间的运行
	void myDelete();//防止内存垃圾
};

//以下是类的成员函数----------------------------------------------------------
//Weapon类
void Weapon::setAggressivity(Warrior* pWorrior)
{
	switch (No)
	{
	case 0:
		aggressivity = pWorrior->aggressivity * 2 / 10; break;
	case 1:
		aggressivity = MAX; break;
	case 2:
		aggressivity = arrowAggressivity; break;
	}
}
void Weapon::setDurability()
{
	switch (No)
	{
	case 0:
		durability = MAX; break;
	case 1:
		durability = 1; break;
	case 2:
		durability = 3; break;
	}
}
int Weapon::changeAggressivity()//0--坏了
{
	if (No == 0)
	{
		aggressivity = aggressivity * 8 / 10;
		if (aggressivity <= 0)
			return 0;
	}
	return 1;
}

//Headquarter类
void Headquarter::set(int life, int st)
{
	lifeNum = life;
	stance = st;
}
void Headquarter::warriorescape()
{
	int te = 0;//便于处理已经死亡的武士
	for (int i = 0; i < totalWarriorNum + te; i++)
	{
		if (points[i] == NULL)//武士已经死亡
		{
			te++;
			continue;
		}
		if (points[i]->escape())//狮子逃跑了！
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << colorName << ' ' << warriorName[points[i]->kind]
				<< ' ' << points[i]->No << " ran away" << endl;//输出信息
			if (stance == 0)
				points[i]->loc->warrior[0] = NULL;
			else
				points[i]->loc->warrior[1] = NULL;
			points[i] = NULL;
			totalWarriorNum--;//总武士数减一
		}
	}
}
void Headquarter::reportLifePoints()
{
	printf("%03d:%02d ", hour, minute % 60);
	cout << lifeNum << " elements in " << colorName << " headquarter" << endl;
}
ostream& operator<<(ostream& o, Headquarter& hd)
{
	o << hd.lifeNum << " elements in " << colorName[hd.stance] << " headquarter" << endl;
	return o;
}

//Warrior类
int Warrior::birthData[warriorNum];
Warrior::Warrior(int n, Headquarter* p): No(n), st(p), weapon(10)
{
	for (int i = 0; i < 10; i++)
		canWeaponUse[i] = true;
}
void Warrior::printNow(int n)
{
	cout << " " << st->colorName << " " << warriorName[n] << " " << No << " born" << endl;
}
ostream& operator<<(ostream& o, Warrior& w)
{
	o << colorName[w.stance] << " " << warriorName[w.kind] << " " << w.No;
	return o;
}
void Warrior::beFought(Warrior& w)
{
	//每次战斗只有一方发起主动进攻一次。
	//被攻击者生命值会减去进攻者的攻击力值和进攻者手中sword的攻击力值
	lifePoint = lifePoint - (w.aggressivity + w.swordNum);
	w.swordNum *= 0.8;
}
void Warrior::everyWeapons()
{
	//遍历一遍，数一下自己的武器数量
	weaponKindNumber[0] = weaponKindNumber[1] = weaponKindNumber[2] = 0;
	for (int i = 0; i < NumofWeapons; i++)
		weaponKindNumber[No]++;
}
void Warrior::reachDestination()
{
	cout << (*this) << " reached " << colorName[!stance] << " headquarter with "
		<< lifePoint << " elements and force " << aggressivity << endl;
	isAlive = 0;
	hasArrived = 1;
}
void Warrior::beFoughtBack(Warrior& w)
{
	//被进攻者若没死，就会发起反击.
	//被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中sword的攻击力值
	lifePoint = lifePoint - (w.aggressivity / 2 + w.swordNum);
	w.swordNum *= 0.8;
}
void Warrior::match()
{
	pace++;
	position = (stance) ? position - 1 : position + 1;
	if (kind == 2 && !(pace % 2))//iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20
	{
		aggressivity += 20;
		lifePoint -= 9;
		if (lifePoint <= 0)//但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死
			lifePoint = 1;
	}
}
void Warrior::showmarch()
{
	cout << (*this) << " marched to city " << position << " with "
		<< lifePoint << " elements and force " << aggressivity << endl;
}
void Warrior::set(Time& t, int st, int id, int cityNum, int kd, int life, int agg, int loy)
{
	isAlive = 1;
	hasArrived = 0;
	No = id;
	stance = st;
	pace = 0;
	kind = kd;
	lifePoint = life;
	aggressivity = agg;
	position = (st == 1) ? cityNum + 1 : 0;
	setWeapon(0, 0, 0);
	cout << t << *this << " born" << endl;
	if (kind == 1)//ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器
	{
		if (id % 3 == 0)
			setWeapon(aggressivity * 2 / 10, 0, 1);
		else if (id % 3 == 1)
			setWeapon(0, 3, 1);
		else
			setWeapon(aggressivity * 2 / 10, 3, 0);
	}
	else if (kind == 3)//lion 有“忠诚度”这个属性，其初始值等于它降生之后其司令部剩余生命元的数目
	{
		loyalty = loy;
		cout << "Its loyalty is " << loy << endl;
	}
	else if (kind == 0)//dragon可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器
	{
		morale = double(loy) / lifePoint;
		printf("Its morale is %.2lf\n", morale);
		if (id % 3 == 0)
			setWeapon(aggressivity * 2 / 10, 0, 0);
		else if (id % 3 == 1)
			setWeapon(0, 0, 1);
		else
			setWeapon(0, 3, 0);
	}
	else if (kind == 2)//iceman可以拥有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器
	{
		if (id % 3 == 0)
			setWeapon(aggressivity * 2 / 10, 0, 0);
		else if (id % 3 == 1)
			setWeapon(0, 0, 1);
		else
			setWeapon(0, 3, 0);
	}
}
void Warrior::setWeapon(int s, int a, int b)
{
	swordNum = s, arrowNum = a, bombNum = b;
}
void Warrior::loot(Warrior* opponent)
{
	if (!swordNum)
	{
		swordNum = opponent->swordNum;
	}
	if (!bombNum)
	{
		bombNum = opponent->bombNum;
	}
	if (!arrowNum)
	{
		arrowNum = opponent->arrowNum;
	}
}
void Warrior::clearWeapon(int temp)//处理耐久度是0的武器
{
	NumofWeapons = temp;
	for (int i = 0; i < 10; i++)
		if (canWeaponUse[i] == false)//武器坏了
		{
			weapon.erase(weapon.begin() + i, weapon.begin() + (i + 1));
			weapon.resize(10);
			canWeaponUse[i] = true;
		}
}
void Warrior::yell(Time& t, int id)
{
	cout << t << (*this) << " yelled in city " << id << endl;
}
void Warrior::output()
{
	cout << (*this) << " has ";
	int check = 0;
	//以下输出武器数量
	if (arrowNum)
	{
		cout << "arrow(" << arrowNum << ")";
		check = 1;
	}
	if (bombNum)
	{
		if (check)
			putchar(',');
		cout << "bomb";
		check = 1;
	}
	if (swordNum)
	{
		if (check)putchar(',');
		cout << "sword(" << swordNum << ")";
		check = 1;
	}
	if (!check)
		cout << "no weapon" << endl;
	else
		cout << endl;
}

//Dragon类
Dragon::Dragon(int n, Headquarter* p) :Warrior(n, p)
{
	weapon[0].No = No % weaponNum;
	NumofWeapons = 1;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[0];
	weapon[0].setAggressivity(this);
	weapon[0].setDurability();
	kind = 0;
	lifePoint = birthData[0];
	morale = (p->getLifeNum()) / (double)birthData[0];
}
void Dragon::printState()
{
	Warrior::printNow(0);
	printf("Its morale is %.2lf", morale);
}
int Dragon::yell()
{
	if (morale <= 0.8)
		return 0;
	printf("%03d:%02d", hour, minute % 60);
	cout << ' ' << colorName[1] << " dragon " << No << " yelled in city ";
	return 1;
}

//Ninja类
void Ninja::printState()
{
		Warrior::printNow(1);
}
Ninja::Ninja(int n, Headquarter* p) :Warrior(n, p)
{
	weapon[0].No = No % weaponNum;
	weapon[1].No = (No + 1) % weaponNum;
	NumofWeapons = 2;
	kind = 1;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[1];
	lifePoint = birthData[1];
	weapon[0].setAggressivity(this);
	weapon[1].setAggressivity(this);
	weapon[0].setDurability();
	weapon[1].setDurability();
}

//Iceman类
Iceman::Iceman(int n, Headquarter* p) :Warrior(n, p)
{
	weapon[0].No = No % weaponNum;
	NumofWeapons = 1;
	kind = 2;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[2];
	weapon[0].setAggressivity(this);
	lifePoint = birthData[2];
	weapon[0].setDurability();
}
void Iceman::printState()
{
	Warrior::printNow(2);
}
void Iceman::match()
{
	matchCount++;
	if (matchCount == 2)
	{
		matchCount = 0;
		lifePoint -= 9;
		aggressivity += 20;
		if (lifePoint <= 0)
			lifePoint = 1;
	}
}

//Lion类
Lion::Lion(int n, Headquarter* p) :Warrior(n, p)
{
	kind = 3;
	NumofWeapons = 0;
	temp = NumofWeapons;
	lifePoint = birthData[3];
	aggressivity = warriorAggressivity[3];
	loyalty = p->getLifeNum();
}
void Lion::printState()
{
	Warrior::printNow(3);
	printf("Its loyalty is %d\n", loyalty);
}
int Lion::escape()//1-escape;0-not escape
{
	if (loyalty <= 0 && position != st->destination)
		return 1;
	return 0;
}

//Wolf类
void Wolf::printState()
{
	Warrior::printNow(4);
}
Wolf::Wolf(int n, Headquarter* p) :Warrior(n, p)
{
	kind = 4;
	NumofWeapons = 0;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[4];
	lifePoint = birthData[4];
}

//Time类
void Time::setLimit(int time)
{
	limit = time;
}
ostream& operator<<(ostream& o, Time& t)
{
	printf("%03d:%02d ", t.hour, t.minute % 60);
	hour = t.hour;
	minute = t.minute;
	return o;
}
int Time::operator+=(int n)
{
	this->minute += n;
	this->hour = minute / 60;
	return minute <= limit;
}

//City类
void City::set(int n)
{
	winner = 0, lifeNum = 0, flag = 0;
	No = n;
	warrior[RED] = warrior[BLUE] = NULL;
	firstAttack = (n + 1) % 2;
}
void City::setFlag(int st, Time& t)
{
	if (st && winner <= 0)//不合理情况
	{
		winner = 1;
		return;
	}
	if (!st && winner >= 0)//不合规情况
	{
		winner = -1;
		return;
	}
	if (st&&winner==1)//st==1表示蓝方获得了胜利
	{
		winner = 2;
		if (!flag)
		{
			flag = 1, firstAttack = 1;//插蓝旗，蓝武士先进攻
			cout << t << "blue flag raised in city " << No << endl;
		}
		else if (!firstAttack)
		{
			flag = 1, firstAttack = 1;//插蓝旗，蓝武士先进攻
			cout << t << "blue flag raised in city " << No << endl;
		}
	}
	else if(winner==-1)//红方胜
	{
		winner = -2;
		if (!flag )
		{
			flag = 1;
			firstAttack = 0;//插红旗，红方先进攻
			cout << t << "red flag raised in city " << No << endl;
		}
		else if (firstAttack)
		{
			flag = 1;
			firstAttack = 0;//插红旗，红方先进攻
			cout << t << "red flag raised in city " << No << endl;
		}
	}
	
}
int City::hasTwoWarriors()
{
	auto p1 = warrior[0];
	auto p2 = warrior[1];
	if (p1 && p2)//双方都在
	{
		if (p1->position == No && p2->position == No)
			return 1;
	}
	return 0;
}
void City::work(Time& t, int st)
{
	
	if (warrior[st]->kind == 4)//wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了
	{
		warrior[st]->loot(warrior[!st]);
	}
	else if (warrior[st]->kind == 0)//dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼
	{
		warrior[st]->morale += 0.2;
		if (st == firstAttack && warrior[st]->morale > 0.8)
			warrior[st]->yell(t, No);
	}
	cout << t << (*warrior[st]) << " earned " << lifeNum << " elements for his headquarter" << endl;
	setFlag(st, t);//插旗子
}
void City::setWarrior(Warrior* p, int stance)
{
	if (stance == 0) warrior[1] = p;
	else warrior[0] = p;
}
void City::change(Time& t, int k)
{
	winner = 0;//无人获胜
	for (int i = 0; i < 2; i++)
	{
		if (warrior[i]->kind == 3)
			warrior[i]->loyalty -= k;
		else if (warrior[i]->kind == 0)
			warrior[i]->morale -= 0.2;
	}
	if (warrior[firstAttack]->kind == 0 && warrior[firstAttack]->morale > 0.8)//龙没死
	{
		cout << t << (*warrior[firstAttack]) << " yelled in city " << No << endl;
	}
}
void City::produceElements()
{
	lifeNum += 10;
}
int City::fight(Time& t, int k)
{
	int tempLifeNum[2] = { warrior[0]->lifePoint,warrior[1]->lifePoint };//临时记录生命值
	int loser;//失败者
	warrior[!firstAttack]->beFought(*warrior[firstAttack]);
	cout << t << (*warrior[firstAttack]) << " attacked "
		<< (*warrior[!firstAttack]) << " in city " << No << " with "
		<< warrior[firstAttack]->lifePoint << " elements and force "
		<< warrior[firstAttack]->aggressivity << endl;//输出信息
	if (warrior[!firstAttack]->lifePoint <= 0)//敌方死了！
	{
		loser = !firstAttack;
		cout << t << (*warrior[!firstAttack]) << " was killed in city " << No << endl;
		work(t, firstAttack);
		if (warrior[loser]->kind == 3)//lion的情况，吸取对方生命元
		{
			warrior[!loser]->lifePoint += tempLifeNum[loser];
		}
		return loser;
	}
	else if (warrior[!firstAttack]->kind != 1)//敌方没死，且不是ninja，需要反击！
	{
		cout << t << (*warrior[!firstAttack]) << " fought back against "
			<< (*warrior[firstAttack]) << " in city " << No << endl;
		warrior[firstAttack]->beFoughtBack(*warrior[!firstAttack]);//输出反击信息
		if (warrior[firstAttack]->lifePoint <= 0)//反击使己方死了！
		{
			loser = firstAttack;
			cout << t << (*warrior[loser]) << " was killed in city " << No << endl;
			work(t, !loser);
			if (warrior[loser]->kind == 3)//lion的情况，吸取lion的生命元
			{
				warrior[!loser]->lifePoint += tempLifeNum[loser];
			}
			return loser;
		}
	}
	change(t, k);//都没死，执行双方都活着的一些变化
	return -1;
}
int City::simulate(Time& t, int k)
{
	//与fight函数的区别，在于仅仅模拟，不做出实质改变
	int tempLifeNum[2] = { warrior[0]->lifePoint,warrior[1]->lifePoint };
	int loser;
	warrior[!firstAttack]->beFought(*warrior[firstAttack]);
	if (warrior[!firstAttack]->lifePoint <= 0)
	{
		loser = !firstAttack;
		return loser;
	}
	else if (warrior[!firstAttack]->kind != 1)//不是ninja
	{
		warrior[firstAttack]->beFoughtBack(*warrior[!firstAttack]);
		if (warrior[firstAttack]->lifePoint <= 0)
		{
			loser = firstAttack;
			return loser;
		}
	}
	return -1;
}

//World类
World::World(int caseNum):end(0)
{
	cin >> startLifePoint >> cityNum >> arrowAttack >> loyaltyLost >> limitTime;
	for (int i = 0; i < 5; i++)
		cin >> startWarriorLifeNum[i];
	for (int i = 0; i < 5; i++)
		cin >> startWarriorAggressivity[i];
	cities = new City[cityNum + 2];
	for (int i = 0; i < cityNum + 2; i++)
		cities[i].set(i);//设置立场
	for (int i = 0; i < 2; i++)
		warrior[i] = new Warrior[limitTime / 60 + 5];
	time.setLimit(limitTime);
	cout << "Case " << caseNum << ":" << endl;
	headquarter[RED].set(startLifePoint, RED);
	headquarter[BLUE].set(startLifePoint, BLUE);
}
void World::produceWarrior(int stance)
{
	auto nowLife = headquarter[stance].lifeNum;//当前司令部生命元
	auto nextProduceLife = startWarriorLifeNum[workOrder[stance][headquarter[stance].nextProduce]];//计算下一个要制造的武士所消耗生命元
	int searchingNum = 0;
	bool check = false, lifeNum = 0;
	int temp = 1;
	if (lifeNum > Warrior::birthData[workOrder[stance][(nextProduceLife + temp) % 5]])//循环考察
	{
		lifeNum -= Warrior::birthData[workOrder[stance][(nextProduceLife + temp) % 5]];
		int Number = 1;
		switch (workOrder[stance][(nextProduceLife + temp) % 5])
		{
		case 0:
			headquarter->points[Number] = new Dragon(Number + 1, this->headquarter);
			break;
		case 1:
			headquarter->points[Number] = new Ninja(Number + 1, this->headquarter);
			break;
		case 2:
			headquarter->points[Number] = new Iceman(Number + 1, this->headquarter);
			break;
		case 3:
			headquarter->points[Number] = new Lion(Number + 1, this->headquarter);
			break;
		case 4:
			headquarter->points[Number] = new Wolf(Number + 1, this->headquarter);
			break;
		}
	}
	if (nowLife >= nextProduceLife)//符合条件，可以继续制造武士
	{
		auto tempNum = ++headquarter[stance].sumWarriorNum;
		auto tempLocation = (stance == 1) ? cityNum + 1 : 0;
		headquarter[stance].lifeNum -= nextProduceLife;
		warrior[stance][tempNum].set(time, stance, headquarter[stance].sumWarriorNum, cityNum, workOrder[stance][headquarter[stance].nextProduce]
			, nextProduceLife, startWarriorAggressivity[workOrder[stance][headquarter[stance].nextProduce]], headquarter[stance].lifeNum);
		cities[tempLocation].warrior[stance] = &warrior[stance][tempNum];//设置武士信息

		headquarter[stance].nextProduce++;//下一个要制造的武士
		headquarter[stance].nextProduce %= 5;//下一个要制造的武士
	}
}
void World::march()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 1; j <= headquarter[i].sumWarriorNum; j++)//枚举
		{
			if (warrior[i][j].isAlive)//死的武士就不必处理了
			{
				cities[warrior[i][j].position].warrior[i] = NULL;//原位置清空
				warrior[i][j].match();//行军
				cities[warrior[i][j].position].warrior[i] = &warrior[i][j];//新位置占领
			}
		}
	}
}
void World::work()
{
	for (int i = 0; i <= cityNum + 1; i++)//枚举
	{
		for (int j = 0; j < 2; j++)
		{
			if (cities[i].warrior[j])//有武士
			{
				cout << time;
				if (i == 0 || (i == cityNum + 1))//如果位置在司令部
				{
					headquarter[j].reach++;
					cities[i].warrior[j]->reachDestination();//到达目的地
					cities[i].warrior[j] = NULL;
					if ((headquarter[j].reach == 2))
					{
						cout << time << colorName[!j] << " headquarter was taken" << endl;
						end = 1;//一方司令部被占了，游戏结束！注意这里不要直接return 0，因为可能还有同一时刻发生的事件需要输出
					}
				}
				else
					cities[i].warrior[j]->showmarch();//位置不在司令部，只是普通的行军而已
			}
		}
	}
}
void World::earnLifePoint(int i)
{
	for (int k = 0; k < 2; k++)
	{
		if (!cities[i].warrior[k] && cities[i].warrior[!k])//本城市只有我自己
		{
			headquarter[!k].lifeNum += cities[i].lifeNum;//收获生命元
			cout << time << *(cities[i].warrior[!k]) << " earned " << cities[i].lifeNum
				<< " elements for his headquarter" << endl;
			cities[i].lifeNum = 0;//城市生命元被收割
		}
	}
}
void World::releaseArrow()
{
	for (int i = 1; i <= cityNum; i++)
	{
		int dx[] = { 1,-1 };
		for (int j = 0; j < 2; j++)
		{
			if (i + dx[j] >= 1 && i + dx[j] <= cityNum)//下一个地方的城市位置合法
			{
				if (cities[i].warrior[j] && cities[i + dx[j]].warrior[!j])//下一个地方有敌军
				{
					if (cities[i].warrior[j]->arrowNum > 0)//自己手里有弓箭
					{
						cities[i + dx[j]].warrior[!j]->lifePoint -= arrowAttack;//放箭射杀
						cities[i].warrior[j]->arrowNum--;//用完就少了
						if (cities[i + dx[j]].warrior[!j]->lifePoint <= 0)//杀死敌军
							cout << time << *(cities[i].warrior[j]) << " shot and killed " << *(cities[i + dx[j]].warrior[!j]) << endl;
						else//没杀死敌军
							cout << time << *(cities[i].warrior[j]) << " shot" << endl;
					}
				}
			}
		}
	}
}
void World::releaseBomb()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].warrior[0] && cities[i].warrior[1])//有两个武士
		{
			if (cities[i].warrior[0]->lifePoint > 0 && cities[i].warrior[1]->lifePoint > 0)//双方都活着
			{
				auto temp1 = *cities[i].warrior[0];//记录模拟前状态
				auto temp2 = *cities[i].warrior[1];//记录模拟前状态
				int temp = cities[i].simulate(time, loyaltyLost); //模拟一次战斗!！
				*cities[i].warrior[0] = temp1;//恢复模拟前原状态
				*cities[i].warrior[1] = temp2;//恢复模拟前原状态
				if (temp == 0 && cities[i].warrior[0]->bombNum)//如果模拟结果是蓝方胜，红方将使用炸弹
				{
					cout << time << *(cities[i].warrior[0]) << " used a bomb and killed " << *(cities[i].warrior[1]) << endl;
					cities[i].warrior[0]->lifePoint = 0;//同归于尽
					cities[i].warrior[1]->lifePoint = 0;//同归于尽
				}
				if (temp == 1 && cities[i].warrior[1]->bombNum)//如果模拟结果是红方胜，蓝方将使用炸弹
				{
					cout << time << *(cities[i].warrior[1]) << " used a bomb and killed " << *(cities[i].warrior[0]) << endl;
					cities[i].warrior[0]->lifePoint = 0;//同归于尽
					cities[i].warrior[1]->lifePoint = 0;//同归于尽
				}
			}
		}
	}
}
void World::giveBonus(int stance, int position, int& bonus)
{
	//获得奖励
	bonus += cities[position].lifeNum;//收获城市生命元
	cities[position].warrior[!stance]->isAlive = 0;//对方死了
	cities[position].warrior[!stance] = NULL;//对方死了，清除指针
	cities[position].lifeNum = 0;
	if (headquarter[stance].lifeNum - 8 > 0)//司令部还可以给予奖励
	{
		headquarter[stance].lifeNum -= 8;
		cities[position].warrior[stance]->lifePoint += 8;
	}
}
void World::output()
{
	for (int i = headquarter[0].sumWarriorNum; i > 0; i--)
	{
		//如果还活着或者已经到达对方司令部，就输出！
		if (warrior[0][i].isAlive)
		{
			cout << time;
			warrior[0][i].output();
		}
		else if (warrior[0][i].hasArrived)
		{
			cout << time;
			warrior[0][i].output();
		}
	}
	for (int i = 1; i <= headquarter[1].sumWarriorNum; i++)
	{
		//如果还活着或者已经到达对方司令部，就输出！
		if (warrior[1][i].isAlive)
		{
			cout << time;
			warrior[1][i].output();
		}
		else if (warrior[1][i].hasArrived)
		{
			cout << time;
			warrior[1][i].output();
		}
	}
}
void World::fight()
{
	int A = 0, B = 0;
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].warrior[0] && cities[i].warrior[1])//该城市有两个武士
		{
			if (cities[i].warrior[0]->lifePoint <= 0 && cities[i].warrior[1]->lifePoint <= 0)//双方都死了
			{
				cities[i].warrior[0]->isAlive = 0;
				cities[i].warrior[1]->isAlive = 0;
				cities[i].warrior[0] = cities[i].warrior[1] = NULL;
			}
			else if (cities[i].warrior[0]->lifePoint <= 0)//红方死了
			{
				cities[i].work(time, 1);
				giveBonus(1, i, B);//蓝B获得奖励
			}
			else if (cities[i].warrior[1]->lifePoint <= 0)//蓝方死了
			{
				cities[i].work(time, 0);
				giveBonus(0, i, A);//红A获得奖励
			}
			else
			{
				//双方都活着，准备开战！
				int temp = cities[i].fight(time,loyaltyLost);
				if (temp == 0)//红方输了，蓝B获得奖励
				{
					giveBonus(1, i, B);
				}
				else if (temp == 1)//蓝方输了，红A获得奖励
				{
					giveBonus(0, i, A);
				}
			}
		}
		else if (cities[i].warrior[0] != NULL && cities[i].warrior[0]->lifePoint <= 0)//一方无武士
		{
			cities[i].warrior[0]->isAlive = 0;
			cities[i].warrior[0] = NULL;
		}
		else if (cities[i].warrior[1] != NULL && cities[i].warrior[1]->lifePoint <= 0)//一方无武士
		{
			cities[i].warrior[1]->isAlive = 0;
			cities[i].warrior[1] = NULL;
		}
	}
	headquarter[0].lifeNum += A;//司令部回收生命元
	headquarter[1].lifeNum += B;
}
void World::escape(int position, int stance)
{
	if (cities[position].warrior[stance]->kind == 3)
	{
		if (cities[position].warrior[stance]->isAlive)
		{
			if (cities[position].warrior[stance]->loyalty <= 0)
			{
				//忠诚度降至0或0以下，则该lion逃离战场,永远消失。但是已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑。
				cout << time << colorName[stance] << " lion " << cities[position].warrior[stance]->No << " ran away" << endl;
				cities[position].warrior[stance]->isAlive = 0;
				cities[position].warrior[stance] = NULL;
			}
		}
	}
}
void World::operation()
{
	while (true)
	{
		//在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。
		produceWarrior(0), produceWarrior(1);
		//在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。
		if ((time += 5) == 0)
			break;
		for (int i = 0; i <= cityNum + 1; i++)
			for (int j = 0; j < 2; j++)
				if (cities[i].warrior[j])
					escape(i, j);
		//在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。
		//或从和敌军司令部相邻的城市到达敌军司令部。
		if ((time += 5) == 0)
			break;
		march();
		work();
		//在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走。
		if (end)
			break;
		if ((time += 10) == 0)
			break;
		for (int i = 1; i <= cityNum; i++)
			cities[i].produceElements();
		//在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，
		//并立即将这些生命元传送到其所属的司令部。
		if ((time += 10) == false)
			break;
		for (int i = 1; i <= cityNum; i++)
			earnLifePoint(i);
		//在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。注意，放箭不算是战斗，
		//因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。
		if ((time += 5) == false)
			break;
		releaseArrow();
		//在每个小时的第38分，拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽。
		if ((time += 3) == false)
			break;
		releaseBomb();
		//在每个小时的第40分：在有两个武士的城市，会发生战斗。 如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，
		//而且存活者视为获得了战斗的胜利。此情况下不会有“武士主动攻击”，“武士反击”，“武士战死”的事件发生，
		//但战斗胜利后应该发生的事情都会发生。如Wolf一样能缴获武器，旗帜也可能更换，等等。
		//在此情况下,Dragon同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。
		if ((time += 2) == false)
			break;
		fight();
		//在每个小时的第50分，司令部报告它拥有的生命元数量。
		if ((time += 10) == false)
			break;
		for (int i = 0; i < 2; i++)
			cout << time << headquarter[i];
		//在每个小时的第55分，每个武士报告其拥有的武器情况。
		if ((time += 5) == false)
			break;
		output();
		//在每小时的第60分，即整点，循环。
		if ((time += 5) == false)
			break;
	}
}
void World::myDelete()
{
	delete[] cities;
	delete[] warrior[0];
	delete[] warrior[1];
}

//以下是main函数----------------------------------------------------------
int main()
{
	int num;
	cin >> num;//输入总数
	const int iterator = num;
	while (num--)
	{
		World world(iterator - num);//分别处理
		world.operation();//整个魔兽世界的运行
		world.myDelete();//每组数据操作结束后，删除内存冗余
	}
	return 0;
}