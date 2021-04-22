#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <math.h>
using namespace std;

enum ModelType {CONTINUOUS, MODELD5HZ, MODELD25HZ, MODELD100HZ};

// --------------------------
// Set type of discrete model here
// --------------------------
const ModelType modelType = MODELD100HZ;
// --------------------------
// Set stop time here
// --------------------------



// --------------------------
// Set stop time here
// --------------------------
#define ENDOFTIME 25*2
// --------------------------
// Set stop time here
// --------------------------

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	// Create dir for logs
	if (!QDir("logs").exists()) {
		QDir().mkdir("logs");
	}

    // Set window size
	this->setMinimumSize(640, 480);

    // Add main layout with two plots
    mainlayout = new QGridLayout(this);
    inputPlot = new QCustomPlot(this);
    outputPlot = new QCustomPlot(this);
	mainlayout->addWidget(inputPlot, 0, 0);
	mainlayout->addWidget(outputPlot, 0, 1);
	inputPlot->addGraph();
	outputPlot->addGraph();
    outputPlot->addGraph();

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor().red());
    outputPlot->graph(1)->setPen(pen);

	startButton = new QPushButton("Start");
	connect(startButton, &QPushButton::clicked, this, [=](){
		startTime = 0;
		relativeTime = 0;
		inputPlot->graph(0)->data()->clear();
		outputPlot->graph(0)->data()->clear();
		timer->start();
	});
	mainlayout->addWidget(startButton, 1, 0);

	saveButton = new QPushButton("Save");
	connect(saveButton, &QPushButton::clicked, this, [=](){
		QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
		inputPlot->savePng(QString("./logs/%1_input.png").arg(timestamp));
		outputPlot->savePng(QString("./logs/%1_output.png").arg(timestamp));
	});
	mainlayout->addWidget(saveButton, 1, 1);

    // Give the axes some labels:
    inputPlot->xAxis->setLabel("t");
    inputPlot->yAxis->setLabel("input");
    outputPlot->xAxis->setLabel("t");
    outputPlot->yAxis->setLabel("output");

    // --------------------------
    // Change ranges if you need
    // --------------------------
    // Set axes ranges so see all data:
    inputPlot->xAxis->setRange(0, ENDOFTIME);
    inputPlot->yAxis->setRange(-3, 3);
    outputPlot->xAxis->setRange(0, ENDOFTIME);
    outputPlot->yAxis->setRange(-1, 0.8);

    // --------------------------
    // Create the object here
    // --------------------------
    _object = new gain(2.0);
    _int1 = new integrator(-1);
    _generator = new generator();
    _model = new model();

    // 5Hz discrete model
    float A5Hz[SIZE_X][SIZE_X] = {
        {0.998202651696995,0.193916933610120,0.017293453834547},
        {-0.025940180751820,0.911735382524261,0.159330025941027},
        {-0.238995038911540,-0.822590310456952,0.593075330642208}
    };
    float B5Hz[SIZE_X] = {0.001198232202004,0.017293453834547,0.159330025941027};
    float C5Hz[SIZE_X] = {0.500000000000000,0.0,0.0};
    float D5Hz = 0;
    _modelD5Hz = new modelD(A5Hz,B5Hz,C5Hz,D5Hz);

    // 25Hz discrete model
    float A25hz[SIZE_X][SIZE_X] = {
        {0.999984321191040,0.039947579871491,7.785688852478380e-04},
        {-0.001167853327872,0.996091476764801,0.038390442100995},
        {-0.057585663151493,-0.193120063832848,0.919310592562810}
    };
    float B25hz[SIZE_X] = {1.045253930676698e-05,7.785688852478380e-04,0.038390442100995};
    float C25hz[SIZE_X] = {0.500000000000000,0.0,0.0};
    float D25hz = 0;
    _modelD25Hz = new modelD(A25hz,B25hz,C25hz,D25hz);

    // 100Hz discrete model
    float A100hz[SIZE_X][SIZE_X] = {
        {0.999999751251228,0.009999170214929,4.966625873189509e-05},
        {-7.449938809784263e-05,0.999751419957569,0.009899837697465},
        {-0.014849756546198,-0.049573687875425,0.979951744562638}
    };
    float B100hz[SIZE_X] = {1.658325145259543e-07,4.966625873189509e-05,0.009899837697465};
    float C100hz[SIZE_X] = {0.500000000000000,0.0,0.0};
    float D100hz = 0;
    _modelD100Hz = new modelD(A100hz,B100hz,C100hz,D100hz);
    // --------------------------
    // Create the object here
    // --------------------------

    timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // --------------------------
    // Set sampling time here
    // --------------------------

    int SAMPLINGTIMEMSEC = 10;
    if (modelType==CONTINUOUS)
        SAMPLINGTIMEMSEC = 5;
    else if (modelType==MODELD5HZ)
        SAMPLINGTIMEMSEC = 200;
    else if (modelType==MODELD25HZ)
        SAMPLINGTIMEMSEC = 40;
    else if (modelType==MODELD100HZ)
        SAMPLINGTIMEMSEC = 10;
    else SAMPLINGTIMEMSEC = 10;


	timer->setInterval(SAMPLINGTIMEMSEC);
    // --------------------------
    // Set sampling time here
    // --------------------------
}

Widget::~Widget()
{
    delete ui;
    delete inputPlot;
    delete outputPlot;
    delete timer;
    delete mainlayout;

    // --------------------------
    // Delete the object here
    // --------------------------
    delete _object;
    delete _int1;
    delete _generator;
    delete _model;
    delete _modelD5Hz;
    delete _modelD25Hz;
    delete _modelD100Hz;
    // --------------------------
    // Delete the object here
    // --------------------------
}

void Widget::update() {

	// --------------------------
	// Replace input signal with ours
	// --------------------------
    double signal = _generator->update(dt/1000.0);
	// --------------------------
	// Replace input signal with ours
	// --------------------------

	// --------------------------
	// Plot initial values here
	// --------------------------
	if (startTime == 0) {
		// First step only plot initial values
		startTime = QDateTime::currentMSecsSinceEpoch();

		inputPlot->graph(0)->addData(0.0, 0);
		outputPlot->graph(0)->addData(0.0, 0);
		return;
	} else {
		dt = relativeTime;
		relativeTime = QDateTime::currentMSecsSinceEpoch() - startTime;
		dt = relativeTime - dt;
	}

	inputPlot->graph(0)->addData(relativeTime / 1000.0, signal);
    outputPlot->graph(0)->addData(relativeTime / 1000.0, _model->update(signal, dt/1000.0));
    if (modelType==MODELD5HZ)
        outputPlot->graph(1)->addData(relativeTime / 1000.0, _modelD5Hz->getY());
    else if (modelType==MODELD25HZ)
        outputPlot->graph(1)->addData(relativeTime / 1000.0, _modelD25Hz->getY());
    else if (modelType==MODELD100HZ)
        outputPlot->graph(1)->addData(relativeTime / 1000.0, _modelD100Hz->getY());

    inputPlot->replot();
    outputPlot->replot();

    // --------------------------
    // Update the object here
    // --------------------------
    _modelD5Hz->update(signal);
    _modelD25Hz->update(signal);
    _modelD100Hz->update(signal);
    // --------------------------
    // Update the object here
    // --------------------------

	if (relativeTime / 1000.0 > ENDOFTIME) {
		timer->blockSignals(true);
		timer->stop();
		timer->blockSignals(false);
	}
}
