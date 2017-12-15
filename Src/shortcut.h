#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <QPushButton>
#include <QMouseEvent>

class Shortcut: public QPushButton
{
    Q_OBJECT
public:
    explicit Shortcut(QWidget *parent = 0);
    ~Shortcut();

    static int globalShortcutID;   // Статическая переменная, счетчик номеров кнопок

    int getShortcutID();
    QString getShortcutTitle();
    QString getShortcutCommand();
    void setShortcutTitle(QString newTitle);
    void setShortcutCommand(QString newCommand);


signals:
    void rightClickedSignal(int currentID, QString currentTitle, QString currentCommand);
    void leftClickedSignal(QString command);

private slots:
    void updateShortcutSlot(int ID, QString newTitle, QString newCommand);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    int shortcutID = 0;   // Локальная переменная, номер кнопки
    QString title;
    QString command;

};

#endif // SHORTCUT_H
