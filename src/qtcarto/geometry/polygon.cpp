/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "polygon.h"
#include "qtcarto.h"

#include <algorithm>
#include <exception>

#include <QVector>

#include "segment.h"
#include "line.h"

/**************************************************************************************************/

QcPolygon::QcPolygon()
  : QcPath()
{
}

/*
QcPolygon::QcPolygon(int number_of_vertexes)
  : m_vertexes(number_of_vertexes), m_edges(0)
{
  if (number_of_vertexes > 1)
    m_edges.reserve(number_of_vertexes -1);
}
*/

QcPolygon::QcPolygon(const VertexListType & vertexes)
  : QcPath(vertexes, true)
{}

QcPolygon::QcPolygon(const QVector<Type> & coordinates)
  : QcPath(coordinates, true)
{}

QcPolygon::QcPolygon(const QcPolygon & polygon)
  : QcPolygon(polygon.vertexes())
{}

QcPolygon::~QcPolygon()
{}

/*
  @return next valid index (current + 1 or start index)
  for an array with n entries
  @param n entries count
  @param current current index
*/
inline int
get_next_index(int number_of_items, int current)
{
  return current == number_of_items - 1 ? 0 : current + 1;
}

// Test if the point is inside the polygon.
// Algorithm:
//   http://arxiv.org/abs/1207.3502
//   A correct even-odd algorithm for the point-in-polygon problem for complex polygons
//   Michael Galetzka, Patrick O. Glauner
bool
QcPolygon::contains(const VertexType & test_point) const
{
  // Fixme: check code for API
  int _number_of_vertexes = number_of_vertexes();

  // Initial start point
  const VertexType origin(0, 0);
  VertexType start_point;
  VertexType end_point;

  // Create axes
  EdgeType x_axis(origin, origin);
  EdgeType x_axis_positive(origin, origin);

  int start_node_position = -1;

  // Is test_point on a node?
  // Move polygon to 0|0
  // Enlarge axes
  VertexListType vertexes;
  for (int i = 0; i < _number_of_vertexes; i++) {
    const VertexType & vertex = vertex_at(i); // [i]
    if (test_point == vertex)
      return true;

    // Translate polygon to 0|0
    VertexType translated_vertex = vertex - test_point;
    vertexes.push_back(translated_vertex);

    // Find start point which is not on the x axis
    if (translated_vertex.y() != 0) {
      start_point = translated_vertex;
      start_node_position = i;
    }

    // Enlarge axes
    Type x = translated_vertex.x();
    if (x > x_axis.p2().x()) {
      x_axis.p2().set_x(x);
      x_axis_positive.p2().set_x(x);
    }
    if (x < x_axis.p1().x()) {
      x_axis.p1().set_x(x);
    }
  }

  // Move test_point to 0|0
  EdgeType test_point_line(origin, origin);
  EdgeType edge;

  // Is test_point on an edge?
  for (int i = 0; i < _number_of_vertexes; i++) {
    edge.set_p1(vertexes[i]);
    // Get correct index of successor edge
    edge.set_p2(vertexes[get_next_index(_number_of_vertexes, i)]);
    if (test_point_line.intersect(edge) == 1) {
	return true;
    }
  }

  // No start point found and point is not on an edge or node
  // --> point is outside
  if (start_node_position == -1) {
    return false;
  }

  unsigned int count = 0;
  int seen_points = 0;
  int i = start_node_position;

  // Consider all edges
  while (seen_points < _number_of_vertexes) {

    int saved_index = get_next_index(_number_of_vertexes, i);
    int saved_x = vertexes[saved_index].x();

    // Move to next point which is not on the x-axis
    do {
      i = get_next_index(_number_of_vertexes, i);
      seen_points++;
    } while (vertexes[i].y() == 0);
    // Found end point
    end_point = vertexes[i];

    // Only intersect lines that cross the x-axis
    if (start_point.y() * end_point.y() < 0) {
      edge.set_p1(start_point);
      edge.set_p2(end_point);

      // No nodes have been skipped
      // and the successor node has been chosen as the end point
      if (i == saved_index) {
	count += edge.intersect(x_axis_positive);
      }
      // If at least one node on the right side has been skipped,
      // the original edge would have been intersected
      // --> intersect with full x-axis
      else if (saved_x > 0) {
	count += edge.intersect(x_axis);
      }
    }

    // End point is the next start point
    start_point = end_point;
  }

  // Odd count --> in the polygon (1)
  // Even count --> outside (0)
  return bool(count % 2);
}

