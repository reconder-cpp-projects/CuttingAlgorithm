#ifndef RENDERAREA_H
#define RENDERAREA_H
#include "cutting.h"

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QTextStream>

//! [0]
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                 Chord, Pie, Path, Text, Pixmap };

    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void initializeSheet(QString sheetWidth, QString sheetHeight);
    void addRectangle(QString rectangleWidth, QString rectangleHeight);
public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);
signals:
    void throwDialog(int num);

protected:

    void paintEvent(QPaintEvent *event) override;

private:

    RectangleManager rm;
    Shape shape;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
};
//! [0]

#endif // RENDERAREA_H
