#include "ClassicUI.h"
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

namespace ClassicUI {

static Vector2      s_virtualMouse = { 0, 0 };
static float        s_scale = 1.7f;
static int          s_baseFontSize = 17;
static Font         s_fontBold = { 0 };

// State for active editable numeric text box
static unsigned int s_activeEditId = 0;
static char         s_editBuffer[32] = { 0 };
static int          s_editMinVal = 0;
static int          s_editMaxVal = 0;
static int*         s_editTargetVal = nullptr;

static unsigned int HashLabel(const char* str) {
    if (!str) return 0;
    unsigned int hash = 5381;
    for (const char* p = str; *p; p++) {
        hash = ((hash << 5) + hash) + (unsigned char)(*p);
    }
    return hash;
}

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

        if (isActive) {
            // Active tab sits 2px taller, highlighted in crisp white, connected seamlessly to panel below
            Rectangle activeR = { tabRect.x, tabRect.y - 2.0f, tabRect.width, tabRect.height + 4.0f };
            DrawRectangleRec(activeR, Color{ 248, 248, 248, 255 });

            // 3px blue highlight bar at top
            DrawRectangle((int)activeR.x, (int)activeR.y, (int)activeR.width, 3, Color{ 0, 80, 190, 255 });

            // 3D borders (left, right, top) - NO bottom border
            DrawLine((int)activeR.x, (int)activeR.y, (int)activeR.x, (int)(activeR.y + activeR.height), CLR_LIGHT);
            DrawLine((int)(activeR.x + activeR.width - 1), (int)activeR.y, (int)(activeR.x + activeR.width - 1), (int)(activeR.y + activeR.height), CLR_DARK_SHADOW);

            int tw = MeasureTextBold(tabs[i], 10);
            float tx = activeR.x + (tabWidth - tw) * 0.5f;
            float ty = activeR.y + 3.0f + (tabHeight - (float)s_baseFontSize) * 0.5f;
            DrawTextBold(tabs[i], tx, ty, 10, Color{ 0, 0, 120, 255 });
        } else {
            // Inactive tab: recessed, darker background, with bottom border separating from panel
            bool hovered = CheckCollisionPointRec(s_virtualMouse, tabRect);
            Color tabBg = hovered ? Color{ 215, 210, 202, 255 } : Color{ 180, 175, 168, 255 };
            DrawRectangleRec(tabRect, tabBg);

            // 3D borders
            DrawLine((int)tabRect.x, (int)tabRect.y, (int)(tabRect.x + tabRect.width - 1), (int)tabRect.y, CLR_LIGHT);
            DrawLine((int)tabRect.x, (int)tabRect.y, (int)tabRect.x, (int)(tabRect.y + tabRect.height), CLR_LIGHT);
            DrawLine((int)(tabRect.x + tabRect.width - 1), (int)tabRect.y, (int)(tabRect.x + tabRect.width - 1), (int)(tabRect.y + tabRect.height), CLR_DARK_SHADOW);
            // Bottom separating border
            DrawLine((int)tabRect.x, (int)(tabRect.y + tabRect.height - 1), (int)(tabRect.x + tabRect.width), (int)(tabRect.y + tabRect.height - 1), CLR_DARK_SHADOW);

            int tw = MeasureTextBold(tabs[i], 10);
            float tx = tabRect.x + (tabWidth - tw) * 0.5f;
            float ty = tabRect.y + (tabHeight - (float)s_baseFontSize) * 0.5f;
            DrawTextBold(tabs[i], tx, ty, 10, Color{ 60, 60, 60, 255 });
        }
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

// Modern Numeric Control: [-] [ Editable Text Box ] [+]
bool DrawNumericRow(float x, float y, float totalW, const char* label, int& value, int minVal, int maxVal, int step, const char* prefix) {
    bool changed = false;
    unsigned int id = HashLabel(label);

    float btnW  = roundf(22.0f * s_scale);
    float editW = roundf(56.0f * s_scale);
    float ctrlH = roundf(20.0f * s_scale);
    float ctrlW = btnW + 2.0f + editW + 2.0f + btnW;

    float ctrlX  = x + totalW - ctrlW;
    float labelX = x;

    // Draw label on left
    DrawTextBold(label, labelX, y + (ctrlH - (float)s_baseFontSize) * 0.5f, 10, CLR_NAVY);

    Rectangle minusRect = { ctrlX, y, btnW, ctrlH };
    Rectangle editRect  = { ctrlX + btnW + 2.0f, y, editW, ctrlH };
    Rectangle plusRect  = { editRect.x + editW + 2.0f, y, btnW, ctrlH };

    // Slower / Decrement [-] button
    if (DrawButton(minusRect, "-")) {
        if (value - step >= minVal) {
            value -= step;
            changed = true;
        } else if (value != minVal) {
            value = minVal;
            changed = true;
        }
        if (s_activeEditId == id) {
            snprintf(s_editBuffer, sizeof(s_editBuffer), "%d", value);
        }
    }

    // Faster / Increment [+] button
    if (DrawButton(plusRect, "+")) {
        if (value + step <= maxVal) {
            value += step;
            changed = true;
        } else if (value != maxVal) {
            value = maxVal;
            changed = true;
        }
        if (s_activeEditId == id) {
            snprintf(s_editBuffer, sizeof(s_editBuffer), "%d", value);
        }
    }

    // Text box in middle (clickable and editable with keyboard)
    bool isFocused = (s_activeEditId == id);

    if (CheckCollisionPointRec(s_virtualMouse, editRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        s_activeEditId = id;
        s_editMinVal = minVal;
        s_editMaxVal = maxVal;
        s_editTargetVal = &value;
        snprintf(s_editBuffer, sizeof(s_editBuffer), "%d", value);
        isFocused = true;
    } else if (isFocused && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(s_virtualMouse, editRect)) {
        // Clicked outside: commit value
        int v = atoi(s_editBuffer);
        if (v < minVal) v = minVal;
        if (v > maxVal) v = maxVal;
        if (value != v) {
            value = v;
            changed = true;
        }
        s_activeEditId = 0;
        isFocused = false;
    }

    if (isFocused) {
        // Read typed characters
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= '0' && key <= '9') || (key == '-' && strlen(s_editBuffer) == 0 && minVal < 0)) {
                size_t len = strlen(s_editBuffer);
                if (len < 10) {
                    s_editBuffer[len] = (char)key;
                    s_editBuffer[len + 1] = '\0';
                }
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            size_t len = strlen(s_editBuffer);
            if (len > 0) {
                s_editBuffer[len - 1] = '\0';
            }
        }

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
            int v = atoi(s_editBuffer);
            if (v < minVal) v = minVal;
            if (v > maxVal) v = maxVal;
            if (value != v) {
                value = v;
                changed = true;
            }
            s_activeEditId = 0;
            isFocused = false;
        }
    }

    // Render edit box
    DrawSunkenBox(editRect, isFocused ? Color{ 255, 255, 255, 255 } : CLR_YELLOW_BG);

    char dispBuf[64];
    if (isFocused) {
        bool showCursor = ((int)(GetTime() * 2.5) % 2 == 0);
        snprintf(dispBuf, sizeof(dispBuf), "%s%s", s_editBuffer, showCursor ? "|" : "");
    } else {
        if (prefix) snprintf(dispBuf, sizeof(dispBuf), "%s%d", prefix, value);
        else snprintf(dispBuf, sizeof(dispBuf), "%d", value);
    }

    int tw = MeasureTextBold(dispBuf, 10);
    float tx = editRect.x + (editRect.width - tw) * 0.5f;
    float ty = editRect.y + (editRect.height - (float)s_baseFontSize) * 0.5f;
    DrawTextBold(dispBuf, tx, ty, 10, isFocused ? Color{ 0, 0, 180, 255 } : CLR_TEXT);

    return changed;
}

