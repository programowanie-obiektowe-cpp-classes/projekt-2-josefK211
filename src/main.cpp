#include <cmath>
#include <iostream>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Point3D
{
private:
    double x, y, z;

public:
    // konstruktor param z lista inicjalizacyjna
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    double getX() const { return x; }
    double getY() const { return y; } // gettery
    double getZ() const { return z; }

    void translate(double dx, double dy, double dz) // metoda translacyjna
    {
        x += dx;
        y += dy; // dodanie odpowiednich przesuniec do zmiennych
        z += dz;
    }

    void rotate(double angleX, double angleY, double angleZ)
    {
        double radX = angleX * M_PI / 180.0;
        double radY = angleY * M_PI / 180.0; // zamiana na radiany
        double radZ = angleZ * M_PI / 180.0;

        double y1 = y * cos(radX) - z * sin(radX); // obrot wokol ox
        double z1 = y * sin(radX) + z * cos(radX);
        y         = y1;
        z         = z1;

        double x2 = x * cos(radY) + z * sin(radY); // obrot wokol oy
        double z2 = -x * sin(radY) + z * cos(radY);
        x         = x2;
        z         = z2;

        double x3 = x * cos(radZ) - y * sin(radZ); // obrot wokol oz
        double y3 = x * sin(radZ) + y * cos(radZ);
        x         = x3;
        y         = y3;
    }

    // metoda rzutujaca na plaszczyzne
    void project(const std::string& plane) const // drukowanie rzutowanych wspolrzednych
    {
        if (plane == "xy")
        {
            std::cout << "rzutowanie na XY: (" << x << ", " << y << ")" << std::endl;
        }
        else if (plane == "xz")
        {
            std::cout << "rzutowanie na XZ: (" << x << ", " << z << ")" << std::endl;
        }
        else if (plane == "yz")
        {
            std::cout << "rzutowanie na YZ: (" << y << ", " << z << ")" << std::endl;
        }
        else
        {
            throw std::invalid_argument("Niepoprawna plaszczyzna. Uzyj 'xy', 'xz', albo 'yz'.");
        }
    }

    void print() const { std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl; }
};

int main()
{
    Point3D p1(1.0, 2.0, 3.0);
    p1.print();                   // wspolrzedne poczatkowe
    p1.translate(3.0, 1.0, -2.0); // przesuniecie o zadane wspolrzedne
    p1.print();                   // po przesunieciu
    p1.rotate(0, 90, 0);          // obrot o 90 stopni wokol OY
    p1.print();
    p1.project("xy"); // rzutowanie na plaszczyzne XY
    p1.project("xz"); 
    p1.project("yz"); 

    return 0;
}
