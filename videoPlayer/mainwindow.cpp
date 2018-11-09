#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QIcon"
#include "QPushButton"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);

    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    this->setCentralWidget(vw);

    fullScreenBtn = new QPushButton(this);

    fullScreenBtn->setIcon(QIcon(":/new/images/Icons/expand.png"));

    fullscreenOrNot = false;


    slider = new QSlider(this);
  //  pBar = new QProgressBar(this);

    switcher = 2;
    playOrNot = 0;

    ui->actionpauseBtn->setVisible(false);

    volumeSlider = ui->lydSlider;

    //volumeSlider->setEnabled(false);
    //volumeSlider->setVisible(false);

    player->setVolume(50);

    slider->setOrientation(Qt::Horizontal);

    ui->statusBar->addPermanentWidget(slider);


    ui->statusBar->addPermanentWidget(fullScreenBtn);

    connect(fullScreenBtn, SIGNAL(clicked()), this, SLOT(fullscreenBtnIsclicked()));


    //connect(this, SIGNAL(clicked()), this, SLOT(playerClickedOnce()));
     connect(slider, &QSlider::sliderMoved,player,&QMediaPlayer::setPosition);


    connect(player, &QMediaPlayer::durationChanged,slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged,slider, &QSlider::setValue);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Åben fil", "", "Video file (*.*)");
    on_actionstopBtn_triggered();

    player->setMedia(QUrl::fromLocalFile(fileName));

    on_actionPlayBtn_triggered();

}

void MainWindow::playerClickedOnce(){



    player->pause();

    ui->statusBar->show();
}
void MainWindow::playerDoubleclicked(){


}

void MainWindow::fullscreenBtnIsclicked(){

    if(!fullscreenOrNot){
        vw->setFullScreen(true);
        fullscreenOrNot=true;

    }else{
        vw->setFullScreen(false);
        fullscreenOrNot=false;
    }

}

void MainWindow::on_actionPlayBtn_triggered()
{

   if(player->media().isNull()){

        ui->statusBar->showMessage("Der er ikke indlæst en video");
   }else{


        if(playOrNot==0){
                player->play();
                ui->statusBar->showMessage("Afspiller");
                ui->actionPlayBtn->setIcon(QIcon(":/new/images/Icons/pause.png"));
                playOrNot=1;
                return;
           }
            if(playOrNot==1){
                player->pause();
                ui->statusBar->showMessage("Stoppet...");
                ui->actionPlayBtn->setIcon(QIcon(":/new/images/Icons/play-button.png"));
                playOrNot=0;
                return;
            }

   }


}
void MainWindow::on_actionpauseBtn_triggered(){


}



void MainWindow::on_actionstopBtn_triggered()
{
    player->stop();
    ui->statusBar->showMessage("Afsluttet");

}

void MainWindow::on_actionLyd_triggered()
{
    switch(switcher){
      case(0): ui->actionLyd->setIcon(QIcon(":/new/images/Icons/speaker_lowVol.png")); player->setVolume(33);  break;
      case(1): ui->actionLyd->setIcon(QIcon(":/new/images/Icons/speaker_medVol.png")); player->setVolume(66); break;
      case(2): ui->actionLyd->setIcon(QIcon(":/new/images/Icons/speaker_highVol.png")); player->setVolume(100); break;
      case(3): ui->actionLyd->setIcon(QIcon(":/new/images/Icons/mute.png")); player->setVolume(0); break;

     }
    if(switcher==3){

        switcher=0;

    }else{
        switcher+=1;

    }






}
