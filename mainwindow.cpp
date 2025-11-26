#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmark.h>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renderTimer = new QTimer(this);
    renderTimer->setSingleShot(true);
    renderTimer->setInterval(120);

    connect(renderTimer, &QTimer::timeout, this, &MainWindow::renderMarkdown);

}

MainWindow::~MainWindow()
{
    delete renderTimer;
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    renderTimer->start();
}

void MainWindow::renderMarkdown()
{
    QString md = ui->textEdit->toPlainText();

    char* html_cstr = cmark_markdown_to_html(
        md.toUtf8().data(),
        md.toUtf8().size(),
        CMARK_OPT_DEFAULT
        );

    // Convert to Qt string
    QString html = QString::fromUtf8(html_cstr);

    // Free the memory allocated by cmark
    free(html_cstr);

    // Display
    ui->textEditOutput->setHtml(html);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("All Files (*.*);;Text Files (*.txt)"));

    if (!filePath.isEmpty())
    {
        // Process the selected file, e.g., load its content
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString content = in.readAll();

            // Set the content to our input text box
            ui->textEdit->setText(content);

            file.close();
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Could not open file: %1").arg(file.errorString()));
        }
    }
}

