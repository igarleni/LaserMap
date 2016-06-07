#include "OpenGL3D.h"


OpenGL3D::OpenGL3D(QWidget *parent, LaserPointList *laserPointListIn)
{
	laserPointList = laserPointListIn;
}

OpenGL3D::OpenGL3D(QWidget *parent)
{

}


OpenGL3D::~OpenGL3D()
{
	//se llama al cerrar la ventana lasermap y cuando se crea un nuevo 3Dmap
}

/////////////////////////////////////////////////////
//////////////////OpenGL FUNCTIONS///////////////////
/////////////////////////////////////////////////////

void OpenGL3D::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGL3D::resizeGL(int w, int h)
{
	//GLdouble ratioWidget = (GLdouble)w / (GLdouble)h;
	//updateGlOrtho(ratioWidget);
	glViewport(0, 0, w, h);
}

void OpenGL3D::paintGL()
{
	updateGlOrtho(width() / (GLdouble)height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	QList<LaserPoint> *pointList = laserPointList->getList();
	for (int i = 0; i < pointList->size(); i++)
	{
		LaserPoint p = pointList->at(i);
		//setColor(p.GetClassification());
		GLfloat normalizeZ = (p.getZ() - laserPointList->zMin) / (laserPointList->zMax - laserPointList->zMin);
		glColor3f(normalizeZ, normalizeZ, normalizeZ);
		glVertex3d(p.getX(), p.getY(), -(p.getZ()));

	}
	glEnd();
}

void OpenGL3D::updateGlOrtho(GLdouble ratioWidget)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (laserPointList->getRatioMap() > ratioWidget)
	{
		glOrtho(laserPointList->xMin, laserPointList->xMax,
			laserPointList->yMin - (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap()))) / 2.0, laserPointList->yMax + (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap()))) / 2.0,
			laserPointList->zMin, laserPointList->zMax);

	}
	else
	{
		glOrtho(laserPointList->xMin - (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap())) / 2.0, laserPointList->xMax + (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap())) / 2.0,
			laserPointList->yMin, laserPointList->yMax,
			laserPointList->zMin, laserPointList->zMax);
	}
	glMatrixMode(GL_MODELVIEW);
}

/////////////////////////////////////////////////////
/////////////////////MOUSE EVENTS////////////////////
/////////////////////////////////////////////////////

void OpenGL3D::mousePressEvent(QMouseEvent *event)
{

}

void OpenGL3D::mouseMoveEvent(QMouseEvent *event)
{

}

void OpenGL3D::mouseReleaseEvent(QMouseEvent *event)
{

}

void OpenGL3D::closeEvent(QCloseEvent *event)
{
	qDebug() << "cerrando ventana 3D";
}
