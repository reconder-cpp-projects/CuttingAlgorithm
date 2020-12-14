
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
class QLineEdit;
class QAbstractButton;
QT_END_NAMESPACE
class RenderArea;

//! [0]
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private slots:
    void shapeChanged();
    void penChanged();
    void brushChanged();
    void initializeSheet();
    void addRectangle();
public slots:
    void throwDialog(int num);

private:
    RenderArea *renderArea;


    QLabel *sheetWidthLabel;
    QLineEdit *sheetWidthInput;
    QLabel *sheetHeightLabel;
    QLineEdit *sheetHeightInput;
    QLabel *rectangleWidthLabel;
    QLineEdit *rectangleWidthInput;
    QLabel *rectangleHeightLabel;
    QLineEdit *rectangleHeightInput;
    QAbstractButton *initializeSheetButton;
    QAbstractButton *addRectangleButton;

};
//! [0]

#endif // WINDOW_H
