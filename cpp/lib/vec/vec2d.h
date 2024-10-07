struct Vec2d
{
    double x{0.};
    double y{0.};

    Vec2d() = default;

    Vec2d(double _x, double _y) : x{_x}, y{_y} {}

    Vec2d& operator+= (const Vec2d& rhs);
    
    Vec2d& operator-= (const Vec2d& rhs);

    Vec2d& operator*= (const int& number);

    Vec2d& operator/= (const int& number);
};

Vec2d operator- (const Vec2d& lhs, const Vec2d& rhs);

Vec2d operator+ (const Vec2d& lhs, const Vec2d& rhs);

Vec2d operator* (const Vec2d& lhs, const double& rhs);

Vec2d operator* (const double& lhs, const Vec2d& rhs);

Vec2d operator/ (const Vec2d& lhs, const double& rhs);

Vec2d operator/ (const double& lhs, const Vec2d& rhs);

double length (const Vec2d& v);

double lengthsqr (const Vec2d& v);

bool operator== (const Vec2d& p, const Vec2d& q);

bool operator!= (const Vec2d& p, const Vec2d& q);