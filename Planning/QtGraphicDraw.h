#pragma once

#include <QMainWindow>
#include <QQuaternion>
#include <QtWidgets>
#include <QWheelEvent>
#include <QMouseEvent>

#include "VehPlanning.h"

#define WIDTH_FACTOR -10
#define HEIGHT_FACTOR 4
#define GRIDLINE_WIDTH 10
#define GRIDLINE_HEIGHT 30
#define CENTER_X 205
#define CENTER_Y 100

QLineF DrawLine(double x1, double y1, double x2, double y2);
QRect DrawRectangle(Obstacle);
QRect DrawRectangle(double x, double y, double width, double height);
QPainterPath DrawPath(vector<PointXY>);
QPainterPath DrawGlobalPath(vector<PointXY>);