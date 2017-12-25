#include "QtGraphicDraw.h"

QLineF DrawLine(double x1, double y1, double x2, double y2)
{
	return QLineF(x1*WIDTH_FACTOR, y1*HEIGHT_FACTOR, x2*WIDTH_FACTOR, y2*HEIGHT_FACTOR);
}

QRect DrawRectangle(double x, double y, double width, double height)
{
	return (QRect(x*WIDTH_FACTOR - width*(-WIDTH_FACTOR) / 2, y*HEIGHT_FACTOR - height*HEIGHT_FACTOR / 2, width*(-WIDTH_FACTOR), height*HEIGHT_FACTOR));
}

QRect DrawRectangle(Obstacle obs)
{
	return DrawRectangle(obs.stCenterPoint.x, obs.stCenterPoint.y + GRIDLINE_HEIGHT, obs.fExpWidth, obs.fExpHeight);
}

QPainterPath DrawPath(vector<PointXY> path)
{
	PointXY tmpPoint;
	QPainterPath qtPath;
	if (path.size() > 0)
	{
		tmpPoint = path[0];
		qtPath.moveTo(tmpPoint.x*WIDTH_FACTOR, (tmpPoint.y + GRIDLINE_HEIGHT)*HEIGHT_FACTOR);
		for (size_t i = 0; i < path.size(); i++)
		{
			qtPath.lineTo(path[i].x*WIDTH_FACTOR, (path[i].y + GRIDLINE_HEIGHT)*HEIGHT_FACTOR);
		}
	}
	return qtPath;
}

QPainterPath DrawGlobalPath(vector<PointXY> path)
{
	PointXY tmpPoint;
	QPainterPath returnPath;
	if (path.size() > 0)
	{
		tmpPoint = path[0];
		returnPath.moveTo(tmpPoint.x, tmpPoint.y);
		for (size_t i = 0; i < path.size(); i++)
		{
			returnPath.lineTo(path[i].x, path[i].y);
		}
	}
	return returnPath;
}
