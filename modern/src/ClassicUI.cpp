#include "ClassicUI.h"
#include <cstdio>
#include <cstring>

namespace ClassicUI {

static Vector2 s_virtualMouse = { 0, 0 };

void SetVirtualMouse(Vector2 mouse) {
    s_virtualMouse = mouse;
}

Vector2 GetVirtualMouse() {
    return s_virtualMouse;
}

void DrawSunkenBox(Rectangle rect, Color bgColor) {
    DrawRectangleRec(rect, bgColor);
    DrawLine((int)rect.x, (int)rect.y, (int)(rect.x + rect.width), (int)rect.y, CLR_SHADOW);
    DrawLine((int)rect.x, (int)rect.y, (int)rect.x, (int)(rect.y + rect.height), CLR_SHADOW);
    DrawLine((int)rect.x + 1, (int)rect.y + 1, (int)(rect.x + rect.width - 1), (int)rect.y + 1, CLR_DARK_SHADOW);
    DrawLine((int)rect.x + 1, (int)rect.y + 1, (int)rect.x + 1, (int)(rect.y + rect.height - 1), CLR_DARK_SHADOW);
    DrawLine((int)(rect.x + rect.width - 1), (int)rect.y, (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height), CLR_LIGHT);
    DrawLine((int)rect.x, (int)(rect.y + rect.height - 1), (int)(rect.x + rect.width), (int)(rect.y + rect.height - 1), CLR_LIGHT);
}

void DrawRaisedBox(Rectangle rect) {
    DrawRectangleRec(rect, CLR_BG);
    DrawLine((int)rect.x, (int)rect.y, (int)(rect.x + rect.width - 1), (int)rect.y, CLR_LIGHT);
    DrawLine((int)rect.x, (int)rect.y, (int)rect.x, (int)(rect.y + rect.height - 1), CLR_LIGHT);
    DrawLine((int)(rect.x + rect.width - 1), (int)rect.y, (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height), CLR_DARK_SHADOW);
    DrawLine((int)rect.x, (int)(rect.y + rect.height - 1), (int)(rect.x + rect.width), (int)(rect.y + rect.height - 1), CLR_DARK_SHADOW);
    DrawLine((int)(rect.x + rect.width - 2), (int)rect.y + 1, (int)(rect.x + rect.width - 2), (int)(rect.y + rect.height - 1), CLR_SHADOW);
    DrawLine((int)rect.x + 1, (int)(rect.y + rect.height - 2), (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height - 2), CLR_SHADOW);
}

void DrawGroupBox(Rectangle rect, const char* caption) {
    int textWidth = MeasureText(caption, 10);
    int topY = (int)rect.y + 6;

    // Etched border (sunken rectangle)
    DrawLine((int)rect.x, topY, (int)rect.x + 8, topY, CLR_SHADOW);
    DrawLine((int)rect.x, topY + 1, (int)rect.x + 8, topY + 1, CLR_LIGHT);

    DrawLine((int)rect.x + 12 + textWidth, topY, (int)(rect.x + rect.width - 1), topY, CLR_SHADOW);
    DrawLine((int)rect.x + 12 + textWidth, topY + 1, (int)(rect.x + rect.width - 2), topY + 1, CLR_LIGHT);

    DrawLine((int)rect.x, topY, (int)rect.x, (int)(rect.y + rect.height - 1), CLR_SHADOW);
    DrawLine((int)rect.x + 1, topY + 1, (int)rect.x + 1, (int)(rect.y + rect.height - 2), CLR_LIGHT);

    DrawLine((int)rect.x, (int)(rect.y + rect.height - 2), (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height - 2), CLR_SHADOW);
    DrawLine((int)rect.x, (int)(rect.y + rect.height - 1), (int)(rect.x + rect.width), (int)(rect.y + rect.height - 1), CLR_LIGHT);

    DrawLine((int)(rect.x + rect.width - 2), topY, (int)(rect.x + rect.width - 2), (int)(rect.y + rect.height - 1), CLR_SHADOW);
    DrawLine((int)(rect.x + rect.width - 1), topY, (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height), CLR_LIGHT);

    DrawText(caption, (int)rect.x + 10, (int)rect.y, 10, CLR_TEXT);
}

int DrawTabs(Rectangle rect, const char* const* tabs, int count, int activeTab) {
    float tabWidth = rect.width / (float)count;
    float tabHeight = rect.height;

    for (int i = 0; i < count; i++) {
        Rectangle tabRect = { rect.x + i * tabWidth, rect.y, tabWidth, tabHeight };
        bool isActive = (i == activeTab);

        if (CheckCollisionPointRec(s_virtualMouse, tabRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            activeTab = i;
            isActive = true;
        }

        DrawRectangleRec(tabRect, CLR_BG);

        DrawLine((int)tabRect.x, (int)tabRect.y, (int)(tabRect.x + tabRect.width - 1), (int)tabRect.y, CLR_LIGHT);
        DrawLine((int)tabRect.x, (int)tabRect.y, (int)tabRect.x, (int)(tabRect.y + tabRect.height), CLR_LIGHT);
        DrawLine((int)(tabRect.x + tabRect.width - 1), (int)tabRect.y, (int)(tabRect.x + tabRect.width - 1), (int)(tabRect.y + tabRect.height), CLR_DARK_SHADOW);

        if (!isActive) {
            DrawLine((int)tabRect.x, (int)(tabRect.y + tabRect.height - 1), (int)(tabRect.x + tabRect.width), (int)(tabRect.y + tabRect.height - 1), CLR_LIGHT);
        }

        int tw = MeasureText(tabs[i], 10);
        int tx = (int)(tabRect.x + (tabWidth - tw) / 2.0f);
        int ty = (int)(tabRect.y + (tabHeight - 10) / 2.0f);
        DrawText(tabs[i], tx, ty, 10, isActive ? CLR_NAVY : CLR_TEXT);
    }

    return activeTab;
}

bool DrawButton(Rectangle rect, const char* caption, bool enabled, Color textColor) {
    bool hovered = enabled && CheckCollisionPointRec(s_virtualMouse, rect);
    bool pressed = hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    bool clicked = hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    if (!enabled) {
        DrawRectangleRec(rect, CLR_BG);
        DrawRectangleLinesEx(rect, 1.0f, CLR_SHADOW);
    } else if (pressed) {
        DrawRectangleRec(rect, CLR_BG);
        DrawLine((int)rect.x, (int)rect.y, (int)(rect.x + rect.width), (int)rect.y, CLR_DARK_SHADOW);
        DrawLine((int)rect.x, (int)rect.y, (int)rect.x, (int)(rect.y + rect.height), CLR_DARK_SHADOW);
        DrawLine((int)rect.x + 1, (int)rect.y + 1, (int)(rect.x + rect.width - 1), (int)rect.y + 1, CLR_SHADOW);
        DrawLine((int)rect.x + 1, (int)rect.y + 1, (int)rect.x + 1, (int)(rect.y + rect.height - 1), CLR_SHADOW);
        DrawLine((int)(rect.x + rect.width - 1), (int)rect.y, (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height), CLR_LIGHT);
        DrawLine((int)rect.x, (int)(rect.y + rect.height - 1), (int)(rect.x + rect.width), (int)(rect.y + rect.height - 1), CLR_LIGHT);
    } else {
        DrawRaisedBox(rect);
    }

    int tw = MeasureText(caption, 10);
    int tx = (int)(rect.x + (rect.width - tw) / 2.0f) + (pressed ? 1 : 0);
    int ty = (int)(rect.y + (rect.height - 10) / 2.0f) + (pressed ? 1 : 0);

    DrawText(caption, tx, ty, 10, enabled ? textColor : CLR_DISABLED);
    return clicked;
}

bool DrawUpDown(Rectangle rect, int& value, int minVal, int maxVal, int step, const char* prefix) {
    bool changed = false;

    float btnW = 15.0f;
    float editW = rect.width - btnW;
    Rectangle editRect = { rect.x, rect.y, editW, rect.height };
    Rectangle upRect   = { rect.x + editW, rect.y, btnW, rect.height / 2.0f };
    Rectangle downRect = { rect.x + editW, rect.y + rect.height / 2.0f, btnW, rect.height / 2.0f };

    DrawSunkenBox(editRect, CLR_YELLOW_BG);

    char valBuf[64];
    if (prefix) snprintf(valBuf, sizeof(valBuf), "%s%d", prefix, value);
    else snprintf(valBuf, sizeof(valBuf), "%d", value);

    int valTw = MeasureText(valBuf, 10);
    DrawText(valBuf, (int)editRect.x + 3, (int)editRect.y + (int)(editRect.height - 10) / 2, 10, CLR_TEXT);

    // Up button
    if (DrawButton(upRect, "^", true)) {
        if (value + step <= maxVal) {
            value += step;
            changed = true;
        }
    }

    // Down button
    if (DrawButton(downRect, "v", true)) {
        if (value - step >= minVal) {
            value -= step;
            changed = true;
        }
    }

    return changed;
}

bool DrawUpDownRow(float x, float y, float totalW, const char* label, int& value, int minVal, int maxVal, int step, const char* prefix) {
    float upDownW = 56.0f;
    float upDownH = 19.0f;
    float labelX = x;
    float labelY = y + 4.0f;
    float upDownX = x + totalW - upDownW;

    DrawText(label, (int)labelX, (int)labelY, 10, CLR_NAVY);
    Rectangle rect = { upDownX, y, upDownW, upDownH };
    return DrawUpDown(rect, value, minVal, maxVal, step, prefix);
}

void DrawReadOnlyEdit(Rectangle rect, const char* text, Color bgColor, Color textColor) {
    DrawSunkenBox(rect, bgColor);
    DrawText(text, (int)rect.x + 4, (int)rect.y + (int)(rect.height - 10) / 2, 10, textColor);
}

void DrawReadOnlyEditRow(float x, float y, float totalW, const char* label, const char* text) {
    float editW = 56.0f;
    float editH = 19.0f;
    float labelX = x;
    float labelY = y + 4.0f;
    float editX = x + totalW - editW;

    DrawText(label, (int)labelX, (int)labelY, 10, CLR_NAVY);
    Rectangle rect = { editX, y, editW, editH };
    DrawReadOnlyEdit(rect, text, CLR_EDIT_BG, CLR_TEXT);
}

void DrawLabel(float x, float y, const char* text, int fontSize, Color color) {
    DrawText(text, (int)x, (int)y, fontSize, color);
}

} // namespace ClassicUI
