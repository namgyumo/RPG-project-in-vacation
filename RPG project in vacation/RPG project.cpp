#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<random>
#include<ctime>
#include<memory>

class Living {
protected:
	std::string name;
	int age{};
	int damage_init{};
	int hp_init{};
	int defence_init{};
	int lv{};
	bool live{};
public:
	Living(std::string name, int age, int damage_init, int hp_init, int defence_init,int lv,bool live) noexcept :
		name(std::move(name)),age(age), damage_init(damage_init), hp_init(hp_init), defence_init(defence_init),lv(lv),live(live) {}

	virtual ~Living() = default;

	const std::string& get_name() const noexcept { return name; }
	int get_age() const noexcept { return age; }
	int get_damage_init() const noexcept { return damage_init; }
	int get_hp_init() const noexcept { return hp_init; }
	int get_defence_init() const noexcept { return defence_init; }
	int get_lv() const noexcept { return lv; }
	bool get_live() const noexcept{ return live; }
	
	void set_name(std::string new_name) noexcept { name = new_name; }
	void set_age(int new_age) noexcept { age = new_age; }
	void set_damage_init(int new_damage_init) noexcept { damage_init = new_damage_init; }
	void set_hp_init(int new_hp_init) noexcept { hp_init = new_hp_init; }
	void set_defence_init(int new_defence_init) noexcept { defence_init = new_defence_init; }
	void set_lv(int new_lv) noexcept { lv = new_lv; }
	void set_live(bool new_live) { live = new_live; }
};

enum class CharacterType {
	Warrior = 1,
	Wizard = 2,
	Knight = 3,
	Archer = 4,
};

class Character : public Living {
private:
	CharacterType character_type{};
public:
	Character(std::string name, int age, int damage_init, int hp_init, int defence_init,int lv,bool live, CharacterType character_type) noexcept :
		Living(std::move(name), age, damage_init, hp_init, defence_init, lv,live), character_type(character_type) {
	}

	CharacterType get_character_type() const noexcept { return character_type; }
	void set_character_type(CharacterType new_character_type) noexcept { character_type = new_character_type; }
};

enum class MonsterType {
	Undead = 1,
	Humanoid = 2,
	Animal = 3,
	Dragon = 4,
};

class Monster : public Living {
private:
	MonsterType monster_type{};
public:
	Monster(std::string name, int age, int damage_init, int hp_init, int defence_init,int lv,bool live, MonsterType monster_type) noexcept:
		Living(std::move(name), age, damage_init, hp_init, defence_init, lv,live), monster_type(monster_type) {
	}
	MonsterType get_monster_type() const noexcept { return monster_type; }
	void set_monster_type(MonsterType new_monster_type) noexcept { monster_type = new_monster_type; }
};

class Character_Manager {
private:
	std::vector<std::unique_ptr<Character>> characters;
public:
	Character* make_character(std::string name, int age, CharacterType character_type) {
		int damage_init, hp_init, defence_init,lv = 1,live = true;
		switch (character_type) {
		case CharacterType::Warrior: damage_init = 10; hp_init = 20; defence_init = 5; break;
		case CharacterType::Wizard: damage_init = 15; hp_init = 15; defence_init = 15; break;
		case CharacterType::Knight: damage_init = 8; hp_init = 25; defence_init = 8; break;
		case CharacterType::Archer: damage_init = 12; hp_init = 18; defence_init = 10; break;
		}
		characters.push_back(std::make_unique<Character>(
			std::move(name), age, damage_init, hp_init, defence_init,lv,live));
		return characters.back().get();
	}
	const std::vector<std::unique_ptr<Character>>& all() const noexcept { return characters; }

	Character* Find_by_name(const std::string& name) {
		for (int i = 0; i<characters.size(); i++) {
			if (characters[i]->get_name() == name) { return characters[i].get(); }
		}
	}
	
};

class Monster_Manager {
	std::vector<std::unique_ptr<Monster>> monsters;
public:
	Monster* make_monster(const std::string& name, int age,int damage_init,int hp_init,int defence_init,int lv ) {
		bool live = true;
		monsters.push_back(std::make_unique<Monster>(std::move(name), age, damage_init, hp_init, defence_init, lv,live));
		return monsters.back().get();
	}
	std::vector<std::unique_ptr<Monster>>& all() { return monsters; }

	Monster* find_by_name(const std::string& name) {
		for (int i = 0; i < monsters.size(); i++) {
			if (monsters[i]->get_name() == name) {
				return monsters[i].get();
			}
		}
	}
	
};

class Map {
public:
	struct Map_node {
		int x, y;
		bool visited{false};
		bool char_here{false};
		struct Map_node* front{ nullptr };
		struct Map_node* back{ nullptr };
		struct Map_node* left{ nullptr };
		struct Map_node* right{ nullptr };
		Monster* monster{nullptr};
	};
	Map_node* map_creation(int x,int y) {
		Map_node* new_map = new Map_node;
		new_map->x = x;
		new_map->y = y;
		return new_map;
	}
	void make_map(int max_x, int max_y) {
		std::vector<std::vector<Map_node*>> grid;
		grid.resize(max_y);
		for (int y = 0; y < max_y; y++) {
			grid[y] = std::vector<Map_node*>(max_x, nullptr);
		}

		for (int y = 0; y < max_y; y++) {
			for (int x = 0; x < max_x; x++) {
				grid[y][x] = map_creation(x, y);
			}
		}

		for (int y = 0; y < max_y; y++) {
			for (int x = 0; x < max_x; x++) {
				if (y > 0) {
					grid[y][x]->back = grid[y - 1][x];
				}
				if (x > 0) {
					grid[y][x]->left = grid[y][x - 1];
				}
				if (y < max_y-1) {
					grid[y][x]->front = grid[y + 1][x];
				}
				if (x < max_x-1) {
					grid[y][x]->right = grid[y][x + 1];
				}
			}
		}
	}
	
};