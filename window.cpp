#include "renderarea.h"
#include "window.h"

#include <QtWidgets>
#include <QTextStream>

Window::Window()
{
    renderArea = new RenderArea;

    sheetWidthInput = new QLineEdit;
    sheetWidthLabel = new QLabel(tr("&Sheet width(cm):"));
    sheetWidthLabel->setBuddy(sheetWidthInput);

    sheetHeightInput = new QLineEdit;
    sheetHeightLabel = new QLabel(tr("&Sheet height(cm):"));
    sheetHeightLabel->setBuddy(sheetHeightInput);

    rectangleWidthInput = new QLineEdit;
    rectangleWidthLabel = new QLabel(tr("&Rectangle width(cm):"));
    rectangleWidthLabel->setBuddy(rectangleWidthInput);

    rectangleHeightInput = new QLineEdit;
    rectangleHeightLabel = new QLabel(tr("&Rectangle height(cm):"));
    rectangleHeightLabel->setBuddy(rectangleHeightInput);

    initializeSheetButton = new QPushButton("&Initialize Sheet", this);
    //initializeSheetButton->clicked(&Window::initializeSheet);

    addRectangleButton = new QPushButton("&Add Rectangle", this);
    //addRectangleButton->clicked(&Window::addRectangle);


    connect(initializeSheetButton, SIGNAL(clicked()), this, SLOT(initializeSheet()));
    connect(addRectangleButton, SIGNAL(clicked()), this, SLOT(addRectangle()));
    QObject::connect(renderArea, SIGNAL(throwDialog(int)), this, SLOT(throwDialog(int)));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    mainLayout->addWidget(sheetWidthLabel, 2, 0, Qt::AlignRight);
    mainLayout->addWidget(sheetWidthInput, 2, 1);
    mainLayout->addWidget(sheetHeightLabel, 3, 0, Qt::AlignRight);
    mainLayout->addWidget(sheetHeightInput, 3, 1);
    mainLayout->addWidget(initializeSheetButton, 4, 1);
    mainLayout->addWidget(rectangleWidthLabel, 2, 2, Qt::AlignRight);
    mainLayout->addWidget(rectangleWidthInput, 2, 3);
    mainLayout->addWidget(rectangleHeightLabel, 3, 2, Qt::AlignRight);
    mainLayout->addWidget(rectangleHeightInput, 3, 3);
    mainLayout->addWidget(addRectangleButton, 4, 3);
    setLayout(mainLayout);

    shapeChanged();
    penChanged();
    brushChanged();

    setWindowTitle(tr("Cutting Algorithm"));
}




void Window::shapeChanged()
{
    RenderArea::Shape shape = RenderArea::Rect;
    renderArea->setShape(shape);
}


void Window::penChanged()
{
    int width = 1;
    Qt::PenStyle style = Qt::SolidLine;
    Qt::PenCapStyle cap = Qt::FlatCap;
    Qt::PenJoinStyle join = Qt::MiterJoin;
    renderArea->setPen(QPen(Qt::black, width, style, cap, join));
}


void Window::brushChanged()
{
    renderArea->setBrush(QBrush(Qt::white, Qt::SolidPattern));
}
void Window::initializeSheet()
{

    renderArea->initializeSheet(sheetWidthInput->text(), sheetHeightInput->text());
}

void Window::addRectangle()
{
    renderArea->addRectangle(rectangleWidthInput->text(), rectangleHeightInput->text());
}

void Window::throwDialog(int num)
{
    QMessageBox msgBox;
    msgBox.setText("You don't have enough space for another rectangle. You have got " + QString::number(num) +" rectangles.");
    msgBox.exec();
}
