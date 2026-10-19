#include "ClassicUI.h"
#include <cstdio>
#include <cstring>
#include <cmath>

namespace ClassicUI {

static Vector2 s_virtualMouse = { 0, 0 };
static float   s_scale = 1.7f;
static int     s_baseFontSize = 17;
static Font    s_fontBold = { 0 };

void Init(float scale, const char* fontPath) {
    s_scale = scale;
    s_baseFontSize = (int)roundf(10.0f * scale);
    if (s_baseFontSize < 10) s_baseFontSize = 10;

    // Load crisp TrueType Bold font (Tahoma Bold or Segoe UI Bold)
    if (fontPath && FileExists(fontPath)) {
        s_fontBold = LoadFontEx(fontPath, s_baseFontSize, NULL, 0);
    } else if (FileExists("assets/tahomabd.ttf")) {
        s_fontBold = LoadFontEx("assets/tahomabd.ttf", s_baseFontSize, NULL, 0);
    } else if (FileExists("assets/segoeuib.ttf")) {
        s_fontBold = LoadFontEx("assets/segoeuib.ttf", s_baseFontSize, NULL, 0);
    }

    if (s_fontBold.texture.id != 0) {
        SetTextureFilter(s_fontBold.texture, TEXTURE_FILTER_BILINEAR);
    }
}

void Shutdown() {
    if (s_fontBold.texture.id != 0) {
        UnloadFont(s_fontBold);
        s_fontBold = { 0 };
    }
}

void SetVirtualMouse(Vector2 mouse) {
    s_virtualMouse = mouse;
}

Vector2 GetVirtualMouse() {
    return s_virtualMouse;
}

float GetScale() {
    return s_scale;
}

int GetBaseFontSize() {
    return s_baseFontSize;
}

void DrawTextBold(const char* text, float x, float y, int size, Color color) {
    if (!text || text[0] == '\0') return;

    int actualSize = (size <= 10) ? s_baseFontSize : (int)roundf((float)size * s_scale);

    if (s_fontBold.texture.id != 0) {
        DrawTextEx(s_fontBold, text, Vector2{ x, y }, (float)actualSize, 1.0f, color);
    } else {
        DrawText(text, (int)x, (int)y, actualSize, color);
        DrawText(text, (int)x + 1, (int)y, actualSize, color);
    }
}

int MeasureTextBold(const char* text, int size) {
    if (!text || text[0] == '\0') return 0;
    int actualSize = (size <= 10) ? s_baseFontSize : (int)roundf((float)size * s_scale);

    if (s_fontBold.texture.id != 0) {
        return (int)MeasureTextEx(s_fontBold, text, (float)actualSize, 1.0f).x;
    } else {
        return MeasureText(text, actualSize) + 1;
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
    int textWidth = MeasureTextBold(caption, 10);
    int topY = (int)rect.y + (int)roundf(6.0f * s_scale);

    // Etched border (sunken rectangle)
    DrawLine((int)rect.x, topY, (int)(rect.x + 8.0f * s_scale), topY, CLR_SHADOW);
    DrawLine((int)rect.x, topY + 1, (int)(rect.x + 8.0f * s_scale), topY + 1, CLR_LIGHT);

    DrawLine((int)(rect.x + 14.0f * s_scale + textWidth), topY, (int)(rect.x + rect.width - 1), topY, CLR_SHADOW);
    DrawLine((int)(rect.x + 14.0f * s_scale + textWidth), topY + 1, (int)(rect.x + rect.width - 2), topY + 1, CLR_LIGHT);

    DrawLine((int)rect.x, topY, (int)rect.x, (int)(rect.y + rect.height - 1), CLR_SHADOW);
    DrawLine((int)rect.x + 1, topY + 1, (int)rect.x + 1, (int)(rect.y + rect.height - 2), CLR_LIGHT);

    DrawLine((int)rect.x, (int)(rect.y + rect.height - 2), (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height - 2), CLR_SHADOW);
    DrawLine((int)rect.x, (int)(rect.y + rect.height - 1), (int)(rect.x + rect.width), (int)(rect.y + rect.height - 1), CLR_LIGHT);

    DrawLine((int)(rect.x + rect.width - 2), topY, (int)(rect.x + rect.width - 2), (int)(rect.y + rect.height - 1), CLR_SHADOW);
    DrawLine((int)(rect.x + rect.width - 1), topY, (int)(rect.x + rect.width - 1), (int)(rect.y + rect.height), CLR_LIGHT);

    DrawTextBold(caption, rect.x + 10.0f * s_scale, rect.y - 1.0f * s_scale, 10, CLR_TEXT);
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

        int tw = MeasureTextBold(tabs[i], 10);
        float tx = tabRect.x + (tabWidth - tw) * 0.5f;
        float ty = tabRect.y + (tabHeight - (float)s_baseFontSize) * 0.5f;
        DrawTextBold(tabs[i], tx, ty, 10, isActive ? CLR_NAVY : CLR_TEXT);
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

    int tw = MeasureTextBold(caption, 10);
    float tx = rect.x + (rect.width - tw) * 0.5f + (pressed ? 1.0f : 0.0f);
    float ty = rect.y + (rect.height - (float)s_baseFontSize) * 0.5f + (pressed ? 1.0f : 0.0f);

    DrawTextBold(caption, tx, ty, 10, enabled ? textColor : CLR_DISABLED);
    return clicked;
}

bool DrawUpDown(Rectangle rect, int& value, int minVal, int maxVal, int step, const char* prefix) {
    bool changed = false;

    float btnW = roundf(15.0f * s_scale);
    float editW = rect.width - btnW;
    Rectangle editRect = { rect.x, rect.y, editW, rect.height };
    Rectangle upRect   = { rect.x + editW, rect.y, btnW, rect.height * 0.5f };
    Rectangle downRect = { rect.x + editW, rect.y + rect.height * 0.5f, btnW, rect.height * 0.5f };

    DrawSunkenBox(editRect, CLR_YELLOW_BG);

    char valBuf[64];
    if (prefix) snprintf(valBuf, sizeof(valBuf), "%s%d", prefix, value);
    else snprintf(valBuf, sizeof(valBuf), "%d", value);

    DrawTextBold(valBuf, editRect.x + 4.0f * s_scale, editRect.y + (editRect.height - (float)s_baseFontSize) * 0.5f, 10, CLR_TEXT);

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
    float upDownW = roundf(58.0f * s_scale);
    float upDownH = roundf(19.0f * s_scale);
    float labelX = x;
    float upDownX = x + totalW - upDownW;

    DrawTextBold(label, labelX, y + 3.0f * s_scale, 10, CLR_NAVY);
    Rectangle rect = { upDownX, y, upDownW, upDownH };
    return DrawUpDown(rect, value, minVal, maxVal, step, prefix);
}

void DrawReadOnlyEdit(Rectangle rect, const char* text, Color bgColor, Color textColor) {
    DrawSunkenBox(rect, bgColor);
    DrawTextBold(text, rect.x + 4.0f * s_scale, rect.y + (rect.height - (float)s_baseFontSize) * 0.5f, 10, textColor);
}

void DrawReadOnlyEditRow(float x, float y, float totalW, const char* label, const char* text) {
    float editW = roundf(60.0f * s_scale);
    float editH = roundf(19.0f * s_scale);
    float labelX = x;
    float editX = x + totalW - editW;

    DrawTextBold(label, labelX, y + 3.0f * s_scale, 10, CLR_NAVY);
    Rectangle rect = { editX, y, editW, editH };
    DrawReadOnlyEdit(rect, text, CLR_EDIT_BG, CLR_TEXT);
}

void DrawLabel(float x, float y, const char* text, int fontSize, Color color) {
    DrawTextBold(text, x, y, fontSize, color);
}

} // namespace ClassicUI
