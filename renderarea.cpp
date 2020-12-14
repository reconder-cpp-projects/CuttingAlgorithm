#include "renderarea.h"

#include <QPainter>
#include <QPainterPath>
#include <QString>
#include <QtWidgets>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    shape = Polygon;
    antialiased = false;
    transformed = false;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
    update();
}

void RenderArea::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}

void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}



void RenderArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}



void RenderArea::setTransformed(bool transformed)
{
    this->transformed = transformed;
    update();
}

void RenderArea::initializeSheet(QString sheetWidth, QString sheetHeight)
{
    double width = sheetWidth.toDouble();
    double height = sheetHeight.toDouble();
    rm.InitializeSheet(width, height);
    update();
}

void RenderArea::addRectangle(QString rectangleWidth, QString rectangleHeight)
{
    double width = rectangleWidth.toDouble();
    double height = rectangleHeight.toDouble();
    rm.AddRectangle(width, height);
    update();
};

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QTextStream out(stdout);
    vector<Recta> rectangles = rm.GetLayout();
    Recta sheet = rm.GetSheet();
    out << "Here" << endl;



//    QPainterPath path;
//    path.moveTo(20, 80);
//    path.lineTo(20, 30);
//    path.cubicTo(80, 0, 50, 50, 80, 80);


    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);
    out << "Here" << endl;
    QRect rect(0, 0, sheet.x, sheet.y);
    painter.save();
    painter.translate(0, 0);
    painter.drawRect(rect);
    painter.restore();
    out << "Here" << endl;
    int num = 0;
    for(Recta r : rectangles)
    {
        if (r.pos.first == -100) { emit throwDialog(num); break;}
        else
        {
        num++;
        QRect rect(r.pos.first, r.pos.second, r.x, r.y);
        out << "pos.x: " << r.pos.first << ", pos.y: " << r.pos.second << ", x: " << r.x << ", y: " << r.y << endl;
        painter.save();
        painter.drawRect(rect);
        painter.restore();
        }
    }
    out << num << endl;
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

