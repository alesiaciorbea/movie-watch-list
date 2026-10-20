#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a10.h"

class a10 : public QMainWindow
{
    Q_OBJECT

public:
    a10(QWidget *parent = nullptr);
    ~a10();

private:
    Ui::a10Class ui;
};

