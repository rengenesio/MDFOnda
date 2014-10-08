/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Sep 22 21:02:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H


QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWireFrame;
    QAction *actionSaveImageAs;
    QAction *actionLight_Rotation;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *renderWidget;
    QHBoxLayout *horizontalLayout;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(731, 418);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionWireFrame = new QAction(MainWindow);
        actionWireFrame->setObjectName(QString::fromUtf8("actionWireFrame"));
        actionWireFrame->setCheckable(true);
        actionSaveImageAs = new QAction(MainWindow);
        actionSaveImageAs->setObjectName(QString::fromUtf8("actionSaveImageAs"));
        actionLight_Rotation = new QAction(MainWindow);
        actionLight_Rotation->setObjectName(QString::fromUtf8("actionLight_Rotation"));
        actionLight_Rotation->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        renderWidget = new QWidget(centralWidget);
        renderWidget->setObjectName(QString::fromUtf8("renderWidget"));
        horizontalLayout = new QHBoxLayout(renderWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout->addWidget(renderWidget);

        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionWireFrame);
        toolBar->addAction(actionLight_Rotation);
        toolBar->addAction(actionSaveImageAs);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionWireFrame->setText(QApplication::translate("MainWindow", "WireFrame", 0, QApplication::UnicodeUTF8));
        actionWireFrame->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        actionSaveImageAs->setText(QApplication::translate("MainWindow", "Save Image As", 0, QApplication::UnicodeUTF8));
        actionSaveImageAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionLight_Rotation->setText(QApplication::translate("MainWindow", "Light Rotation", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
