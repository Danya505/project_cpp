console.log('ЭТО ПОГРУЖЕНИЕ, БРАТИК!');

var GAME = {
    width: 500,
    height: 500,
    background: '#f5f0e1'
}

var canvas = document.getElementById("canvas");
var canvasWidth = 500;
var canvasHeight = 500;
canvas.width = GAME.width;
canvas.height = GAME.height;
var canvasContext = canvas.getContext("2d");

canvasContext.fillStyle = "#f5f0e1";
canvasContext.fillRect(0, 0, canvasWidth, canvasHeight);

var ROCKET = {
    x: 0,
    y: 450,
    width: 100,
    height: 20,
    color: '#1e3d59',
    xDirection: 10,
}

var BALL = {
    color: '#ff6e40',
    x: 100,
    y: 80,
    radius: 10,
    xDirection: 3,
    yDirection: 5,
    score: 0,
}

function drawFrame() {
    canvasContext.clearRect(0, 0, GAME.width, GAME.height);
    drawBackground();
    drawRocket();
    drawBall();
    drawRocketScore();
}

function drawBackground() {
    canvasContext.fillStyle = GAME.background;
    canvasContext.fillRect(0, 0, GAME.width, GAME.height);
}

function drawRocket() {
    canvasContext.fillStyle = ROCKET.color;
    canvasContext.fillRect(ROCKET.x, ROCKET.y, ROCKET.width, ROCKET.height);
}

function drawBall() {
    canvasContext.fillStyle = BALL.color;
    canvasContext.beginPath();
    canvasContext.arc(BALL.x, BALL.y, BALL.radius, 0, 2 * Math.PI);
    canvasContext.closePath();
    canvasContext.fill();
}

function drawLose() {
    canvasContext.clearRect(0, 0, GAME.width, GAME.height);
    drawBackground();
    canvasContext.fillStyle = 'Black';
    canvasContext.font = '48px serif';
    canvasContext.textAlign = 'center';
    canvasContext.fillText('GAME OVER', GAME.width / 2, GAME.height/2);
}

function drawRocketScore() {
    canvasContext.font = '48px serif';
    canvasContext.fillText('Score', 70, 50);
    canvasContext.fillText(BALL.score, 200, 50);
}

function drawVictory() {
    canvasContext.clearRect(0, 0, GAME.width, GAME.height);
    drawBackground();
    canvasContext.fillStyle = 'Black';
    canvasContext.font = '96px serif';
    canvasContext.textAlign = 'center';
    canvasContext.fillText('VICTORY', GAME.width / 2, GAME.height/2);
}

//drawBall(100, 80, 20, '#ff6e40');
//drawBall();

function updateBall() {
    BALL.x += BALL.xDirection;
    BALL.y += BALL.yDirection;
    if ((BALL.y + BALL.radius > GAME.height) || (BALL.y - BALL.radius < 0)) {
        BALL.yDirection = -BALL.yDirection;
    }
    if ((BALL.x + BALL.radius > GAME.width) || (BALL.x - BALL.radius < 0)) {
        BALL.xDirection = -BALL.xDirection;
    }
    var racketTopLineCollision = BALL.y + BALL.radius > ROCKET.y;
    var racketLeftLineCollision = BALL.x + BALL.radius > ROCKET.x;
    var racketRightLineCollision = BALL.x - BALL.radius < ROCKET.x + ROCKET.width;
    var racketBottomLineCollision = BALL.y - BALL.radius < ROCKET.y + ROCKET.height;
    if (racketTopLineCollision && racketLeftLineCollision && racketRightLineCollision && racketBottomLineCollision) {
        BALL.yDirection = - BALL.yDirection;
        BALL.xDirection = BALL.xDirection;
        BALL.score += 1;
        console.log('Score: ',BALL.score);
    }
    //if (BALL.y - BALL.radius > ROCKET.y + ROCKET.height) {
    //drawFrame();
    //}
}

function initEventsListneres() {
    window.addEventListener('mousemove', onCanvasMouseMove);
    window.addEventListener('keydown', onCanvasKeyDown);
}

function onCanvasKeyDown(event) {
    if (event.key === 'ArrowLeft') {
        ROCKET.x -= ROCKET.xDirection;
    }
    if (event.key === 'ArrowRight') {
        ROCKET.x += ROCKET.xDirection;
    }
    clampROCKETPosition();
}

function onCanvasMouseMove(event) {
    ROCKET.x = event.clientX;
    clampROCKETPosition();
}

function clampROCKETPosition() {
    if (ROCKET.x < 0) {
        ROCKET.x = 0;
    }
    if (ROCKET.x + ROCKET.width > GAME.width) {
        ROCKET.x = GAME.width - ROCKET.width;
    }
}

function play() {
    drawFrame();
    if (BALL.y - BALL.radius > ROCKET.y + ROCKET.height) {
        drawLose();
        drawRocketScore()
    }
    else if (BALL.score < 7) {
        updateBall();
        requestAnimationFrame(play);
    }
    else if (BALL.score === 7) {
        drawVictory();
        drawRocketScore()
    }
    
}

initEventsListneres();

play();