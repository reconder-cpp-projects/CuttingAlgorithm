#include <iostream>
#include <vector>
#include <algorithm>
#include <QTextStream>
using namespace std;



QTextStream out(stdout);

struct Recta {
    pair<int, int> pos;
    int x;  //pixels
    int y;  //pixels
    Recta() { x = 0; y = 0; }
    Recta(int X, int Y) {
        if (X > Y)
        {
            y = X;
            x = Y;
            return;
        }
        x = X;
        y = Y;
    };
    bool operator<(Recta& other) {
        if (y == other.y) { return x > other.x; }
        return y > other.y;
    }

    void Place(Recta& sheet, vector<bool>& sheetLayout, int& leftx, int& topy, int& nextTopy)
    {



        if (topy + y > sheet.y)
        {
            throw("Sheet is too small.");
        }

        int lx = leftx;
        int ty = topy;

        if (ty > 0) {
            while (sheetLayout[lx + (ty - 1) * sheet.y] && ty > 0)
            {
                if (--ty == 0) { break; }
            }
        }
        if (ty < topy) {
            while (sheetLayout[lx - 1 + (ty + y) * sheet.y] && lx > 0)
            {
                lx--;
            }
        }
        if (lx + x > sheet.x)
        {
            lx = 0;
            ty = nextTopy;
            topy = nextTopy;
            nextTopy = topy + y;
        }

        pos = { lx, ty };
        Draw(sheet, sheetLayout, lx, ty);
        std::cout << topy << ", " << nextTopy << endl;

        leftx = lx + x;


    }
    void Draw(Recta& sheet, vector<bool>& sheetLayout, int ltx, int lty)
    {
        for (int i = lty; i < lty + y; i++)
        {
            for (int j = ltx; j < ltx + x; j++)
            {
                sheetLayout[j + i * sheet.y] = false;
            }
        }
    }
};


class RectangleManager {
private:
    Recta sheet;
    vector<bool> sheetLayout;
    vector<Recta> rectangles;
    void ResetLayout() {
        sheetLayout.assign(sheetLayout.size(), true);
    }
    void PackRectangles() {

        ResetLayout();

        sort(rectangles.begin(), rectangles.end());

        int leftx = 0;
        int topy = 0;
        rectangles[0].Draw(sheet, sheetLayout, leftx, topy);

        rectangles[0].pos = { leftx, topy };
        leftx = rectangles[0].x;
        int nextTopy = rectangles[0].y;

        for (int i = 1; i < rectangles.size(); i++)
        {

            rectangles[i].Place(sheet, sheetLayout, leftx, topy, nextTopy);
            cout << i << endl;

        }

    }
public:

    RectangleManager() {};

    void InitializeSheet(int x, int y)
    {

        sheet.x = x;
        sheet.y = y;
        sheetLayout.empty();
        sheetLayout.reserve(x * y);
        sheetLayout.resize(x * y);
    }

    void AddRectangle(int x, int y)
    {
        Recta r(x, y);
        rectangles.push_back(r);
        PackRectangles();
        for(auto& r : rectangles)
        {
            out << "pos.x: " << r.pos.first << ", pos.y: " << r.pos.second << ", x: " << r.x << ", y: " << r.y << endl;
        }
    }

    vector<Recta> GetLayout() {
        return rectangles;
    }



};









//int main()
//{

//    //Rect sheet = InitializeSheet();
//    //cout << "Enter the sizes of rectangles" << endl;
//    //bla bla bla
//    Rect sheet(10, 10);
//    Rect r1(2, 5);
//    Rect r2(4, 3);
//    Rect r3(2, 2);
//    Rect r4(4, 5);
//    Rect r5(4, 4);
//    Rect r6(2, 2);
//    Rect r7(2, 2);
//    Rect r8(1, 1);
//    vector<Rect> rectangles;
//    rectangles.push_back(r1);
//    rectangles.push_back(r2);
//    rectangles.push_back(r3);
//    rectangles.push_back(r4);
//    rectangles.push_back(r5);
//    rectangles.push_back(r6);
//    rectangles.push_back(r7);
//    rectangles.push_back(r8);
//    PackRectangles(sheet, rectangles);

//}
