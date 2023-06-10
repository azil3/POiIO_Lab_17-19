#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

struct Character {
    std::string name;
    int strength;
    int speed;
    int agility;
};

class RPGGame : public QWidget {
public:
    RPGGame(QWidget *parent = nullptr) : QWidget(parent), availablePoints(10) {
        srand(time(NULL));

        QGridLayout *layout = new QGridLayout(this);

        QLabel *nameLabel = new QLabel("Nazwa postaci:", this);
        layout->addWidget(nameLabel, 0, 0);

        nameLineEdit = new QLineEdit(this);
        layout->addWidget(nameLineEdit, 0, 1);

        QLabel *strengthLabel = new QLabel("Siła:", this);
        layout->addWidget(strengthLabel, 1, 0);

        QHBoxLayout *strengthLayout = new QHBoxLayout;
        layout->addLayout(strengthLayout, 1, 1);

        strengthLineEdit = new QLineEdit(this);
        strengthLayout->addWidget(strengthLineEdit);

        QPushButton *strengthMinusButton = new QPushButton("-", this);
        strengthLayout->addWidget(strengthMinusButton);
        connect(strengthMinusButton, &QPushButton::clicked, this, &RPGGame::decreaseStrength);

        QPushButton *strengthPlusButton = new QPushButton("+", this);
        strengthLayout->addWidget(strengthPlusButton);
        connect(strengthPlusButton, &QPushButton::clicked, this, &RPGGame::increaseStrength);

        QLabel *speedLabel = new QLabel("Szybkość:", this);
        layout->addWidget(speedLabel, 2, 0);

        QHBoxLayout *speedLayout = new QHBoxLayout;
        layout->addLayout(speedLayout, 2, 1);

        speedLineEdit = new QLineEdit(this);
        speedLayout->addWidget(speedLineEdit);

        QPushButton *speedMinusButton = new QPushButton("-", this);
        speedLayout->addWidget(speedMinusButton);
        connect(speedMinusButton, &QPushButton::clicked, this, &RPGGame::decreaseSpeed);

        QPushButton *speedPlusButton = new QPushButton("+", this);
        speedLayout->addWidget(speedPlusButton);
        connect(speedPlusButton, &QPushButton::clicked, this, &RPGGame::increaseSpeed);

        QLabel *agilityLabel = new QLabel("Zwinność:", this);
        layout->addWidget(agilityLabel, 3, 0);

        QHBoxLayout *agilityLayout = new QHBoxLayout;
        layout->addLayout(agilityLayout, 3, 1);

        agilityLineEdit = new QLineEdit(this);
        agilityLayout->addWidget(agilityLineEdit);

        QPushButton *agilityMinusButton = new QPushButton("-", this);
        agilityLayout->addWidget(agilityMinusButton);
        connect(agilityMinusButton, &QPushButton::clicked, this, &RPGGame::decreaseAgility);

        QPushButton *agilityPlusButton = new QPushButton("+", this);
        agilityLayout->addWidget(agilityPlusButton);
        connect(agilityPlusButton, &QPushButton::clicked, this, &RPGGame::increaseAgility);

        QLabel *pointsLabel = new QLabel("Punkty dostępne: 10", this);
        layout->addWidget(pointsLabel, 4, 0, 1, 2);

        QLabel *enemyNameLabel = new QLabel("Przeciwnik:", this);
        layout->addWidget(enemyNameLabel, 5, 0);

        enemyNameLineEdit = new QLineEdit(this);
        enemyNameLineEdit->setReadOnly(true);
        layout->addWidget(enemyNameLineEdit, 5, 1);

        QLabel *enemyStrengthLabel = new QLabel("Siła:", this);
        layout->addWidget(enemyStrengthLabel, 6, 0);

        enemyStrengthLineEdit = new QLineEdit(this);
        enemyStrengthLineEdit->setReadOnly(true);
        layout->addWidget(enemyStrengthLineEdit, 6, 1);

        QLabel *enemySpeedLabel = new QLabel("Szybkość:", this);
        layout->addWidget(enemySpeedLabel, 7, 0);

        enemySpeedLineEdit = new QLineEdit(this);
        enemySpeedLineEdit->setReadOnly(true);
        layout->addWidget(enemySpeedLineEdit, 7, 1);

        QLabel *enemyAgilityLabel = new QLabel("Zwinność:", this);
        layout->addWidget(enemyAgilityLabel, 8, 0);

        enemyAgilityLineEdit = new QLineEdit(this);
        enemyAgilityLineEdit->setReadOnly(true);
        layout->addWidget(enemyAgilityLineEdit, 8, 1);

        QPushButton *createButton = new QPushButton("Stwórz postać", this);
        layout->addWidget(createButton, 9, 0, 1, 2);

        connect(createButton, &QPushButton::clicked, this, &RPGGame::createCharacter);

        setLayout(layout);
    }

private slots:
    void increaseStrength() {
        if (availablePoints > 0) {
            int currentStrength = strengthLineEdit->text().toInt();
            currentStrength++;
            strengthLineEdit->setText(QString::number(currentStrength));

            availablePoints--;
            updatePointsLabel();
        }
    }

