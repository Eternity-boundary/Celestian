//Created by Eternity_boundary on Jan 3,2025
#include "Celestian.h"
#include "SelectWindowDialog.h"
#include <Windows.h>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <TlHelp32.h>

// 全局变量（或改为 MainWindow 的成员变量）
HWND targetWindow = nullptr;

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
		// 如果定时器正在运行，停止并重置按钮文字
		timer->stop();
		button->setText("启动修炼");
		qDebug() << "定时器已停止";
	}
	else {
		// 弹出窗口选择对话框
		SelectWindowDialog dlg(this);
		if (dlg.exec() == QDialog::Accepted) {
			// 用户点击“确定”，获取选中的窗口句柄
			targetWindow = dlg.selectedHwnd();
			if (targetWindow == nullptr) {
				qDebug() << "未选择任何有效窗口，操作中断。";
				return;
			}

			// 启动定时器
			timer->start(68000); // 每 68 秒触发一次，这里需要略大于修炼时间一些，确保不会出现bug
			button->setText("停止修炼");
			qDebug() << "定时器已启动";

			// 立即执行一次
			simulateKeyPress();
		}
		else {
			// 用户点了取消或关闭对话框，则不执行后续操作
			qDebug() << "用户取消选择窗口，操作中断。";
		}
	}
}

void MainWindow::simulateKeyPress() {
	if (!targetWindow) {
		qDebug() << "未设置目标窗口句柄，无法模拟按键。";
		return;
	}

	// 将目标窗口设置为前台窗口
	SetForegroundWindow(targetWindow);
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