#include <QApplication>
#include "Game.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMessageBox mbStartGame;
    int startButton;

    // welcome window
    mbStartGame.setText("Start the game?");
    mbStartGame.addButton(QMessageBox::StandardButton::Yes);
    mbStartGame.addButton(QMessageBox::StandardButton::No);
    mbStartGame.setDefaultButton(QMessageBox::StandardButton::Yes);
    startButton = mbStartGame.exec();

    // start the game if answer is yes
    if (startButton == QMessageBox::Yes)
    {
        game = new Game();
        game->show();
        game->start();
        return a.exec();
    }
    else
    {
        QApplication::quit();
    }
}
