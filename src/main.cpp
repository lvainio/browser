#include <iostream>

#include "url.h"

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QWidget>

class RenderArea : public QWidget {
public:
    RenderArea(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);

        // White background
        painter.fillRect(rect(), Qt::white);

        // Draw some basic text — this is where your rendering engine will draw
        painter.setPen(Qt::black);
        painter.drawText(50, 50, "Hello, Browser!");

        // You can draw boxes, images, lines — whatever your engine generates
    }
};

class BrowserWindow : public QMainWindow {
public:
    BrowserWindow() {
        setWindowTitle("My Custom Browser");
        resize(800, 600);

        auto *renderArea = new RenderArea(this);
        setCentralWidget(renderArea);
    }
};

void show(std::string body) {
    bool in_tag = false;
    for (char ch : body) {
        if (ch == '<') {
            in_tag = true;
        } else if (ch == '>') {
            in_tag = false;
        } else if (!in_tag) {
            std::cout << ch;
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    std::size_t testvar = 5;

    std::cout << sizeof testvar << std::endl;

    std::cout << "A very nice web browser!" << std::endl;

    Url url("https://browser.engineering/examples/example1-simple.html");

    std::cout << url.toString() << std::endl;

    std::string body = url.request();

    std::cout << "------------\nPRINTING HTML BODY:\n------------ " << std::endl;

    show(body);

    QApplication app(argc, argv);

    BrowserWindow window;
    window.show();

    return app.exec();
}
