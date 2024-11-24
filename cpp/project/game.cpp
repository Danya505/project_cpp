#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <string>

const int GAME_WIDTH = 500;
const int GAME_HEIGHT = 500;

struct Rocket {
    int x = 200;
    int y = 450;
    int width = 100;
    int height = 20;
    int xDirection = 10;
    Fl_Color color = FL_DARK_BLUE;
} rocket;

struct Ball {
    int x = 100;
    int y = 80;
    int radius = 10;
    int xDirection = 3;
    int yDirection = 5;
    int score = 0;
    Fl_Color color = FL_RED;
} ball;

class GameWindow : public Fl_Double_Window {
public:
    GameWindow(int w, int h, const char* title = 0) : Fl_Double_Window(w, h, title) {
        color(FL_WHITE);
        end();
    }

    void draw() override {
        Fl_Double_Window::draw();
        drawBackground();
        drawRocket();
        drawBall();
        drawScore();
        
        if (gameOver) {
            drawGameOver();
        } else if (victory) {
            drawVictory();
        }
    }

    int handle(int event) override {
        switch (event) {
            case FL_KEYDOWN:
                if (Fl::event_key() == FL_Left) {
                    rocket.x -= rocket.xDirection;
                } else if (Fl::event_key() == FL_Right) {
                    rocket.x += rocket.xDirection;
                }
                clampRocketPosition();
                redraw();
                return 1;
            default:
                return Fl_Double_Window::handle(event);
        }
    }

    void update() {
        if (!gameOver && !victory) {
            updateBall();
            redraw();
            Fl::repeat_timeout(1.0/60, Timer_CB, this);
        }
    }

private:
    bool gameOver = false;
    bool victory = false;

    void drawBackground() {
        fl_rectf(0, 0, GAME_WIDTH, GAME_HEIGHT, fl_rgb_color(245, 240, 225));
    }

    void drawRocket() {
        fl_rectf(rocket.x, rocket.y, rocket.width, rocket.height, rocket.color);
    }

    void drawBall() {
        fl_color(ball.color);
        fl_pie(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, 0, 360);
    }

    void drawScore() {
        fl_color(FL_BLACK);
        fl_font(FL_HELVETICA, 16);
        fl_draw("Score: ", 20, 30);
        fl_draw(std::to_string(ball.score).c_str(), 80, 30);
    }

    void drawGameOver() {
        fl_color(FL_BLACK);
        fl_font(FL_HELVETICA, 48);
        fl_draw("GAME OVER", GAME_WIDTH / 2 - 150, GAME_HEIGHT / 2);
    }

    void drawVictory() {
        fl_color(FL_BLACK);
        fl_font(FL_HELVETICA, 48);
        fl_draw("VICTORY", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2);
    }

    void clampRocketPosition() {
        if (rocket.x < 0) rocket.x = 0;
        if (rocket.x + rocket.width > GAME_WIDTH) rocket.x = GAME_WIDTH - rocket.width;
    }

    void updateBall() {
        ball.x += ball.xDirection;
        ball.y += ball.yDirection;

        if (ball.y + ball.radius > GAME_HEIGHT || ball.y - ball.radius < 0) {
            ball.yDirection = -ball.yDirection;
        }
        if (ball.x + ball.radius > GAME_WIDTH || ball.x - ball.radius < 0) {
            ball.xDirection = -ball.xDirection;
        }

        bool rocketCollision = ball.y + ball.radius > rocket.y &&
                               ball.x + ball.radius > rocket.x &&
                               ball.x - ball.radius < rocket.x + rocket.width &&
                               ball.y - ball.radius < rocket.y + rocket.height;

        if (rocketCollision) {
            ball.yDirection = -ball.yDirection;
            ball.score += 1;
            if (ball.score >= 7) victory = true;
        }

        if (ball.y - ball.radius > rocket.y + rocket.height) {
            gameOver = true;
        }
    }
public:
    static void Timer_CB(void *data) {
        GameWindow *gw = (GameWindow*)data;
        gw->update();
    }
};

int main(int argc, char **argv) {
    GameWindow window(GAME_WIDTH, GAME_HEIGHT, "Simple Game");
    window.show(argc, argv);
    Fl::add_timeout(1.0/60, GameWindow::Timer_CB, &window);
    return Fl::run();
}
