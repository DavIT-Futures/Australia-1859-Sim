#ifndef CLASSIC_UI_H
#define CLASSIC_UI_H

#include "raylib.h"

namespace ClassicUI {

    // Classic Windows 95/98/2000 / Borland C++Builder 6 color palette
    const Color CLR_BG          = { 212, 208, 200, 255 }; // TForm standard gray (clBtnFace)
    const Color CLR_LIGHT       = { 255, 255, 255, 255 }; // 3D highlight (clBtnHighlight)
    const Color CLR_SHADOW      = { 128, 128, 128, 255 }; // 3D shadow (clBtnShadow)
    const Color CLR_DARK_SHADOW = {  64,  64,  64, 255 }; // 3D dark shadow (cl3DDkShadow)
    const Color CLR_TEXT        = {   0,   0,   0, 255 }; // Text (clWindowText)
    const Color CLR_NAVY        = {   0,   0, 128, 255 }; // Borland navy label (clNavy)
    const Color CLR_DISABLED    = { 128, 128, 128, 255 }; // Disabled text (clGrayText)
    const Color CLR_EDIT_BG     = { 255, 255, 255, 255 }; // TEdit background (clWindow)
    const Color CLR_YELLOW_BG   = { 255, 255, 128, 255 }; // Borland yellow edit background

    void Init(float scale = 1.7f, const char* fontPath = "assets/tahomabd.ttf");
    void Shutdown();

    void SetVirtualMouse(Vector2 mouse);
    Vector2 GetVirtualMouse();

    float GetScale();
    int   GetBaseFontSize();

    void DrawTextBold(const char* text, float x, float y, int size, Color color);
    int  MeasureTextBold(const char* text, int size);

    void DrawSunkenBox(Rectangle rect, Color bgColor = CLR_EDIT_BG);
    void DrawRaisedBox(Rectangle rect);
    void DrawGroupBox(Rectangle rect, const char* caption);
    int  DrawTabs(Rectangle rect, const char* const* tabs, int count, int activeTab);
    bool DrawButton(Rectangle rect, const char* caption, bool enabled = true, Color textColor = CLR_TEXT);
    bool DrawNumericRow(float x, float y, float totalW, const char* label, int& value, int minVal, int maxVal, int step = 1, const char* prefix = nullptr);
    bool DrawUpDownRow(float x, float y, float totalW, const char* label, int& value, int minVal, int maxVal, int step = 1, const char* prefix = nullptr);
    void DrawReadOnlyEdit(Rectangle rect, const char* text, Color bgColor = CLR_EDIT_BG, Color textColor = CLR_TEXT);
    void DrawReadOnlyEditRow(float x, float y, float totalW, const char* label, const char* text);
    void DrawLabel(float x, float y, const char* text, int fontSize = 10, Color color = CLR_TEXT);

} // namespace ClassicUI

#endif // CLASSIC_UI_H
