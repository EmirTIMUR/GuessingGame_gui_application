#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "software.h"

#include <QMessageBox>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_guess->setMaxLength(4);
    ui->lineEdit_answer->setMaxLength(5);

    componentEnabledFalse();

    tableItem = new QTableWidgetItem();
    tableItem->setTextAlignment(Qt::AlignCenter);

    messageBoxFont = new QFont("Times", 12, QFont::Bold);

    softwarePtr = new Software; // oyun başlatıldığında Sofware sınıfından bir nesne oluşturuluyor.
    userPtr = new User;// oyun başlatıldığında User sınıfından bir nesne oluşturuluyor.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_guess_clicked()
{
    QTableWidgetItem *userTableItem = tableItem->clone();
    QString qStrGuess = ui->lineEdit_guess->text();
    std::string guess = qStrGuess.toStdString();

    // kullanıcını tahmini kontrol ediliyor, bir hata yoksa 'Kullanıcı' tablosuna işleniyor.
    if(userPtr->checkGuess(guess))
    {
        userTableItem->setText(qStrGuess);
        int insertRow = ui->table_user->rowCount();
        ui->table_user->insertRow(insertRow);
        ui->table_user->setItem(insertRow, 0, userTableItem);

        //kullanıcın tahminine karşılık yazılım cevap veriyor.
        setUserTableAnswer(softwarePtr->answerToGuess(guess));
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("HATA");
        msgBox.setInformativeText( tr("Hatalı bir tahmin girdiniz!\n"
                                      "Lütfen uygun bir tahmin giriniz."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setFont(*messageBoxFont);
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_answer_clicked()
{
    QTableWidgetItem *softwareTableItem = tableItem->clone();
    QTableWidgetItem *softwareTableItem2 = tableItem->clone();

    QString answer = ui->lineEdit_answer->text();

    //kullanıcının cevabı kontrol ediliyor ve taha yoksa bu 'Software' tablosuna işleniyor.
    if(userPtr->checkAnswer(answer.toStdString()))
    {
        softwareTableItem->setText((QString)answer[1]);
        softwareTableItem2->setText((QString)answer[4]);

        int insertRow = ui->table_software->rowCount();
        ui->table_software->setItem(insertRow - 1, 1, softwareTableItem);
        ui->table_software->setItem(insertRow - 1, 2, softwareTableItem2);

        // kazananın olup olmadığını veya
        // hatalı puanlama sonucu havuzun tamamen boşalıp boşalmadığı kontrol ediyor.
        if(checkWinnerOrError(answer))
            newGame();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("HATA");
        msgBox.setInformativeText(tr("Hatalı bir cevap girdiniz!\n"
                                     "Lütfen uygun bir cevap girin."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setFont(*messageBoxFont);
        msgBox.exec();
    }
}

//başla butonuna basılınca yapılan düzenlemeler.
void MainWindow::on_pushButton_start_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("OYUN BAŞLIYOR");
    msgBox.setInformativeText(tr("İlk hamle sırası sizde!\n"
                                 "Aklınızda bir sayı tutmayı unutmayın."));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setFont(*messageBoxFont);
    msgBox.exec();

    ui->pushButton_start->setEnabled(false);
    ui->lineEdit_guess->setEnabled(true);
    ui->pushButton_guess->setEnabled(true);
}

//çıkış tuşuna basılınca oyundan çıkılıyor.
void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_newGame_clicked()
{
    newGame();
}

//yazılımın cevabı 'Kullanıcı' tablosuna işleniyor.
//kullanıcının kazanıp kazanmadığı kontrol ediliyor.
void MainWindow::setUserTableAnswer(const std::string &answer)
{
    QString plus = QChar(answer[1]);
    QString minus = QChar(answer[4]);

    QTableWidgetItem *userTableItem = tableItem->clone();
    QTableWidgetItem *userTableItem2 = tableItem->clone();

    userTableItem->setText(plus);
    userTableItem2->setText(minus);

    int insertRow = ui->table_user->rowCount();

    ui->table_user->setItem(insertRow -1, 1, userTableItem);
    ui->table_user->setItem(insertRow -1, 2, userTableItem2);

    if(answer[1] == '4')
        userWon = true;

    //bir sonraki hamle için component active/passive düzenlemesi yapılıyor.
    ui->lineEdit_guess->clear();
    ui->lineEdit_guess->setEnabled(false);
    ui->pushButton_guess->setEnabled(false);
    ui->lineEdit_answer->setEnabled(true);
    ui->pushButton_answer->setEnabled(true);

    //yazılımın bir tahmin yapması isteniyor.
    setSoftwareTableGuess();
}


//yazılım bir tahmin yapıyor ve bu 'Software' tablosuna işleniyor.
void MainWindow::setSoftwareTableGuess(void) const
{
    std::string guess = softwarePtr->makeGuess();
    QString qStrGuess = QString::fromStdString(guess);
    QTableWidgetItem *softwareTableItem = tableItem->clone();
    softwareTableItem->setText(qStrGuess);

    int insertRow = ui->table_software->rowCount();
    ui->table_software->insertRow(insertRow);
    ui->table_software->setItem(insertRow, 0, softwareTableItem);
}


//bir kazananın olup olmadığı veya oyunun berabere bitip bitmediğini kontrol eden fonksiyon.
bool MainWindow::isThereWinner(const QString &answer) const
{
    if(answer[1] == '4' || userWon == true)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);;
        msgBox.setWindowTitle("KAZANAN");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setFont(*messageBoxFont);

        if(answer[1] == '4' && userWon == true)
            msgBox.setInformativeText("Oyun berabere bitti.");
        else if(userWon)
            msgBox.setInformativeText("Oyunu kullanıcı kazandı.");
        else
        {
            QString msgQstr = "Oyunu bilgisayar kazandı!\n Bilgisayarın sakladığı sayı: ";
            QString qStrSecret = QString::fromStdString(softwarePtr->getHiddenNumber());

            msgQstr+=qStrSecret;
            msgBox.setInformativeText(msgQstr);
        }

        msgBox.exec();
        return true;
    }

    return false;
}

//kullanıcın cevapları üzerine 'HATALI PUANLAMA'nın var olup olmadığını kontrol eden fonksiyon.
bool MainWindow::checkWinnerOrError(const QString &answer) const
{
    if(!isThereWinner(answer)) // bir kazanan yok ise
    {
        QTableWidgetItem *softwareTableGuessItem =
                ui->table_software->item(ui->table_software->rowCount() - 1, 0);
        QString qStrGuess = softwareTableGuessItem->text();

        softwarePtr->editSet(qStrGuess.toStdString(),answer.toStdString());
        if(softwarePtr->isTheSetEmpty())
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("HATA");
            msgBox.setInformativeText(tr("Puanlamada bir hata yaptınız!\n"
                                         "Oyun tekrar başlatılıyor."));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.setFont(*messageBoxFont);
            msgBox.exec();
        }
        else
        {
            ui->lineEdit_answer->clear();
            ui->lineEdit_answer->setEnabled(false);
            ui->pushButton_answer->setEnabled(false);
            ui->lineEdit_guess->setEnabled(true);
            ui->pushButton_guess->setEnabled(true);

            return false;
        }
    }

    return true;
}

//yeni oyun için gerekli düzenlemeler.
void MainWindow::newGame(void)
{
    softwarePtr = new Software;
    userPtr = new User;

    componentEnabledFalse();
    ui->pushButton_start->setEnabled(true);

    ui->table_user->setRowCount(0);
    ui->table_software->setRowCount(0);

    ui->lineEdit_answer->clear();
    ui->lineEdit_guess->clear();

    userWon = false;
}

void MainWindow::componentEnabledFalse() const
{
    ui->lineEdit_guess->setEnabled(false);
    ui->pushButton_guess->setEnabled(false);

    ui->lineEdit_answer->setEnabled(false);
    ui->pushButton_answer->setEnabled(false);
}
