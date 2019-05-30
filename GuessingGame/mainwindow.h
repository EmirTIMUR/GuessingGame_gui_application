#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QTableWidgetItem>
#include<string>
#include"software.h"
#include"user.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void on_pushButton_guess_clicked();

    void on_pushButton_answer_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_newGame_clicked();

private:
    void componentEnabledFalse(void) const;
    void setSoftwareTableGuess(void) const;
    void setUserTableAnswer(const std::string &);
    bool isThereWinner(const QString &) const;
    bool checkWinnerOrError(const QString &) const;
    void newGame(void);

    Ui::MainWindow *ui;
    QTableWidgetItem *tableItem;
    QFont *messageBoxFont;

    Software *softwarePtr;
    User *userPtr;

    bool userWon;
};

#endif // MAINWINDOW_H
