/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "shortcut.h"
#include "shortcutcreator.h"
#include "mainhandler.h"
#include "filter.h"
#include "filtereditor.h"
#include <QScrollArea>






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings =  new SettingsDialog;
    creator =   new ShortcutCreator;
    handler =   new MainHandler;
    editor =   new FilterEditor;


    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->actionQuit->setEnabled(true);
    ui->sendButton->setEnabled(false);


    initConnections();


    fileUISettings = new QFile("D:/Projects/My project/Terminal/Build/UISettings.ini");
    if (fileUISettings->open(QIODevice::ReadOnly))
    {
        QString line;
        QString title;
        QString command;
        while(!fileUISettings->atEnd())
        {
            line = fileUISettings->readLine();
            if (line.startsWith("Shortcut"))
            {
                line = fileUISettings->readLine();
                if(line.startsWith("Title"))
                {
                    line = fileUISettings->readLine();
                    title = line.replace(QRegExp("\n"),"");
                }
                line = fileUISettings->readLine();
                if(line.startsWith("Command"))
                {
                    line = fileUISettings->readLine();
                    command = line.replace(QRegExp("\n"),"");;
                }

                addShortcut(title,command);
            }
        }
    }
    fileUISettings->close();


}

MainWindow::~MainWindow()
{
   /* fileUISettings->resize(0);

    if(fileUISettings ->open(QFile::WriteOnly))
    {

        QTextStream stream(fileUISettings);

        for(int i = 0; i < ui->shortcutsLayout->count(); i++)
        {
            Shortcut *shortcut = qobject_cast<Shortcut*>(ui->shortcutsLayout->itemAt(i)->widget());
            stream << "Shortcut \n";
            stream << shortcut->getShortcutTitle() + "\n";
            stream << shortcut->getShortcutCommand() + "\n";
            fileUISettings->flush();

            delete shortcut;
        }
    }

    fileUISettings->close();*/
    delete fileUISettings;
    delete editor;
    delete settings;
    delete creator;
    delete handler;
    delete ui;
}

void MainWindow::initConnections()
{

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), ui->comInfo, SLOT(clear()));
    connect(ui->actionConnect,SIGNAL(triggered()),this,SLOT(connectSlot()));
    connect(ui->actionDisconnect,SIGNAL(triggered()),this,SLOT(disconnectSlot()));

    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addShortcutSlot()));
    connect(creator, SIGNAL(deleteShortcutSignal(int)),this,SLOT(deleteShortcutSlot(int)));

    connect(ui->filterEditorButton,SIGNAL(clicked()),editor,SLOT(show()));
    connect(editor, SIGNAL(updateFiltersSignal(QList<FilterInfo>)),this,SLOT(updateFiltersSlot(QList<FilterInfo>)));

    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(commandLineSlot()));

    connect(this,SIGNAL(connectSignal(void*)),handler,SLOT(connectSlot(void*)));
    connect(this,SIGNAL(disconnectSignal()),handler,SLOT(disconnectSlot()));
    connect(this,SIGNAL(commandSignal(QString)),handler,SLOT(commandSlot(QString)));



    connect(handler,SIGNAL(dataSignal(QString)),this,SLOT(getDataSlot(QString)));
    
    connect(handler,SIGNAL(sendAvaliblePortsInfoSignal(std::vector<QStringList>*)),this,SLOT(getAvaliblePortsInfoSlot(std::vector<QStringList>*)));
    connect(this, SIGNAL(sendAvaliblePortsInfoSignal(std::vector<QStringList>*)),settings, SLOT(getAvaliblePortsInfoSlot(std::vector<QStringList>*)));

    connect(settings,SIGNAL(updateAvaliblePortsInfoSignal()),this,SLOT(getUpdateAvaliblePortsInfoSlot()));
    connect(this, SIGNAL(updateAvaliblePortsInfoSignal()),handler, SLOT(getUpdateAvaliblePortsInfoSlot()));




}

