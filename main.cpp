//Created by Eternity_boundary on Jan 3,2025
#include "Celestian.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setWindowTitle("自动修炼器");
	mainWindow.resize(300, 150);
	mainWindow.show();

	return app.exec();
}