#include "ClassicUI.h"
#include <cstdio>
#include <cstring>

namespace ClassicUI {

static Vector2 s_virtualMouse = { 0, 0 };
static Font s_uiFont = { 0 };

void SetVirtualMouse(Vector2 mouse) {
    s_virtualMouse = mouse;
}

Vector2 GetVirtualMouse() {
    return s_virtualMouse;
}

void SetUIFont(Font font) {
    s_uiFont = font;
}

Font GetUIFont() {
    return s_uiFont;
}

static inline void DrawTextClassic(const char* text, float x, float y, float size, Color color) {
    if (s_uiFont.texture.id != 0) {
        DrawTextEx(s_uiFont, text, Vector2{ x, y }, size, 0.5f, color);
    } else {
        DrawText(text, (int)x, (int)y, (int)size, color);
    }
}

static inline float MeasureTextClassic(const char* text, float size) {
    if (s_uiFont.texture.id != 0) {
        return MeasureTextEx(s_uiFont, text, size, 0.5f).x;
    } else {
        return (float)MeasureText(text, (int)size);
    }
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
    float textWidth = MeasureTextClassic(caption, 11.0f);
    int topY = (int)rect.y + 6;

    // Etched border (sunken rectangle)
    DrawLine((int)rect.x, topY, (int)rect.x + 8, topY, CLR_SHADOW);
    DrawLine((int)rect.x, topY + 1, (int)rect.x + 8, topY + 1, CLR_LIGHT);

    DrawLine((int)(rect.x + 14 + textWidth), topY, (int)(rect.x + rect.width - 1), topY, CLR_SHADOW);
    DrawLine((int)(rect.x + 14 + textWidth), topY + 1, (int)(rect.x + rect.width - 2), topY + 1, CLR_LIGHT);

    DrawLine((int)rect.x, topY, (int)rect.x, (int)(rect.y + rect.height - 1), CLR_SHADOW);
    DrawLine((int)rect.x + 1, topY + 1, (int)rect.x + 1, (int)(rect.y + rect.height - 2), CLR_LIGHT);

    DrawLine((int)rect.x, (int)(rect.y + rect.height - 2), (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height - 2), CLR_SHADOW);
    DrawLine((int)rect.x, (int)(rect.y + rect.height - 1), (int)(rect.x + rect.width), (int)(rect.y + rect.height - 1), CLR_LIGHT);

    DrawLine((int)(rect.x + rect.width - 2), topY, (int)(rect.x + rect.width - 2), (int)(rect.y + rect.height - 1), CLR_SHADOW);
    DrawLine((int)(rect.x + rect.width - 1), topY, (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height), CLR_LIGHT);

    DrawTextClassic(caption, rect.x + 10.0f, rect.y - 1.0f, 11.0f, CLR_TEXT);
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

        float tw = MeasureTextClassic(tabs[i], 11.0f);
        float tx = tabRect.x + (tabWidth - tw) * 0.5f;
        float ty = tabRect.y + (tabHeight - 11.0f) * 0.5f;
        DrawTextClassic(tabs[i], tx, ty, 11.0f, isActive ? CLR_NAVY : CLR_TEXT);
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

    float tw = MeasureTextClassic(caption, 11.0f);
    float tx = rect.x + (rect.width - tw) * 0.5f + (pressed ? 1.0f : 0.0f);
    float ty = rect.y + (rect.height - 11.0f) * 0.5f + (pressed ? 1.0f : 0.0f);

    DrawTextClassic(caption, tx, ty, 11.0f, enabled ? textColor : CLR_DISABLED);
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

    DrawTextClassic(valBuf, editRect.x + 4.0f, editRect.y + (editRect.height - 11.0f) * 0.5f, 11.0f, CLR_TEXT);

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
    float upDownW = 58.0f;
    float upDownH = 19.0f;
    float labelX = x;
    float upDownX = x + totalW - upDownW;

    DrawTextClassic(label, labelX, y + 3.0f, 11.0f, CLR_NAVY);
    Rectangle rect = { upDownX, y, upDownW, upDownH };
    return DrawUpDown(rect, value, minVal, maxVal, step, prefix);
}

void DrawReadOnlyEdit(Rectangle rect, const char* text, Color bgColor, Color textColor) {
    DrawSunkenBox(rect, bgColor);
    DrawTextClassic(text, rect.x + 4.0f, rect.y + (rect.height - 11.0f) * 0.5f, 11.0f, textColor);
}

void DrawReadOnlyEditRow(float x, float y, float totalW, const char* label, const char* text) {
    float editW = 60.0f;
    float editH = 19.0f;
    float labelX = x;
    float editX = x + totalW - editW;

    DrawTextClassic(label, labelX, y + 3.0f, 11.0f, CLR_NAVY);
    Rectangle rect = { editX, y, editW, editH };
    DrawReadOnlyEdit(rect, text, CLR_EDIT_BG, CLR_TEXT);
}

void DrawLabel(float x, float y, const char* text, float fontSize, Color color) {
    DrawTextClassic(text, x, y, fontSize, color);
}

} // namespace ClassicUI
