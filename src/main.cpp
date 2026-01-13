#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

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



class TicTacToeGrid : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape topline;
    sf::RectangleShape botline;
    sf::RectangleShape lefline;
    sf::RectangleShape rigline;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(topline, states);
        target.draw(botline, states);
        target.draw(lefline, states);
        target.draw(rigline, states);
    }

public:
    TicTacToeGrid() {
        sf::Vector2f hSize(Config::GridSize, Config::LineThickness);
        sf::Vector2f vSize(Config::LineThickness, Config::GridSize);

        topline.setSize(hSize);
        topline.setPosition(sf::Vector2f(Config::GridOriginX, Config::GridOriginY + Config::CellSize));

        botline.setSize(hSize);
        botline.setPosition(sf::Vector2f(Config::GridOriginX, Config::GridOriginY + Config::CellSize*2 + Config::LineThickness));

        lefline.setSize(vSize);
        lefline.setPosition(sf::Vector2f(Config::GridOriginX + Config::CellSize, Config::GridOriginY));

        rigline.setSize(vSize);
        rigline.setPosition(sf::Vector2f(Config::GridOriginX + Config::CellSize * 2 + Config::LineThickness, Config::GridOriginY));
    }
};


class CrossShape : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape line1;
    sf::RectangleShape line2;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(line1, states);
        target.draw(line2, states);
    }

public:
    void setup(int pos) {
        int row = pos / 3;
        int col = pos % 3;

        float centerX = Config::GridOriginX + (col * Config::CellSize) + (col * Config::LineThickness) + (Config::CellSize / 2.f);
        float centerY = Config::GridOriginY + (row * Config::CellSize) + (row * Config::LineThickness) + (Config::CellSize / 2.f);

        line1.setSize({Config::CrossSize, Config::CrossThickness});
        line1.setOrigin({Config::CrossSize / 2, Config::CrossThickness / 2});
        line1.setPosition({centerX, centerY});
        line1.setRotation(sf::degrees(45));
        line1.setFillColor(sf::Color::Green);

        line2.setSize({Config::CrossSize, Config::CrossThickness});
        line2.setOrigin({Config::CrossSize / 2, Config::CrossThickness / 2});
        line2.setPosition({centerX, centerY});
        line2.setRotation(sf::degrees(135));
        line2.setFillColor(sf::Color::Green);
    }
};


class GameEndLines : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape line;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(line, states);
    }

public:
    void setup(int pos) {
        if (pos == 8) return;
        line.setFillColor(sf::Color::White);
        float diagonalLength = std::sqrt(2*Config::CellSize*Config::CellSize);

        if (pos <= 2) {
            line.setSize({Config::GridSize, Config::LineThickness});
            line.setPosition({Config::GridOriginX, Config::GridOriginY + Config::CellSize / 2 + (pos*(Config::CellSize + Config::LineThickness))});
        }
        else if ((pos > 2) && (pos < 6)) {
            line.setSize({Config::LineThickness, Config::GridSize});
            line.setPosition({Config::GridOriginX + Config::CellSize / 2 + ((pos-3)*(Config::CellSize + Config::LineThickness)), Config::GridOriginY});
        }
        else if (pos == 6) {
            line.setRotation(sf::degrees(45));
            line.setSize(sf::Vector2f(diagonalLength*3, Config::LineThickness));
            line.setPosition(sf::Vector2f(Config::GridOriginX, Config::GridOriginY));
        }
        else if (pos == 7) {
            line.setRotation(sf::degrees(135));
            line.setSize(sf::Vector2f(diagonalLength*3, Config::LineThickness));
            line.setPosition(sf::Vector2f(Config::GridOriginX + Config::CellSize*3 + Config::LineThickness*2, Config::GridOriginY));
        }
    }
};


class GameState : public sf::Drawable, public sf::Transformable{
private:
    sf::CircleShape circles[9];
    CrossShape crosses[9];

    GameEndLines game_end_lines[9];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int arr_pos = i * 3 + j;
                if (state[i][j] == 3)
                    target.draw(circles[arr_pos]);
                else if (state[i][j] == 2) {
                    target.draw(crosses[arr_pos]);
                }
            }
        }
        if (game_end) {
            target.draw(game_end_lines[game_end_line_no]);
        }
    }

