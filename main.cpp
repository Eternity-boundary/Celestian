//Created by Eternity_boundary on Jan 3,2025
#include "Celestian.h"
#include <QtWidgets/QApplication>
#define _CELESTIAN_VERSION "0.0.2"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setWindowTitle("Celestian--自动修炼器");
	mainWindow.resize(300, 150);
	mainWindow.show();

	return app.exec();
}