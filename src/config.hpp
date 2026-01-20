#pragma once

namespace Config {
    constexpr float CellSize = 100.f;
    constexpr float LineThickness = 5.f;
    constexpr float GridSize = (CellSize * 3.f) + (LineThickness * 2.f);

    constexpr int WindowWidth = 800;
    constexpr int WindowHeight = 600;

    constexpr float GridOriginX = (WindowWidth - GridSize) / 2.f;
    constexpr float GridOriginY = (WindowHeight - GridSize) / 2.f;

    constexpr float CrossThickness = 7.f;
    constexpr float CrossSize = CellSize * 0.8f;

    constexpr float CircleRadius = (CellSize / 2.f) - 15.f;
    constexpr float CircleThickness = 7.f;

    enum Player { None = 1, X = 2, O = 3 };
}

