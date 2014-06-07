#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iprojectorfactory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < projector.getNumProjectors(); i++)
    {
        ui->projectorBox->addItem(projector.getNameProjectors(i));
    }

    connect(ui->actionExit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->actionOpen, SIGNAL(triggered()),
            &projector, SLOT(changeOpenPicturePath()));
    connect(ui->actionSave, SIGNAL(triggered()),
            &projector, SLOT(changeSavePicturePath()));

    connect(ui->leftButton, SIGNAL(clicked()),
            &projector, SLOT(changeRotateLeft()));
    connect(ui->rightButton, SIGNAL(clicked()),
            &projector, SLOT(changeRotateRight()));
    connect(ui->upButton, SIGNAL(clicked()),
            &projector, SLOT(changeRotateUp()));
    connect(ui->downButton, SIGNAL(clicked()),
            &projector, SLOT(changeRotateDown()));

    connect(ui->widthNum, SIGNAL(valueChanged(int)),
            &projector, SLOT(changeWidth(int)));
    connect(ui->heightNum, SIGNAL(valueChanged(int)),
            &projector, SLOT(changeHeight(int)));

    connect(ui->projectorBox, SIGNAL(currentIndexChanged(QString)),
            &projector, SLOT(changeSelectedProjector(QString)));

    connect(&projector, SIGNAL(imageIsChanged(QImage*)),
            &adapter, SLOT(drawPicture(QImage*)));
    connect(&adapter, SIGNAL(drawLabel(QPicture)),
            ui->picture, SLOT(setPicture(QPicture)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
