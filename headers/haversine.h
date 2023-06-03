#ifndef LEIC_TSP_HAVERSINE_H
#define LEIC_TSP_HAVERSINE_H

#include <cmath>
#include <realvertexedge.h>

using namespace std;

/** Calculates the distance between two nodes using Haversine's Formula
* @param source the source node
* @param target the target node
* @return the double value that corresponds to the distance between two nodes
*/
double haversine(RealVertex* source, RealVertex* target);

/** Calculates the distance between two points on Earth using Haversine's Formula
* @param lat1 the first point's latitude
* @param long1 the first point's longitude
* @param lat2 the second point's latitude
* @param lat2 the second point's longitude
* @return the double value that corresponds to the distance between two points
*/
double haversine(double lat1, double long1, double lat2, double long2);

#endif //LEIC_TSP_HAVERSINE_H
