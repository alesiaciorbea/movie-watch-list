#pragma once
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class StartGUI : public QWidget {
    Q_OBJECT
public:
    StartGUI(QWidget* parent = nullptr);

    bool isSQLiteSelected() const;
    bool isCSVSelected() const;

private:
    QRadioButton* radioText;
    QRadioButton* radioSQLite;
    QRadioButton* radioCSV;
    QRadioButton* radioHTML;
    QPushButton* btnStart;

signals:
    void startApplication(); 
};