inline int
to_grid(double x, double grid_step)
{
  return int(x / grid_step);
}

class OpenInterval
{
public:
  OpenInterval(double x, int direction)
    : x(x), direction(direction)
  {}

  OpenInterval(const OpenInterval & other)
    : x(other.x), direction(other.direction)
  {}

  OpenInterval & operator=(const OpenInterval & other)
  {
    if (this != &other) {
      x = other.x;
      direction = other.direction;
    }

    return *this;
  }

  bool is_gap(const OpenInterval & other) const {
    return other.direction < 0 && direction > 0 && (x - other.x) >= 2;
  }

  friend bool operator<(const OpenInterval & open_interval1, const OpenInterval & open_interval2) {
    return open_interval1.x < open_interval2.x;
  }

  double x;
  double direction;
};

QcTiledPolygon
QcPolygon::intersec_with_grid(double grid_step) const {
  return QcTiledPolygon(*this, grid_step);
}

QcPolygon
QcPolygon::rotate_counter_clockwise(double angle) const
{
  VertexListType _vertexes(vertexes());
  for (VertexType & vertex: _vertexes)
    vertex.rotate_counter_clockwise(angle);

  return QcPolygon(_vertexes);
}

QcPolygon::Type
QcPolygon::area() const
{
  /* (signed) Area of a planar non-self-intersecting polygon
   *
   * 1/2 Sum(determinant egde)
   *
   * Note that the area of a convex polygon is defined to be positive
   * if the points are arranged in a counterclockwise order,
   * and negative if they are in clockwise order.
   *
   * Reference: Beyer, W. H. (Ed.). CRC Standard Mathematical Tables, 28th ed. Boca Raton, FL: CRC Press, pp. 123-124, 1987.
   */

  if (is_self_intersecting())
    return .0;

  Type _area = .0;
  EdgeListType _edges = edges();
  for (const auto & edge : _edges)
    _area += edge.determinant();

  return abs(_area) * .5;
}

/**************************************************************************************************/

QcTiledPolygonRun::QcTiledPolygonRun(int y, const QcIntervalInt & interval)
  : m_y(y), m_interval(interval)
{
}

bool
QcTiledPolygonRun::operator==(const QcTiledPolygonRun & other) const
{
  return (m_y == other.m_y) && (m_interval == other.m_interval);
}

bool
QcTiledPolygonRun::cut(const QcTiledPolygonRun & other,
		       QcIntervalInt & intersection, QcIntervalInt & left,  QcIntervalInt & right,
		       bool & exchanged) const
{
  if (m_y == other.m_y) {
    intersection = m_interval.cut(other.m_interval, left, right, exchanged);
    return true;
  }
  else
    return false;
}

QVector<QcTileMatrixIndex>
QcTiledPolygonRun::tile_indexes() const
{
  QVector<QcTileMatrixIndex> _tile_indexes(m_interval.length());
  int i;
  int x;
  for (i = 0, x = m_interval.inf(); x <= m_interval.sup(); x++, i++)
    _tile_indexes[i] = QcTileMatrixIndex(x, m_y);
  return _tile_indexes;
}

/**************************************************************************************************/

