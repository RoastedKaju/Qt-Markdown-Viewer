#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // On Input Markdown text changed
    void on_textEdit_textChanged();

    // Display Markdown
    void renderMarkdown();

    // On file open action triggered
    void on_actionOpen_triggered();

private:
    // UI reference
    Ui::MainWindow *ui;
    // Debounce timer
    QTimer* renderTimer;
};
#endif // MAINWINDOW_H