bool DrawUpDownRow(float x, float y, float totalW, const char* label, int& value, int minVal, int maxVal, int step, const char* prefix) {
    return DrawNumericRow(x, y, totalW, label, value, minVal, maxVal, step, prefix);
}

void DrawReadOnlyEdit(Rectangle rect, const char* text, Color bgColor, Color textColor) {
    DrawSunkenBox(rect, bgColor);
    DrawTextBold(text, rect.x + 4.0f * s_scale, rect.y + (rect.height - (float)s_baseFontSize) * 0.5f, 10, textColor);
}

void DrawReadOnlyEditRow(float x, float y, float totalW, const char* label, const char* text) {
    float editW = roundf(60.0f * s_scale);
    float editH = roundf(20.0f * s_scale);
    float labelX = x;
    float editX = x + totalW - editW;

    DrawTextBold(label, labelX, y + (editH - (float)s_baseFontSize) * 0.5f, 10, CLR_NAVY);
    Rectangle rect = { editX, y, editW, editH };
    DrawReadOnlyEdit(rect, text, CLR_EDIT_BG, CLR_TEXT);
}

void DrawLabel(float x, float y, const char* text, int fontSize, Color color) {
    DrawTextBold(text, x, y, fontSize, color);
}

} // namespace ClassicUI
