//Created by Eternity_boundary on Jan 3,2025
#include "Celestian.h"
#include <Windows.h>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <TlHelp32.h>
#pragma warning(disable:_STL_DISABLED_WARNINGS)
#pragma warning(disable:_CELESTIAN_DISABLED_WARNINGS)

HWND targetWindow = nullptr; // 全局变量保存窗口句柄

// 枚举顶层窗口的回调函数
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	wchar_t className[256];
	wchar_t windowTitle[256];

	// 获取窗口类名
	GetClassName(hwnd, className, sizeof(className) / sizeof(wchar_t));

	// 获取窗口标题
	GetWindowText(hwnd, windowTitle, sizeof(windowTitle) / sizeof(wchar_t));

	// 匹配类名和窗口标题
	if (wcscmp(className, L"Chrome_WidgetWin_1") == 0 && wcscmp(windowTitle, L"QQ") == 0) {
		targetWindow = hwnd; // 保存找到的窗口句柄
		return FALSE;        // 停止枚举
	}
	return TRUE; // 继续枚举
}

// 获取窗口句柄函数
HWND getWindowHandle() {
	targetWindow = nullptr;
	EnumWindows(EnumWindowsProc, 0);
	if (!targetWindow) {
		qDebug() << "未找到匹配的窗口";
	}
	return targetWindow;
}

// 主窗口实现
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	// 创建按钮
	button = new QPushButton("启动修炼", this);
	button->setGeometry(50, 50, 200, 50);

	// 定时器
	timer = new QTimer(this);

	// 连接信号和槽
	connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
	connect(timer, &QTimer::timeout, this, &MainWindow::simulateKeyPress);
}

void MainWindow::onButtonClicked() {
	if (timer->isActive()) {
		timer->stop();
		button->setText("启动修炼");
		qDebug() << "定时器已停止";
	}
	else {
		timer->start(68000); // 每 68 秒触发一次
		button->setText("停止修炼");
		qDebug() << "定时器已启动";
	}
}

void MainWindow::simulateKeyPress() {
	// 获取目标窗口句柄
	HWND hwnd = getWindowHandle();
	if (!hwnd) {
		qDebug() << "未找到目标窗口";
		return;
	}

	// 将目标窗口设置为前台窗口
	SetForegroundWindow(hwnd);
	Sleep(200); // 等待窗口切换完成

	// 准备输入事件
	INPUT inputs[6] = {};

	// 输入“修”
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = 0; // 不使用虚拟键
	inputs[0].ki.wScan = L'修';
	inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;

	// 输入“炼”
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = 0;
	inputs[1].ki.wScan = L'炼';
	inputs[1].ki.dwFlags = KEYEVENTF_UNICODE;

	// 释放“修”
	inputs[2] = inputs[0];
	inputs[2].ki.dwFlags |= KEYEVENTF_KEYUP;

	// 释放“炼”
	inputs[3] = inputs[1];
	inputs[3].ki.dwFlags |= KEYEVENTF_KEYUP;

	// 模拟回车键
	inputs[4].type = INPUT_KEYBOARD;
	inputs[4].ki.wVk = VK_RETURN; // 虚拟键码：回车键
	inputs[4].ki.dwFlags = 0;     // 按下回车键

	// 释放回车键
	inputs[5].type = INPUT_KEYBOARD;
	inputs[5].ki.wVk = VK_RETURN; // 虚拟键码：回车键
	inputs[5].ki.dwFlags = KEYEVENTF_KEYUP; // 释放回车键

	// 发送输入事件
	UINT sent = SendInput(6, inputs, sizeof(INPUT));
	if (sent != 6) {
		qDebug() << "按键模拟失败，错误代码：" << GetLastError();
	}
	else {
		qDebug() << "成功模拟输入: 修炼 + 回车";
	}
}