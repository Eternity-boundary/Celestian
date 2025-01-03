//Created by Eternity_boundary on Jan 3,2025
#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <windows.h> // 用于 Windows API

#define _CELESTIAN_DISABLED_WARNINGS C26813 C26495

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

private slots:
	void simulateKeyPress();
	void onButtonClicked();

private:
	QPushButton* button;
	QTimer* timer;
};

HWND getWindowHandle();
