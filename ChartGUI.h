#pragma once
#include <QWidget>
#include <QPainter>
#include "Controller.h"
#include <map>

class ChartGUI : public QWidget {
    Q_OBJECT
public:
    ChartGUI(Controller& controller, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Controller& ctrl;
};