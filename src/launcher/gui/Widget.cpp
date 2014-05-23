
#include "Widget.hpp"
#include "../WindowsError.hpp"

namespace gui {

	Widget::Widget() : hWnd(NULL) {}

	Widget::~Widget() {
		this->destroy();
	}

	void Widget::destroy() {
		if (hWnd) {
			::DestroyWindow(hWnd);
			this->hWnd = NULL;
		}
	}

	void Widget::setVisible(bool visible) {
		::ShowWindow(hWnd, SW_SHOWDEFAULT);
	}

	bool Widget::getVisible() const {
		return ::IsWindowVisible(hWnd)!=FALSE;
	}

	Handle Widget::getHandle() const {
		return hWnd;
	}

	void Widget::setBounds(const Rect &rect) {
		DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);

		if (::SetWindowPos(hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_FRAMECHANGED) == FALSE) {
			throw WindowsError(::GetLastError());
		}
	}

	Rect Widget::getBounds() const {
		RECT rect = { 0 };

		if (::GetWindowRect(hWnd, &rect) == FALSE) {
			throw WindowsError(::GetLastError());
		} else {
			return Rect(rect.left, rect.top, rect.right, rect.bottom);
		}
	}

	void Widget::setClientBounds(const Rect &rect) {
		DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
		
		if (::SetWindowPos(hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_FRAMECHANGED) == FALSE) {
			throw WindowsError(::GetLastError());
		}
	}

	Rect Widget::getClientBounds() const {
		RECT rect = { 0 };

		if (::GetClientRect(hWnd, &rect) == FALSE) {
			throw WindowsError(::GetLastError());
		} else {
			return Rect(rect.left, rect.top, rect.right, rect.bottom);
		}
	}


	Widget* Widget::getParent() {
		HWND hWndParent = ::GetParent(hWnd);

		if (hWndParent == NULL) {
			return nullptr;
		}
		
		LONG lUserData = ::GetWindowLong(hWndParent, GWL_USERDATA);

		if (lUserData == NULL) {
			return nullptr;
		} 

		return reinterpret_cast<Widget*>(lUserData);
	}

	const Widget* Widget::getParent() const {
		return const_cast<Widget*>(this)->getParent();
	}

	std::wstring Widget::getText() const {
		wchar_t buffer[2048] = {0};

		if (::GetWindowText(hWnd, buffer, sizeof(buffer)) == 0) {
			throw WindowsError(::GetLastError());
		}

		return buffer;
	}

	void Widget::setText(const std::wstring &text) {
		if (::SetWindowText(hWnd, text.c_str()) == 0) {
			throw WindowsError(::GetLastError());
		}
	}

	void Widget::create(DWORD dwExStyle, const wchar_t *lpClassName, const wchar_t *lpWindowName, DWORD dwStyle, int x, int y, int w, int h, HWND hWndParent, HMENU hMenu) {
		hWnd = ::CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, w, h, hWndParent, hMenu, ::GetModuleHandle(NULL), NULL);

		if (hWnd == NULL) {
			throw WindowsError(::GetLastError());
		}

		::SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(this));

		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
		HFONT hFont = ::CreateFontIndirect(&ncm.lfMessageFont);
		::SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
	}

	void Widget::setEnable(bool enable) {
		::EnableWindow(hWnd, enable ? TRUE : FALSE);
	}

	bool Widget::getEnable() const {
		return ::IsWindowEnabled(hWnd) != 0;
	}

    bool Widget::hasFocus() const {
        return ::GetFocus() == this->getHandle();
    }

    void Widget::setFocus() {
        if (::SetFocus(this->hWnd) == NULL) {
            throw WindowsError(::GetLastError());
        }
    }

    void Widget::tryFocus() {
        ::SetFocus(this->hWnd);
    }
}
