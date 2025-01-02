//Created by Eternity_boundary on Jan 3,2025
#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <windows.h> // 用于 Windows API

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

// 声明辅助函数
HWND getWindowHandle();