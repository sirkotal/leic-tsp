#include "haversine.h"

double haversine(RealVertex* source, RealVertex* target) {
    return haversine(source->getLatitude(), source->getLongitude(), target->getLatitude(), target->getLongitude());
}

double haversine(double lat1, double long1, double lat2, double long2) {
    double dstLat = (lat2 - lat1) * M_PI / 180.0;
    double dstLong = (long2 - long1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double alpha = pow(sin(dstLat / 2), 2) + pow(sin(dstLong / 2), 2) * cos(lat1) * cos(lat2); // a
    double radius_earth = 6371;
    double omega = 2 * asin(sqrt(alpha)); // c

    return radius_earth * omega;
}