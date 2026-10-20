#include "ChartGUI.h"
#include <QPainter>
#include <vector>
#include <map>
#include <QString>

ChartGUI::ChartGUI(Controller& controller, QWidget* parent)
    : QWidget(parent), ctrl(controller) {
    this->setWindowTitle("Movie Genres - Bar Chart");
    this->resize(600, 400);
}

void ChartGUI::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    std::map<std::string, int> genreCounts;
    for (const auto& m : this->ctrl.getRepo().getMovies()) {
        genreCounts[m.getGenre()]++;
    }

    if (genreCounts.empty()) {
        painter.setPen(Qt::white);
        painter.drawText(this->rect(), Qt::AlignCenter, "No data to display.");
        return;
    }

    int maxCount = 0;
    for (const auto& pair : genreCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
        }
    }

    if (maxCount == 0) maxCount = 1;

    int padding = 50;
    int chartWidth = this->width() - 2 * padding;
    int chartHeight = this->height() - 2 * padding;

    int numBars = genreCounts.size();
    int barWidth = chartWidth / numBars;

    for (int i = 0; i <= maxCount; ++i) {
        int y = this->height() - padding - (i * chartHeight) / maxCount;

        painter.setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
        painter.drawLine(padding, y, this->width() - padding, y);

        painter.setPen(Qt::white);
        painter.drawText(padding - 20, y + 5, QString::number(i));
    }

    painter.setPen(QPen(Qt::white, 2));

    painter.drawLine(padding, padding, padding, this->height() - padding);

    painter.drawLine(padding, this->height() - padding, this->width() - padding, this->height() - padding);

    int currentX = padding + 10;

    std::vector<Qt::GlobalColor> colors = { Qt::red, Qt::blue, Qt::green, Qt::cyan, Qt::magenta, Qt::yellow };
    int colorIndex = 0;

    for (const auto& pair : genreCounts) {
        QString genreName = QString::fromStdString(pair.first);
        int count = pair.second;
        int barHeight = (count * chartHeight) / maxCount;
        painter.setBrush(QBrush(colors[colorIndex % colors.size()]));
        painter.setPen(QPen(Qt::black, 1));

        int barY = this->height() - padding - barHeight;
        painter.drawRect(currentX, barY, barWidth - 20, barHeight);

        painter.setPen(Qt::white);
        painter.drawText(currentX, this->height() - padding + 20, genreName);
        painter.drawText(currentX + (barWidth - 20) / 2 - 5, barY - 5, QString::number(count));

        currentX += barWidth;
        colorIndex++;
    }
}