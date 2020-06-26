#pragma once


class City {
private:
    float x, y, max_dis;
public:
    float getMaxDis() const;

    void setMaxDis(float maxDis);

private:
    int state;
    bool is_capital;

public:
    float getX() const;

    float getY() const;

    int getState() const;

    bool isCapital() const;

    void setIsCapital(bool isCapital);

public:
    City(float x, float y, int state);

    float distance(City &that);

    float distance(float x0, float y0) const;
};
