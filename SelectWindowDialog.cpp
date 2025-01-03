//Created by Eternity_boundary on Jan 3,2025
#include "SelectWindowDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

SelectWindowDialog::SelectWindowDialog(QWidget* parent)
	: QDialog(parent), m_selectedHwnd(nullptr) {
	comboBox = new QComboBox(this);
	okButton = new QPushButton("确定", this);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(new QLabel("请选择目标窗口：", this));
	layout->addWidget(comboBox);
	layout->addWidget(okButton);

	setLayout(layout);
	setWindowTitle("选择目标窗口");

	// 枚举顶层窗口，填充下拉框
	enumerateWindows();

	// 连接确定按钮
	connect(okButton, &QPushButton::clicked, this, &SelectWindowDialog::onOkClicked);
}

SelectWindowDialog::~SelectWindowDialog() {
}

void SelectWindowDialog::onOkClicked() {
	int idx = comboBox->currentIndex();
	if (idx >= 0 && idx < m_windowList.size()) {
		m_selectedHwnd = m_windowList[idx].hWnd;
	}
	accept();
}

// 静态回调函数
BOOL CALLBACK SelectWindowDialog::EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	if (!IsWindowVisible(hwnd)) {
		return TRUE; // 继续枚举
	}

	// 获取窗口标题
	wchar_t windowTitle[256];
	GetWindowText(hwnd, windowTitle, sizeof(windowTitle) / sizeof(wchar_t));
	QString qWindowTitle = QString::fromWCharArray(windowTitle).trimmed();
	if (qWindowTitle.isEmpty()) {
		return TRUE;
	}

	// 获取窗口类名
	wchar_t className[256];
	GetClassName(hwnd, className, sizeof(className) / sizeof(wchar_t));
	QString qClassName = QString::fromWCharArray(className).trimmed();

	// 将信息保存到对话框实例的 m_windowList 中
	SelectWindowDialog* dialog = reinterpret_cast<SelectWindowDialog*>(lParam);
	WindowInfo info;
	info.hWnd = hwnd;
	info.title = qWindowTitle;
	info.className = qClassName;
	dialog->m_windowList.append(info);

	return TRUE; // 继续枚举
}

void SelectWindowDialog::enumerateWindows() {
	m_windowList.clear();
	EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));

	for (int i = 0; i < m_windowList.size(); ++i) {
		const WindowInfo& win = m_windowList[i];
		comboBox->addItem(QString("%1 [%2]").arg(win.title).arg(win.className));
	}
}