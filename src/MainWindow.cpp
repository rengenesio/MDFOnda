#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    if(objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));

    playing = false;

    // SIZE
    resize(731, 418);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(sizePolicy.hasHeightForWidth());
    setSizePolicy(sizePolicy);

    // WIDGETS E LAYOUT
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    verticalLayout = new QVBoxLayout(centralWidget);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(11, 0, 11, 11);
    setCentralWidget(centralWidget);

    createMenus();
    createToolBar();
    createStatusBar();

    /*connect(ui->actionWireFrame, SIGNAL(toggled(bool)), this, SIGNAL(wireframeClicked(bool)));
    connect(ui->actionLight_Rotation, SIGNAL(toggled(bool)), this, SIGNAL(lightRotationToggle(bool)));
    connect(ui->actionSaveImageAs, SIGNAL(triggered()), this, SIGNAL(saveResultAsImage()));*/
}

MainWindow::~MainWindow()
{
}

void MainWindow::setGLDisplay(GLDisplay *display)
{
    verticalLayout->addWidget(display);
}

void MainWindow::createMenus()
{
    menuBar = new QMenuBar(this);

    menuFile = menuBar->addMenu(tr("&File"));
    actionOpen = new QAction(tr("&Open"), menuFile);
    menuFile->addAction(actionOpen);
    actionSave = new QAction(tr("&Save"), menuFile);
    menuFile->addAction(actionSave);
    actionClose = new QAction(tr("&Close"), menuFile);
    menuFile->addAction(actionClose);
    menuFile->addSeparator();
    actionExit = new QAction(tr("&Exit"), menuFile);
    menuFile->addAction(actionExit);

    menuOptions = menuBar->addMenu(tr("&Options"));
    actionOrigin = new QAction(tr("&Origin"), menuOptions);
    actionOrigin->setCheckable(true);
    actionOrigin->setChecked(false);
    menuOptions->addAction(actionOrigin);
    actionWireFrame = new QAction(tr("&WireFrame"), menuOptions);
    actionWireFrame->setCheckable(true);
    actionWireFrame->setChecked(false);
    menuOptions->addAction(actionWireFrame);
    actionVelocity= new QAction(tr("&Color as Velocity"), menuOptions);
    actionVelocity->setCheckable(true);
    actionVelocity->setChecked(false);
    menuOptions->addAction(actionVelocity);

    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(actionClose, SIGNAL(triggered()), this, SLOT(closeWave()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

    this->setMenuBar(menuBar);
}

void MainWindow::createToolBar()
{
    toolBar = addToolBar(tr("Play"));
    actionRewind = new QAction(QIcon("resources/images/buttons/rewind.png"), "Rewind", toolBar);
    actionRewind->setEnabled(false);
    actionSlower = new QAction(QIcon("resources/images/buttons/slower.png"), "Slower", toolBar);
    actionSlower->setEnabled(false);
    actionPlayPause = new QAction(QIcon("resources/images/buttons/play.png"), "Play", toolBar);
    actionPlayPause->setEnabled(false);
    actionFaster = new QAction(QIcon("resources/images/buttons/faster.png"), "Faster", toolBar);
    actionFaster->setEnabled(false);
    actionForward = new QAction(QIcon("resources/images/buttons/forward.png"), "Forward", toolBar);
    actionForward->setEnabled(false);
    toolBar->addAction(actionRewind);
    toolBar->addAction(actionSlower);
    toolBar->addAction(actionPlayPause);
    toolBar->addAction(actionFaster);
    toolBar->addAction(actionForward);
    toolBar->addSeparator();
    toolBar->addWidget(new QLabel("TIME:"));

    connect(actionRewind, SIGNAL(triggered()), this, SLOT(rewind()));
    connect(actionPlayPause, SIGNAL(triggered()), this, SLOT(playingToggle()));
    connect(actionForward, SIGNAL(triggered()), this, SLOT(forward()));
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("MDFonda");
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files (*.*)"));
    if(fileName.isEmpty())
        return;

    actionRewind->setEnabled(true);
    actionSlower->setEnabled(true);
    actionPlayPause->setEnabled(true);
    actionFaster->setEnabled(true);
    actionForward->setEnabled(true);

    emit(loadWave(fileName));
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), tr("image.png"));
    if(fileName.isEmpty())
        return;

    emit(saveWave(fileName));
}

void MainWindow::closeWave()
{
    actionPlayPause->setIcon(QIcon("resources/images/buttons/play.png"));
    actionRewind->setEnabled(false);
    actionSlower->setEnabled(false);
    actionPlayPause->setEnabled(false);
    actionFaster->setEnabled(false);
    actionForward->setEnabled(false);
}

void MainWindow::rewind()
{
    actionPlayPause->setIcon(QIcon("resources/images/buttons/play.png"));
    playing = false;
    emit(rewindWave());
}

void MainWindow::playingToggle()
{
    if(playing)
    {
        actionPlayPause->setIcon(QIcon("resources/images/buttons/play.png"));
        playing = false;
    }
    else
    {
        actionPlayPause->setIcon(QIcon("resources/images/buttons/pause.png"));
        playing = true;
    }
}

void MainWindow::forward()
{
    actionPlayPause->setIcon(QIcon("resources/images/buttons/play.png"));
    playing = false;
    emit(forwardWave());
}