    void decreaseStrength() {
        int currentStrength = strengthLineEdit->text().toInt();
        if (currentStrength > 1) {
            currentStrength--;
            strengthLineEdit->setText(QString::number(currentStrength));

            availablePoints++;
            updatePointsLabel();
        }
    }

    void increaseSpeed() {
        if (availablePoints > 0) {
            int currentSpeed = speedLineEdit->text().toInt();
            currentSpeed++;
            speedLineEdit->setText(QString::number(currentSpeed));

            availablePoints--;
            updatePointsLabel();
        }
    }

    void decreaseSpeed() {
        int currentSpeed = speedLineEdit->text().toInt();
        if (currentSpeed > 1) {
            currentSpeed--;
            speedLineEdit->setText(QString::number(currentSpeed));

            availablePoints++;
            updatePointsLabel();
        }
    }

    void increaseAgility() {
        if (availablePoints > 0) {
            int currentAgility = agilityLineEdit->text().toInt();
            currentAgility++;
            agilityLineEdit->setText(QString::number(currentAgility));

            availablePoints--;
            updatePointsLabel();
        }
    }

    void decreaseAgility() {
        int currentAgility = agilityLineEdit->text().toInt();
        if (currentAgility > 1) {
            currentAgility--;
            agilityLineEdit->setText(QString::number(currentAgility));

            availablePoints++;
            updatePointsLabel();
        }
    }

    void createCharacter() {
        std::string name = nameLineEdit->text().toStdString();
        int strength = strengthLineEdit->text().toInt();
        int speed = speedLineEdit->text().toInt();
        int agility = agilityLineEdit->text().toInt();

        Character player;
        player.name = name;
        player.strength = strength;
        player.speed = speed;
        player.agility = agility;

        generateEnemy();

        QString result = "Postać gracza: " + QString::fromStdString(player.name) + " (Siła: " + QString::number(player.strength)
                + ", Szybkość: " + QString::number(player.speed) + ", Zwinność: " + QString::number(player.agility) + ")\n";
        result += "Przeciwnik: " + QString::fromStdString(enemy.name) + " (Siła: " + QString::number(enemy.strength)
                + ", Szybkość: " + QString::number(enemy.speed) + ", Zwinność: " + QString::number(enemy.agility) + ")\n";

        // Symulacja pojedynku - porównanie atrybutów
        if (player.strength > enemy.strength && player.speed > enemy.speed && player.agility > enemy.agility) {
            result += "Gracz wygrywa pojedynek!";
        } else {
            result += "Gracz przegrywa pojedynek!";
        }

        QMessageBox::information(this, "Wynik pojedynku", result);

        reset();
    }

private:
    QLineEdit *nameLineEdit;
    QLineEdit *strengthLineEdit;
    QLineEdit *speedLineEdit;
    QLineEdit *agilityLineEdit;
    QLineEdit *enemyNameLineEdit;
    QLineEdit *enemyStrengthLineEdit;
    QLineEdit *enemySpeedLineEdit;
    QLineEdit *enemyAgilityLineEdit;
    int availablePoints;

    Character enemy;

    void generateEnemy() {
        enemy.name = "Przeciwnik";
        enemy.strength = rand() % 5 + 1;
        enemy.speed = rand() % 5 + 1;
        enemy.agility = rand() % 5 + 1;

        enemyStrengthLineEdit->setText(QString::number(enemy.strength));
        enemySpeedLineEdit->setText(QString::number(enemy.speed));
        enemyAgilityLineEdit->setText(QString::number(enemy.agility));
    }

    void updatePointsLabel() {
        QString pointsText = "Punkty dostępne: " + QString::number(availablePoints);

        // Znajdź widget z etykietą punktów
        QLabel* pointsLabel = nullptr;
        for (int i = 0; i < layout()->count(); i++) {
            QLayoutItem* item = layout()->itemAt(i);
            if (QLabel* label = qobject_cast<QLabel*>(item->widget())) {
                if (label->text().startsWith("Punkty dostępne:")) {
                    pointsLabel = label;
                    break;
                }
            }
        }

        if (pointsLabel) {
            pointsLabel->setText(pointsText);
        }
    }

    void reset() {
        nameLineEdit->clear();
        strengthLineEdit->clear();
        speedLineEdit->clear();
        agilityLineEdit->clear();
        availablePoints = 10;
        updatePointsLabel();
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    RPGGame game;
    game.show();

    return a.exec();
}
