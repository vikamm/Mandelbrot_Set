#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

double coordx_now = 600, coordy_now = 600;
double x1 = -2, x2 = 2;
double y1_ = -2, y2_ = 2;


int count_ = 0;

int now_it = 0;

vector <pair<pair<double, double>, pair<double, double>>> pred;

class Complex_number {
public:
    Complex_number(double a_in_, double b_in_) {
        a_ = a_in_;
        b_ = b_in_;
    }

    bool modul() {
        if (a_ * a_ + b_ * b_ > 4) {
            return 1;
        }
        return 0;
    }

    Complex_number operator + (Complex_number other) {
        Complex_number prom(0, 0);
        prom.a_ = a_ + other.a_;
        prom.b_ = b_ + other.b_;
        return prom;
    }

    Complex_number operator * (Complex_number other) {
        Complex_number prom(0, 0);
        prom.a_ = a_ * other.a_ - b_ * other.b_;
        prom.b_ = a_ * other.b_ + b_ * other.a_;
        return prom;
    }

private:
    double a_, b_;
};


void solution(sf::RenderWindow& window) {
    for (double x = 0; x < 600; x += 1) {
        for (double y = 0; y < 600; y += 1) {
            Complex_number zn(0, 0);
            int i = 0;
            while (i < 500 && !zn.modul()) {
                Complex_number pl_number(x / 600 * (x2 - x1) + x1, y / 600 * (y2_ - y1_) + y1_);
                zn = zn * zn;
                zn = zn + pl_number;
                ++i;
            }
            if (zn.modul()) {
                sf::RectangleShape pix(sf::Vector2f(1, 1));
                pix.setFillColor(sf::Color((7 * i) % 256, (0 * i) % 256, (15 * i) % 256));
                pix.setPosition(x, y);
                window.draw(pix);
            }
        }
    }
}

void output() {
    sf::Font font;
    string now;
    if (!font.loadFromFile("D:/праки/практикум. многочлены/Times New Roman/timesnewromanpsmt.ttf")) {
        std::cout << "error";
    }
    sf::RenderWindow window(sf::VideoMode(600, 600), "mandelbrot_set");
    /*sf::RectangleShape now_wind(sf::Vector2f(0, 0));
    now_wind.setFillColor(sf::Color(0, 0, 0, 0));
    now_wind.setOutlineThickness(1.f);
    now_wind.setOutlineColor(sf::Color(250, 250, 250));
    now_wind.move(0, 0);*/
    window.clear();
    solution(window);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (now_it - 1 >= 0) {
                    x1 = pred[now_it].first.first;
                    y1_ = pred[now_it].first.second;
                    x2 = pred[now_it].second.first;
                    y2_ = pred[now_it].second.second;
                    pred.pop_back();

                    now_it--;

                    window.clear();
                    solution(window);
                    window.display();
                    sf::sleep(sf::milliseconds(150));
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                double x_ = position.x, y_ = position.y;
                count_++;
                if (count_ < 2) {
                    coordx_now = x_;
                    coordy_now = y_;
                }
                else {
                    ++now_it;
                    double xmin = min(double(x_), coordx_now), ymin = min(double(y_), coordy_now);
                    double xmax = max(double(x_), coordx_now), ymax = max(double(y_), coordy_now);
                    /**pred.push_back(make_pair(make_pair(coordx_now_pred, coordy_now_pred), make_pair(coordx_now1, coordy_now2)));
                    predx.push_back(make_pair(make_pair(x1, y1_), make_pair(x2, y2_)));
                    coordx_now1_pred = coordx_now1;
                    coordy_now2_pred = coordy_now2;*/
                    pred.push_back(make_pair(make_pair(x1, y1_), make_pair(x2, y2_)));
                    xmin = (xmin / 600) * (x2 - x1) + x1;
                    xmax = (xmax / 600) * (x2 - x1) + x1;
                    ymin = (ymin / 600) * (y2_ - y1_) + y1_;
                    ymax = (ymax / 600) * (y2_ - y1_) + y1_;
                    x1 = xmin;
                    x2 = xmax;
                    y1_ = ymin;
                    y2_ = ymax;
                    window.clear();
                    solution(window);
                    window.display();
                    count_ = 0;
                }
                sf::sleep(sf::milliseconds(150));
            }
        }
    }
}

int main() {
    pred.push_back(make_pair(make_pair(-2, -2), make_pair(2, 2)));
    output();
}