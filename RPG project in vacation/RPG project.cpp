#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<random>
#include<ctime>
#include<memory>


int random(int min, int max) {// make random 
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
	
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

struct Skill {
	std::string skill_name{};
	std::string skill_exp{};
	int damage_increase{};
	int hp_increase{};
	int defence_increase{};

	std::vector<std::shared_ptr<Skill>>children;
};

class Character : public Living {
private:
	std::vector<std::shared_ptr<Skill>> skills;
	CharacterType character_type{};
	
public:
	Character(std::string name, int age, int damage_init, int hp_init, int defence_init,int lv,bool live, CharacterType character_type,std::vector<std::shared_ptr<Skill>> skills) noexcept :
		Living(std::move(name), age, damage_init, hp_init, defence_init, lv,live), character_type(character_type),skills(skills) {
	}

	CharacterType get_character_type() const noexcept { return character_type; }
	std::vector<std::shared_ptr<Skill>>& get_skill() noexcept { return skills; }
	void set_character_type(CharacterType new_character_type) noexcept { character_type = new_character_type; }
	void set_skill(std::vector<std::shared_ptr<Skill>> new_skills) noexcept { skills = std::move(new_skills); }
	void learn_skill(std::shared_ptr<Skill> skill) { skills.push_back(skill); }
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
			std::move(name), age, damage_init, hp_init, defence_init,lv,live,character_type));
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
	Monster* make_monster(const std::string& name, int age,int damage_init,int hp_init,int defence_init,int lv,MonsterType monster_type) {
		bool live = true;
		monsters.push_back(std::make_unique<Monster>(std::move(name), age, damage_init, hp_init, defence_init, lv,live,monster_type));
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

	std::string to_string(MonsterType type) {
		switch (type) {
		case MonsterType::Undead:   return "Undead";
		case MonsterType::Humanoid: return "Humanoid";
		case MonsterType::Animal:   return "Animal";
		case MonsterType::Dragon:   return "Dragon";
		}
	}

	Monster* make_random_monster(int lv) {

		std::string name_data[21] = { "Angry", "Brutal", "Cunning", "Dark", "Elder",
		"Fierce", "Giant", "Hungry", "Infernal", "Jeweled",
		"Keen", "Lethal", "Mighty", "Nimble", "Obsidian",
		"Poisonous", "Quick", "Ruthless", "Savage", "Terrifying" };

		int typenum = random(1, 100);
		if (typenum > 41) { typenum = 1; }
		else if (typenum > 61) { typenum = 2; }
		else if (typenum > 91) { typenum = 3; }
		else { typenum = 4; }
		MonsterType monster_type = static_cast<MonsterType>(typenum);
		int damage_init, hp_init, defence_init;
		switch (monster_type) {
		case MonsterType::Undead: damage_init = 8; hp_init = 15; defence_init = 4; break;
		case MonsterType::Humanoid: damage_init = 15; hp_init = 20; defence_init = 8; break;
		case MonsterType::Animal: damage_init = 6; hp_init = 15; defence_init = 13; break;
		case MonsterType::Dragon: damage_init = 20; hp_init = 25; defence_init = 3; break;
		}
		damage_init *= 1 + (lv * 0.5);
		hp_init *= 1 + (lv * 0.5);
		defence_init *= 1 + (lv * 0.5);
		std::string name = name_data[random(0, 19)] +" "+ to_string(monster_type);
		int age = random(1, 500);
		Monster* monster = make_monster(name, age, damage_init, hp_init, defence_init, lv, monster_type);
		return monster;
	}
	
};

