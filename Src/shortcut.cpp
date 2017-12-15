#include "shortcut.h"



Shortcut::Shortcut(QWidget *parent):
    QPushButton(parent)
{

    globalShortcutID++;
    shortcutID = globalShortcutID;
    title = "Button" +QString::number(shortcutID);
    command = "";
    this->setText(title);
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setMinimumHeight(23);
    this->setMaximumHeight(23);
    this->setMinimumWidth(75);
    this->setMaximumWidth(75);
    this->setStyleSheet("text-align: center");

}

Shortcut::~Shortcut()
{

}

int Shortcut::getShortcutID()
{
    return shortcutID;
}

QString Shortcut::getShortcutTitle()
{
    return title;
}

QString Shortcut::getShortcutCommand()
{
    return command;
}

void Shortcut::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        emit rightClickedSignal(shortcutID, title, command);
    }
    else if(event->button() == Qt::LeftButton)
    {
        emit leftClickedSignal(command);
    }
}

void Shortcut::updateShortcutSlot(int ID, QString newTitle, QString newCommand)
{
   if(shortcutID == ID)
   {
    if(newTitle != title)
    {
        title = newTitle;
        this->setText(title);
    }

    if(command != newCommand)
    {
        command = newCommand;
    }
   }
}

void Shortcut::setShortcutTitle(QString newTitle)
{
    title = newTitle;
    this->setText(title);
}
void Shortcut::setShortcutCommand(QString newCommand)
{
    command = newCommand;
}

int Shortcut::globalShortcutID = 0;


