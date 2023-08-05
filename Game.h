#ifndef GAME_H
#define GAME_H

#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView
{
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void start();
    void createBlockCol(double x);
    void creatBlockGrid();
    void checkGameStatus();
    void gameOver();
    void checkWin();
    void showWin();
    void showScore();

    // public attributes
    QGraphicsScene* scene;
    bool inGame;
    bool isWon;
    int score;
    int numBlocks = 48;
private:
    int widthScene = 435;
    int heightScene = 600;
    int numRows = 6;
    int numColumns = 8;
    int spaceBetweenBlocks = 52;
    int spaceBetweenSceneAndBlock = 10;
    int spaceBetweenBallAndScene = 150;
    int spaceBetweenPaddleAndScene = 30;
};

#endif // GAME_H
