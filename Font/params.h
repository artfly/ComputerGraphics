#ifndef PARAMS_H
#define PARAMS_H

class Params {
public:
    Params(int x = 0, int y = 0,  int scale = 0,  bool fill = true, bool outline = true);
    int getX() const;
    int getY() const;
    int getScale() const;
    bool getFill() const;
    bool getOutline() const;
private:
    int x;
    int y;
    int scale;
    bool fill;
    bool outline;
};

#endif // PARAMS_H
