#pragma once


class City {
private:
    double x, y, max_dis;
public:
    double getMaxDis() const;

    void setMaxDis(double maxDis);

private:
    int state;
    bool is_capital;

public:
    double getX() const;

    double getY() const;

    int getState() const;

    bool isCapital() const;

    void setIsCapital(bool isCapital);

public:
    City(double x, double y, int state);

    double distance(City *that);

    double distance(double x0, double y0) const;
};