void MainWindow::addShortcut(QString title, QString command)
{
    Shortcut *shortcut = new Shortcut(this);
    ui->shortcutsLayout->addWidget(shortcut);
    shortcut->setShortcutTitle(title);
    shortcut->setShortcutCommand(command);

    connect(shortcut, SIGNAL(rightClickedSignal(int,QString,QString)),creator,SLOT(updateShortcutSlot(int,QString,QString)));
    connect(shortcut, SIGNAL(leftClickedSignal(QString)),this,SLOT(commandShortcutSlot(QString)));
    connect(creator,SIGNAL(updateShortcutSignal(int,QString,QString)),shortcut,SLOT(updateShortcutSlot(int,QString,QString)));
}

void MainWindow::addShortcutSlot()
{
    Shortcut *shortcut = new Shortcut(this);
    ui->shortcutsLayout->addWidget(shortcut); 

    connect(shortcut, SIGNAL(rightClickedSignal(int,QString,QString)),creator,SLOT(updateShortcutSlot(int,QString,QString)));
    connect(shortcut, SIGNAL(leftClickedSignal(QString)),this,SLOT(commandShortcutSlot(QString)));
    connect(creator,SIGNAL(updateShortcutSignal(int,QString,QString)),shortcut,SLOT(updateShortcutSlot(int,QString,QString)));

    emit shortcut->rightClickedSignal(shortcut->getShortcutID(),shortcut->getShortcutTitle(),shortcut->getShortcutCommand());

}

void MainWindow::deleteShortcutSlot(int shortcutID)
{
    for(int i = 0; i < ui->shortcutsLayout->count(); i++)
    {
        Shortcut *shortcut = qobject_cast<Shortcut*>(ui->shortcutsLayout->itemAt(i)->widget());
        if(shortcut->getShortcutID() == shortcutID)
        {
            shortcut->hide();
            delete shortcut;
        }
    }
}

void MainWindow::commandShortcutSlot(QString command)
{
    emit commandSignal(command);
}

void MainWindow::commandLineSlot()
{
    emit commandSignal(ui->commandEdit->text());
}

void MainWindow::getDataSlot(QString data)
{
    ui->comInfo->append(data);
}

void MainWindow::connectSlot()
{
    ui->actionConnect->setEnabled(false);
    ui->actionDisconnect->setEnabled(true);
    ui->actionConfigure->setEnabled(false);
    ui->actionQuit->setEnabled(false);
    ui->sendButton->setEnabled(true);

    ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                               .arg(settings->getSettings()->name)
                               .arg(settings->getSettings()->stringBaudRate)
                               .arg(settings->getSettings()->stringDataBits)
                               .arg(settings->getSettings()->stringParity)
                               .arg(settings->getSettings()->stringStopBits)
                               .arg(settings->getSettings()->stringFlowControl));

    emit connectSignal((void*)settings->getSettings());
}

void MainWindow::disconnectSlot()
{
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->actionQuit->setEnabled(true);
    ui->sendButton->setEnabled(false);

    emit disconnectSignal();

}

void MainWindow::getUpdateAvaliblePortsInfoSlot()
{
    emit updateAvaliblePortsInfoSignal();
}

void MainWindow::getAvaliblePortsInfoSlot(std::vector<QStringList> *portsInfo)
{
    emit sendAvaliblePortsInfoSignal(portsInfo);
}

void MainWindow::updateFiltersSlot(QList<FilterInfo> newFiltersList)
{
    int count = ui->filtersLayout->count();
    for(int i = 0; i <count ; i++)
    {
        Filter *filter = qobject_cast<Filter*>(ui->filtersLayout->itemAt(0)->widget());
        filter->hide();
        delete filter;
    }


    for (int filterNumber = 0; filterNumber < newFiltersList.size(); filterNumber++)
    {
        if(newFiltersList[filterNumber].getState())
        {
            Filter *filter = new Filter(newFiltersList[filterNumber].getType(), newFiltersList[filterNumber].getExpresion(),this);
            ui->filtersLayout->addWidget(filter);
            connect(handler,SIGNAL(dataSignal(QString)),filter,SLOT(getDataSlot(QString)));
        }

    }
}
