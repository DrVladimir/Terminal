#ifndef SHORTCUTCREATOR_H
#define SHORTCUTCREATOR_H

#include <QDialog>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {
class ShortcutCreator;
}

QT_END_NAMESPACE

class ShortcutCreator : public QDialog
{
    Q_OBJECT

public:
    explicit ShortcutCreator(QWidget *parent = 0);
    ~ShortcutCreator();

signals:
    void updateShortcutSignal(int shortcutID, QString newTitleShortcut, QString newCommandShortcut);
    void deleteShortcutSignal(int shortcutID);

private slots:
    void updateShortcutSlot(int shortcutID, QString newTitleShortcut, QString newCommandShortcut);
    void deleteButtonSlot();
    void okButtonSlot();
    void cancelButtonSlot();

private:
    Ui::ShortcutCreator *ui;
    int currentShortcut = 0;
};

#endif // SHORTCUTCREATOR_H