class Map {
public:
	struct Map_node {
		int x, y;
		bool visited{ false };
		bool char_here{ false };
		struct Map_node* front{ nullptr };
		struct Map_node* back{ nullptr };
		struct Map_node* left{ nullptr };
		struct Map_node* right{ nullptr };
		Monster* monster{ nullptr };
	};
private:
	Monster_Manager monster_manager;
	std::vector<std::vector<Map_node*>> grid;
public:
	Map_node* map_creation(int x,int y,Monster* monster) {
		Map_node* new_map = new Map_node;
		new_map->x = x;
		new_map->y = y;
		new_map->monster = monster;
		return new_map;
	}
	void make_map(int max_x, int max_y) {
		grid.clear();
		grid.resize(max_y);
		for (int y = 0; y < max_y; y++) {
			grid[y] = std::vector<Map_node*>(max_x, nullptr);
		}

		for (int y = 0; y < max_y; y++) {
			for (int x = 0; x < max_x; x++) {
				int monster_lv = x > y ? x : y;
				Monster* monster = monster_manager.make_random_monster(monster_lv);
				grid[y][x] = map_creation(x, y,monster);
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

class Skill_Tree {
private:
	std::shared_ptr<Skill>root;
	std::vector<std::shared_ptr<Skill>> skills; // 모든 스킬 저장
public:
	// 새 스킬 생성 후 반환
	std::shared_ptr<Skill> make_skill(const std::string& name,
		const std::string& exp,
		int dmg, int hp, int def)
	{
		auto skill = std::make_shared<Skill>();
		skill->skill_name = name;
		skill->skill_exp = exp;
		skill->damage_increase = dmg;
		skill->hp_increase = hp;
		skill->defence_increase = def;
		skills.push_back(skill);
		if (!root) { root = skill; }
		return skill; // 필요하면 밖에서 children 연결 가능
	}

	std::shared_ptr<Skill> get_rood() const { return root; }

	// 디버그용: 전체 스킬 출력
	void print_skills() {
		for (auto& s : skills) {
			std::cout << s->skill_name << " - " << s->skill_exp << "\n";
		}
	}
};

class Skill_Manager {
private:
	Skill_Tree tree;
public:
	void skill_init() {
		// 0차 (루트)
		auto root = tree.make_skill("칼날 배기", "기본 검술로 적을 벤다", 10, 0, 0);

		// 1차 (5개, 원소별 칼날)
		auto fire_slash = tree.make_skill("화염 칼날", "불꽃을 두른 일격", 20, 0, 0);
		auto water_slash = tree.make_skill("물의 칼날", "물결처럼 흐르는 일격", 18, 0, 5);
		auto lightning_slash = tree.make_skill("번개 칼날", "번개의 속도로 벤다", 22, 0, -2);
		auto wind_slash = tree.make_skill("바람의 칼날", "날카로운 바람으로 벤다", 16, 0, 8);
		auto earth_slash = tree.make_skill("대지의 칼날", "대지의 힘으로 적을 내려친다", 15, 10, 10);

		root->children = { fire_slash, water_slash, lightning_slash, wind_slash, earth_slash };

		// 2차 (각 원소마다 2개 → 총 10개)
		auto fire_blast = tree.make_skill("화염 폭발", "불꽃의 폭발을 일으킨다", 40, 0, 0);
		auto fire_guard = tree.make_skill("화염 방패", "불꽃으로 방패를 만든다", 15, 20, 10);
		fire_slash->children = { fire_blast, fire_guard };

		auto water_wave = tree.make_skill("해일", "거대한 파도로 적을 덮친다", 35, 0, 15);
		auto water_guard = tree.make_skill("물의 방패", "물을 응축해 방패를 만든다", 10, 25, 20);
		water_slash->children = { water_wave, water_guard };

		auto lightning_storm = tree.make_skill("번개 폭풍", "번개의 폭풍을 일으킨다", 45, 0, 5);
		auto lightning_guard = tree.make_skill("전격 보호막", "전류를 띤 보호막", 20, 15, 25);
		lightning_slash->children = { lightning_storm, lightning_guard };

		auto wind_storm = tree.make_skill("회오리 바람", "회오리로 적을 휩쓸어버린다", 32, 0, 12);
		auto wind_guard = tree.make_skill("바람 장막", "바람으로 장막을 쳐 막는다", 12, 20, 25);
		wind_slash->children = { wind_storm, wind_guard };

		auto earth_quake = tree.make_skill("대지 진동", "땅을 울려 적을 무너뜨린다", 30, 0, 30);
		auto earth_guard = tree.make_skill("바위 방패", "바위로 방패를 만든다", 10, 35, 30);
		earth_slash->children = { earth_quake, earth_guard };

		// 3차 (2차의 각 스킬마다 2개 → 총 20개)
		fire_blast->children = {
			tree.make_skill("불의 심판", "불의 심판을 내려 적을 소멸시킨다", 80, 0, 0),
			tree.make_skill("용암 분출", "대지를 갈라 용암을 분출시킨다", 70, 20, 10)
		};
		fire_guard->children = {
			tree.make_skill("불꽃 장벽", "불길의 장벽으로 적을 태운다", 60, 40, 20),
			tree.make_skill("불사 효과", "자신을 불꽃으로 감싸 불굴의 힘을 얻는다", 50, 30, 30)
		};

		water_wave->children = {
			tree.make_skill("해일 폭발", "해일을 폭발시켜 광역 피해", 75, 0, 25),
			tree.make_skill("빙결 파도", "파도를 얼려 적을 봉쇄한다", 65, 10, 40)
		};
		water_guard->children = {
			tree.make_skill("얼음 장막", "얼음 장막으로 방어력을 강화한다", 40, 30, 50),
			tree.make_skill("치유의 물결", "물결이 아군을 치유한다", 0, 80, 20)
		};

		lightning_storm->children = {
			tree.make_skill("천둥의 심판", "하늘에서 신의 번개를 내린다", 90, 0, 15),
			tree.make_skill("플라즈마 베기", "플라즈마 칼날로 벤다", 85, 0, 10)
		};
		lightning_guard->children = {
			tree.make_skill("자기장 보호막", "자기장을 형성해 방어", 20, 40, 60),
			tree.make_skill("충격파 반사", "공격을 흡수 후 반사한다", 30, 20, 70)
		};

		wind_storm->children = {
			tree.make_skill("태풍 소환", "거대한 태풍을 소환한다", 70, 20, 30),
			tree.make_skill("칼바람 일격", "칼날 같은 바람으로 벤다", 85, 0, 15)
		};
		wind_guard->children = {
			tree.make_skill("공기 방패", "압축 공기로 방어", 15, 35, 55),
			tree.make_skill("바람의 춤", "민첩성이 상승한다", 40, 30, 40)
		};

		earth_quake->children = {
			tree.make_skill("산맥 붕괴", "산맥을 무너뜨려 광역 피해", 100, 20, 20),
			tree.make_skill("바위 창", "바위를 창처럼 쏜다", 95, 0, 25)
		};
		earth_guard->children = {
			tree.make_skill("대지의 요새", "대지와 하나 되어 방어", 30, 60, 80),
			tree.make_skill("철벽", "무적에 가까운 방어 태세", 20, 80, 100)
		};

			
	}
};