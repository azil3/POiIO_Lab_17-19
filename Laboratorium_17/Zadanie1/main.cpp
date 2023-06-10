#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Character {
    string name;
    int strength;
    int speed;
    int agility;
};

void createCharacter(Character* character, int availablePoints) {
    cout << "Tworzenie postaci" << endl;
    cout << "Podaj nazwê postaci: ";
    cin >> character->name;

    cout << "Masz " << availablePoints << " punktów do rozdysponowania." << endl;

    do {
        cout << "Podaj wartoœæ atrybutu si³y (0-" << availablePoints << "): ";
        cin >> character->strength;
    } while (character->strength < 0 || character->strength > availablePoints);

    availablePoints -= character->strength;

    do {
        cout << "Podaj wartoœæ atrybutu szybkoœci (0-" << availablePoints << "): ";
        cin >> character->speed;
    } while (character->speed < 0 || character->speed > availablePoints);

    availablePoints -= character->speed;
    character->agility = availablePoints;

    cout << "Postaæ zosta³a utworzona." << endl;
}

Character generateEnemy() {
    Character enemy;
    enemy.name = "Przeciwnik";
    enemy.strength = rand() % 10 + 1;
    enemy.speed = rand() % 10 + 1;
    enemy.agility = rand() % 10 + 1;

    return enemy;
}

void fight(const Character& player, const Character& enemy) {
    cout << "Rozpoczyna siê walka!" << endl;
    cout << "Gracz: " << player.name << " vs Przeciwnik: " << enemy.name << endl;

    if (player.strength > enemy.strength) {
        cout << "Gracz wygrywa pojedynek!" << endl;
    } else if (player.strength < enemy.strength) {
        cout << "Gracz przegrywa pojedynek!" << endl;
    } else {
        cout << "Remis! Nikt nie wygrywa pojedynku." << endl;
    }
}

int main() {
    setlocale(LC_ALL,"polish");
    srand(time(NULL));

    Character player;
    createCharacter(&player, 10);

    cout << "Postaæ gracza:" << endl;
    cout << "Nazwa: " << player.name << endl;
    cout << "Si³a: " << player.strength << endl;
    cout << "Szybkoœæ: " << player.speed << endl;
    cout << "Zwinnoœæ: " << player.agility << endl;

    Character enemy = generateEnemy();

    fight(player, enemy);

    return 0;
}
