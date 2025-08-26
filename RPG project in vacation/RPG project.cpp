#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Living {
private:
	std::string name;
	int age;
	int damage_init;
	int hp_init;
	int defence_init;
public:
	Living(std::string name, int age, int damage_init, int hp_init, int defence_init) :
		name(name), damage_init(damage_init), hp_init(hp_init), defence_init(defence_init) {}

	std::string get_name() { return name; }
	int get_age() { return age; }
	int get_damage_init() { return damage_init; }
	int get_hp_init() { return hp_init; }
	int get_defence_init() { return defence_init; }
	
	void set_name(std::string new_name) { name = new_name; }
	void set_age(int new_age) { age = new_age; }
	void set_damage_init(int new_damage_init) { damage_init = new_damage_init; }
	void set_hp_init(int new_hp_init) { hp_init = new_hp_init; }
	void set_defence_init(int new_defence_init) { defence_init = new_defence_init; }
};