//Created by Eternity_boundary on Jan 3,2025
#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <windows.h>

#define _CELESTIAN_DISABLED_WARNINGS C26813 C26495
constexpr auto PRACTICETIME = 68000;

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
