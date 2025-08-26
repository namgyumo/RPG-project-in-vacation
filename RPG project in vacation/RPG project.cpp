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
public:
	Living(std::string name, int age, int damage_init, int hp_init, int defence_init) noexcept :
		name(std::move(name)),age(age), damage_init(damage_init), hp_init(hp_init), defence_init(defence_init) {}

	virtual ~Living() = default;

	const std::string& get_name() const noexcept { return name; }
	int get_age() const noexcept { return age; }
	int get_damage_init() const noexcept { return damage_init; }
	int get_hp_init() const noexcept { return hp_init; }
	int get_defence_init() const noexcept { return defence_init; }
	
	void set_name(std::string new_name) noexcept { name = new_name; }
	void set_age(int new_age) noexcept { age = new_age; }
	void set_damage_init(int new_damage_init) noexcept { damage_init = new_damage_init; }
	void set_hp_init(int new_hp_init) noexcept { hp_init = new_hp_init; }
	void set_defence_init(int new_defence_init) noexcept { defence_init = new_defence_init; }
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
	Character(std::string name, int age, int damage_init, int hp_init, int defence_init, CharacterType character_type) noexcept :
		Living(std::move(name), age, damage_init, hp_init, defence_init), character_type(character_type) {
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
	Monster(std::string name, int age, int damage_init, int hp_init, int defence_init, MonsterType monster_type) noexcept:
		Living(std::move(name), age, damage_init, hp_init, defence_init), monster_type(monster_type) {
	}
	MonsterType get_monster_type() const noexcept { return monster_type; }
	void set_monster_type(MonsterType new_monster_type) noexcept { monster_type = new_monster_type; }
};

class Character_Manager {
private:
	std::unique_ptr<Character> character;
public:
	Character* make_character(std::string name, int age, CharacterType character_type) {
		int damage_init, hp_init, defence_init;
		switch (character_type) {
		case CharacterType::Warrior: damage_init = 10; hp_init = 20; defence_init = 5; break;
		case CharacterType::Wizard: damage_init = 15; hp_init = 15; defence_init = 15; break;
		case CharacterType::Knight: damage_init = 8; hp_init = 25; defence_init = 8; break;
		case CharacterType::Archer: damage_init = 12; hp_init = 18; defence_init = 10; break;
		}
		character = std::make_unique<Character>(
			std::move(name), age, damage_init, hp_init, defence_init, character_type
		);
		return character.get();
	}
};