QcTiledPolygon::QcTiledPolygon(const QcPolygon & polygon, double grid_step)
  : m_polygon(polygon), m_grid_step(grid_step)
{
  const QcPolygon::IntervalType & polygon_interval = polygon.interval();
  const QcPolygon::VertexListType & vertexes = polygon.vertexes();

  QcInterval2DInt interval_on_grid(to_grid(polygon_interval.x().inf(), grid_step),
				   to_grid(polygon_interval.x().sup(), grid_step),
				   to_grid(polygon_interval.y().inf(), grid_step),
				   to_grid(polygon_interval.y().sup(), grid_step));

  int Y_min = interval_on_grid.y().inf();
  int number_of_rows = interval_on_grid.y().length();
  QVector<QList<OpenInterval>> rows(number_of_rows);

  int number_of_vertexes = vertexes.size();
  for (int i = 0; i < number_of_vertexes; i++) {
    const QcPolygon::VertexType & p0 = vertexes[i];
    int ii = i + 1;
    if (ii == number_of_vertexes)
      ii = 0;
    const QcPolygon::VertexType & p1 = vertexes[ii];

    double X0 = to_grid(p0.x(), grid_step);
    double Y0 = to_grid(p0.y(), grid_step);
    double X1 = to_grid(p1.x(), grid_step);
    double Y1 = to_grid(p1.y(), grid_step);

    // qinfo() << "P0 - P1" << i << X0 << Y0 << X1 << Y1;
    QcLineDouble line = QcLineDouble::from_two_points(p0, p1);

    if (Y1 > Y0) {
      rows[Y0 - Y_min].push_back(OpenInterval(X0, 1));
      for (int Y = Y0 +1; Y < Y1 +1; Y++) {
	double y = Y * grid_step;
	double x = line.get_x_from_y(y);
	int X = to_grid(x, grid_step);
	int YY = Y - Y_min;
	if (X1 < X0)
	  YY -= 1;
	OpenInterval open_interval(X, 1);
	rows[YY].push_back(open_interval);
      }
      rows[Y1 - Y_min].push_back(OpenInterval(X1, 1));
    }
    else if (Y1 < Y0) {
      rows[Y1 - Y_min].push_back(OpenInterval(X1, -1));
      for (int Y = Y1 +1; Y < Y0 +1; Y++) {
	double y = Y * grid_step;
	double x = line.get_x_from_y(y);
	double X = to_grid(x, grid_step);
	int YY = Y - Y_min;
	if (X1 < X0)
	  YY -= 1;
	OpenInterval open_interval(X, -1);
	rows[YY].push_back(open_interval);
      }
      rows[Y0 - Y_min].push_back(OpenInterval(X0, -1));
    }
  }
  // qinfo() << "OpenInterval built";

  for (int i = 0; i < number_of_rows; i++) {
    QList<OpenInterval> & row = rows[i];
    if (!row.size()) // Fixme: check
      continue;
    std::sort(row.begin(), row.end());
    int Y = Y_min + i;
    OpenInterval previous_interval = row[0];
    double x_inf = previous_interval.x;
    QList<QcIntervalInt> intervals;
    intervals.push_back(QcIntervalInt(x_inf, x_inf));
    int number_of_intervals = row.size();
    if (number_of_intervals > 1)
      for (int j = 1; j < number_of_intervals; j++) {
 	const OpenInterval & open_interval = row[j];
	// qinfo() << "i,j: " << i << j << open_interval.x << open_interval.direction;
	if (open_interval.is_gap(previous_interval)) {
	  double x_inf = open_interval.x;
	  intervals.push_back(QcIntervalInt(x_inf, x_inf));
	}
	else {
	  intervals.last().set_sup(open_interval.x);
	  previous_interval = open_interval;
	}
      }
    for (const QcIntervalInt & interval : intervals)
      m_runs.push_back(QcTiledPolygonRun(Y, interval));
  }
}

QcTiledPolygonDiff
QcTiledPolygon::diff(const QcTiledPolygon & old_tiled_polygon)
{
  QcTiledPolygonDiff tiled_polygon_diff;
  QcTiledPolygonRunList old_runs = old_tiled_polygon.m_runs;

  bool exchanged;
  QcIntervalInt intersection;
  QcIntervalInt left;
  QcIntervalInt right;
  QVector<unsigned int> intersection_count(old_runs.size(), 0);

  for (const QcTiledPolygonRun & new_run : m_runs) {
    bool has_intersection = false;
    int i = 0;
    for (const QcTiledPolygonRun & old_run : old_runs) {
      if (new_run.cut(old_run, intersection, left, right, exchanged)) {
	int y = new_run.y();
	qQCInfo() << y << intersection << left << right << exchanged;
	has_intersection = true;
	intersection_count[i] += 1;

	tiled_polygon_diff.add_same_area(QcTiledPolygonRun(y, intersection));

	if (left.is_not_empty()) {
	  QcTiledPolygonRun run(y, left);
	  if (exchanged)
	    tiled_polygon_diff.add_old_area(run);
	  else
	    tiled_polygon_diff.add_new_area(run);
	}

	if (right.is_not_empty()) {
	  QcTiledPolygonRun run(y, right);
	  if (exchanged)
	    tiled_polygon_diff.add_new_area(run);
	  else
	    tiled_polygon_diff.add_old_area(run);
	}
      }
      i++;
    }

    if (!has_intersection)
      tiled_polygon_diff.add_new_area(new_run);
  }

  for (int i = 0; i < old_runs.size(); i++) {
    if (!intersection_count[i])
      tiled_polygon_diff.add_old_area(old_runs[i]);
  }

  return tiled_polygon_diff;
}
