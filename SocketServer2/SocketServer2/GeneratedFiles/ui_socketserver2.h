/********************************************************************************
** Form generated from reading UI file 'socketserver2.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCKETSERVER2_H
#define UI_SOCKETSERVER2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocketServer2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SocketServer2Class)
    {
        if (SocketServer2Class->objectName().isEmpty())
            SocketServer2Class->setObjectName(QStringLiteral("SocketServer2Class"));
        SocketServer2Class->resize(600, 400);
        menuBar = new QMenuBar(SocketServer2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        SocketServer2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SocketServer2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SocketServer2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(SocketServer2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SocketServer2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SocketServer2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SocketServer2Class->setStatusBar(statusBar);

        retranslateUi(SocketServer2Class);

        QMetaObject::connectSlotsByName(SocketServer2Class);
    } // setupUi

    void retranslateUi(QMainWindow *SocketServer2Class)
    {
        SocketServer2Class->setWindowTitle(QApplication::translate("SocketServer2Class", "SocketServer2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SocketServer2Class: public Ui_SocketServer2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCKETSERVER2_H
