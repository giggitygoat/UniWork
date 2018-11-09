#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton* fullScreenBtn;
    int switcher;
    int playOrNot;
    bool fullscreenOrNot;
private slots:
    void on_actionopenFile_triggered();

    void on_actionPlayBtn_triggered();

    void on_actionpauseBtn_triggered();

    void on_actionstopBtn_triggered();

    void on_actionLyd_triggered();

    void playerClickedOnce();
    void playerDoubleclicked();

    void fullscreenBtnIsclicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QProgressBar* pBar;
    QSlider* slider;
    QSlider* volumeSlider;


};

#endif // MAINWINDOW_H