public:
    int state[3][3];
    bool turn;
    bool game_end;
    int game_end_line_no;
    GameState() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                state[i][j] = Config::Player::None;
            }
        }
        turn = true;
        game_end = false;

        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;

            float centerX = Config::GridOriginX + (col * Config::CellSize) + (col * Config::LineThickness) + (Config::CellSize / 2.f);
            float centerY = Config::GridOriginY + (row * Config::CellSize) + (row * Config::LineThickness) + (Config::CellSize / 2.f);

            circles[i].setRadius(Config::CircleRadius);
            circles[i].setOrigin({Config::CircleRadius, Config::CircleRadius});
            circles[i].setOutlineColor(sf::Color::Red);
            circles[i].setOutlineThickness(Config::CircleThickness);
            circles[i].setFillColor(sf::Color::Black);
            circles[i].setPosition(sf::Vector2f(centerX, centerY));

            crosses[i].setup(i);
            game_end_lines[i].setup(i);
        }
    }


    void reset() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                state[i][j] = Config::Player::None;
            }
        }
        turn = true;
        game_end = false;
    }


    void updateState(int pos[2]) {
        int x = pos[0];
        int y = pos[1];

        if (state[x][y] != Config::Player::None) return;

        if (turn) state[x][y] = Config::Player::X;
        else      state[x][y] = Config::Player::O;

        if (turn) turn = false;
        else      turn = true;
    }


    void checkGameEnd() {
        for (int i = 0; i < 3; i++) {
            if ((state[i][0] == state[i][1]) && (state[i][0] == state[i][2]) && state[i][0] != 1) {
                game_end = true;
                game_end_line_no = i;
                return;
            }
        }
        for (int i = 0; i < 3; i++) {
            if ((state[0][i] == state[1][i]) && (state[0][i] == state[2][i]) && state[0][i] != 1) {
                game_end = true;
                game_end_line_no = 3+i;
                return;
            }
        }
        if ((state[0][0] == state[1][1]) && (state[0][0] == state[2][2]) && state[0][0] != 1) {
            game_end = true;
            game_end_line_no = 6;
            return;
        }
        if ((state[2][0] == state[1][1]) && (state[2][0] == state[0][2]) && state[2][0] != 1) {
            game_end = true;
            game_end_line_no = 7;
            return;
        }
        int no_blanks = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == Config::Player::None) no_blanks++;
            }
        }
        if (no_blanks == 0) {
            game_end = true;
            game_end_line_no = 8;
        }
    }

    void printState() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << state[i][j] << ", ";
            }
            std::cout << std::endl;
        }
    }
};


class Game { 
private:
    GameState gamestate;
    TicTacToeGrid grid;
    sf::RenderWindow window;

public:
    void reset_state() {
        window.clear(sf::Color::Black);
        gamestate.reset();
    }

    void run_game_loop() {
        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) 
                    window.close();
                
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == sf::Mouse::Button::Left) {
                        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                        if ((mouse_position.x >= Config::GridOriginX) && (mouse_position.x < (Config::GridOriginX + Config::CellSize * 3 + Config::LineThickness * 2)) && 
                            (mouse_position.y >= Config::GridOriginY) && (mouse_position.y < (Config::GridOriginY + Config::CellSize * 3 + Config::LineThickness * 2))) {
                            int col = (mouse_position.x - Config::GridOriginX) / (Config::CellSize + Config::LineThickness);
                            int row = (mouse_position.y - Config::GridOriginY) / (Config::CellSize + Config::LineThickness);
                            int update_arr[2] = {row, col};
                            gamestate.updateState(update_arr);
                            gamestate.checkGameEnd();
                        }
                    }
                }
            }
            window.clear(sf::Color::Black);
            window.draw(grid);
            window.draw(gamestate);
            window.display();
            if (gamestate.game_end == true) {
                sf::sleep(sf::seconds(1.5));
                reset_state();
            }
       }
    }

    Game() {
        window.create(sf::VideoMode({Config::WindowWidth, Config::WindowHeight}), "Tic Tac Toe", sf::Style::Default);
    }
};


int main()
{
    Game tic_tac_toe;
    tic_tac_toe.reset_state();
    tic_tac_toe.run_game_loop();
}

