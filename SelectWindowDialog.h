//Created by Eternity_boundary on Jan 3,2025
#pragma once
#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QVector>
#include <Windows.h>

struct WindowInfo {
	HWND hWnd;
	QString title;
	QString className;
};

class SelectWindowDialog : public QDialog {
	Q_OBJECT
public:
	explicit SelectWindowDialog(QWidget* parent = nullptr);
	~SelectWindowDialog();

	HWND selectedHwnd() const { return m_selectedHwnd; }

private slots:
	void onOkClicked();

private:
	void enumerateWindows(); // 枚举所有顶层窗口，填充到下拉框
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

	QComboBox* comboBox;
	QPushButton* okButton;

	QVector<WindowInfo> m_windowList;
	HWND m_selectedHwnd;
};