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
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
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
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QList>
#include "filterinfo.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class SettingsDialog;
class ShortcutCreator;
class MainHandler;
class FilterEditor;
class FilterInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void connectSignal(void *settingsOfConnection);
    void disconnectSignal();
    void commandSignal(QString command);


    void updateAvaliblePortsInfoSignal();
    void sendAvaliblePortsInfoSignal(std::vector<QStringList>* portsInfo);

private slots:   
    void connectSlot();
    void disconnectSlot();
    
    void getUpdateAvaliblePortsInfoSlot();
    void getAvaliblePortsInfoSlot(std::vector<QStringList>* portsInfo);    
        
    void addShortcutSlot();
    void deleteShortcutSlot(int shortcutID);
    void commandShortcutSlot(QString command);

    void commandLineSlot();

    void getDataSlot(QString data);

    void updateFiltersSlot(QList<FilterInfo> newFiltersList);



private:
    void addShortcut(QString title, QString command);

    void initConnections();

private:
    QFile *fileUISettings;
    Ui::MainWindow *ui;
    SettingsDialog *settings;
    ShortcutCreator *creator;
    MainHandler *handler;
    FilterEditor *editor;

    QList<FilterInfo> filtersList;
};

#endif // MAINWINDOW_H
