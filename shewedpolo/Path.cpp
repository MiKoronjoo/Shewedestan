#include <cstdint>
#include "Path.hpp"

Path::Path() : distance(INT64_MAX), to(-1) {}

Path::Path(double distance, int to) : distance(distance), to(to) {}
