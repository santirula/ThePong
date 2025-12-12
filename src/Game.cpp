#include "Game.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

Game::Game()
    : window(sf::VideoMode(800, 600), "Pong Game - Extended Edition"),
      leftPaddle(15.f, 100.f, 30.f, 250.f, 400.f),
      rightPaddle(15.f, 100.f, 755.f, 250.f, 400.f),
      ball(10.f, 300.f),
      leftScore(0),
      rightScore(0),
      state(MENU),
      powerUpSpawnTime1(3.f),
      powerUpSpawnTime2(5.f),
      powerUpSpawnTime3(7.f) {
    
    std::cout << "=== INICIANDO JUEGO PONG ===" << std::endl;
    window.setFramerateLimit(60);
    
    // Intentar cargar diferentes fuentes del sistema
    bool fontLoaded = false;
    
    std::vector<std::string> fontPaths = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "arial.ttf",
        "fonts/arial.ttf"
    };
    
    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            fontLoaded = true;
            std::cout << "Fuente cargada: " << path << std::endl;
            break;
        }
    }
    
    if (!fontLoaded) {
        std::cerr << "ADVERTENCIA: No se pudo cargar ninguna fuente del sistema." << std::endl;
    }
    
    // Cargar imagen de fondo
    std::cout << "\n--- Intentando cargar fondo ---" << std::endl;
    bool backgroundLoaded = false;
    std::vector<std::string> backgroundPaths = {
        "assets/images/Fondo.jpg",
        "assets/images/Fondo.jpg",
        "assets/images/Fondo.jpg",
        "assets/images/Fondo.jpg"
    };
    
    for (const auto& path : backgroundPaths) {
        std::cout << "Probando: " << path << " ... ";
        if (backgroundTexture.loadFromFile(path)) {
            backgroundLoaded = true;
            std::cout << "EXITO!" << std::endl;
            
            backgroundSprite.setTexture(backgroundTexture);
            
            // Ajustar al tamaño de ventana
            sf::Vector2u texSize = backgroundTexture.getSize();
            std::cout << "Tamanio imagen: " << texSize.x << "x" << texSize.y << std::endl;
            
            float scaleX = 800.f / texSize.x;
            float scaleY = 600.f / texSize.y;
            backgroundSprite.setScale(scaleX, scaleY);
            
            std::cout << "Escala: " << scaleX << "x" << scaleY << std::endl;
            break;
        } else {
            std::cout << "No encontrado" << std::endl;
        }
    }
    
    if (!backgroundLoaded) {
        std::cerr << "\n*** ERROR: No se pudo cargar Fondo.jpg ***" << std::endl;
        std::cerr << "Copia Fondo.jpg a la carpeta 'images/' o junto al .exe" << std::endl;
    }
    std::cout << "--------------------------------\n" << std::endl;

        // Cargar música de fondo
    std::cout << "--- Intentando cargar música ---" << std::endl;
    bool musicLoaded = false;
    std::vector<std::string> musicPaths = {
        "assets/music/Music.ogg",      // Cambia "musica.ogg" por el nombre real de tu archivo
        "assets/music/Music.ogg",
        "assets/music/Music.ogg",
    };
    
    for (const auto& path : musicPaths) {
        std::cout << "Probando: " << path << " ... ";
        if (music.openFromFile(path)) {
            musicLoaded = true;
            std::cout << "EXITO!" << std::endl;
            music.setLoop(true);     // Que se repita infinitamente
            music.setVolume(30.f);   // Volumen al 50% (0-100)
            music.play();            // Iniciar música
            break;
        } else {
            std::cout << "No encontrado" << std::endl;
        }
    }
    
    if (!musicLoaded) {
        std::cerr << "\n*** ERROR: No se pudo cargar la música ***" << std::endl;
        std::cerr << "Formatos soportados: .ogg, .wav, .flac" << std::endl;
    }
    std::cout << "--------------------------------\n" << std::endl;

     std::cout << "--- Intentando cargar sonido de golpe ---" << std::endl;
    bool hitSoundLoaded = false;
    std::vector<std::string> hitSoundPaths = {
        "assets/music/hitmarker.ogg",          // Cambia "hit.wav" por el nombre real
        "assets/music/hitmarker.ogg"
       "assets/music/hitmarker.ogg",
        "assets/music/hitmarker.ogg",
    
    };
    
    for (const auto& path : hitSoundPaths) {
        std::cout << "Probando: " << path << " ... ";
        if (hitSoundBuffer.loadFromFile(path)) {
            hitSoundLoaded = true;
            std::cout << "EXITO!" << std::endl;
            hitSound.setBuffer(hitSoundBuffer);
            hitSound.setVolume(15.f);  // Volumen al 70%
            break;
        } else {
            std::cout << "No encontrado" << std::endl;
        }
    }
    
    if (!hitSoundLoaded) {
        std::cerr << "\n*** ERROR: No se pudo cargar el sonido de golpe ***" << std::endl;
    }
    std::cout << "--------------------------------\n" << std::endl;

        // Cargar sonido de game over
    std::cout << "--- Intentando cargar sonido de game over ---" << std::endl;
    bool gameOverSoundLoaded = false;
    std::vector<std::string> gameOverSoundPaths = {
        "assets/music/gay.ogg",     // Cambia por el nombre real
        "assets/music/gay.ogg",
        "assets/music/gay.ogg",
        "assets/music/gay.ogg",
        "assets/music/gay.ogg",
       "assets/music/gay.ogg",
        "assets/music/gay.ogg"
    };
    
    for (const auto& path : gameOverSoundPaths) {
        std::cout << "Probando: " << path << " ... ";
        if (gameOverSoundBuffer.loadFromFile(path)) {
            gameOverSoundLoaded = true;
            std::cout << "EXITO!" << std::endl;
            gameOverSound.setBuffer(gameOverSoundBuffer);
            gameOverSound.setVolume(80.f);  // Volumen al 80%
            break;
        } else {
            std::cout << "No encontrado" << std::endl;
        }
    }
    
    if (!gameOverSoundLoaded) {
        std::cerr << "\n*** ERROR: No se pudo cargar el sonido de game over ***" << std::endl;
    }
    std::cout << "--------------------------------\n" << std::endl;
    
    // Textos de puntuación
    leftScoreText.setFont(font);
    leftScoreText.setCharacterSize(50);
    leftScoreText.setFillColor(sf::Color::White);
    leftScoreText.setPosition(300.f, 20.f);
    leftScoreText.setString("0");
    
    rightScoreText.setFont(font);
    rightScoreText.setCharacterSize(50);
    rightScoreText.setFillColor(sf::Color::White);
    rightScoreText.setPosition(480.f, 20.f);
    rightScoreText.setString("0");
    
    // Menú
    menuTitle.setFont(font);
    menuTitle.setCharacterSize(120);
    menuTitle.setFillColor(sf::Color::Cyan);
    menuTitle.setString("PONG");
    menuTitle.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = menuTitle.getLocalBounds();
    menuTitle.setOrigin(titleBounds.left + titleBounds.width/2.0f, titleBounds.top + titleBounds.height/2.0f);
    menuTitle.setPosition(400.f, 120.f);
    
    menuInstruction.setFont(font);
    menuInstruction.setCharacterSize(24);
    menuInstruction.setFillColor(sf::Color(200, 200, 200));
    menuInstruction.setString("Presiona ESPACIO para comenzar");
    sf::FloatRect instrBounds = menuInstruction.getLocalBounds();
    menuInstruction.setOrigin(instrBounds.left + instrBounds.width/2.0f, instrBounds.top + instrBounds.height/2.0f);
    menuInstruction.setPosition(400.f, 500.f);
    
    menuControls.setFont(font);
    menuControls.setCharacterSize(20);
    menuControls.setFillColor(sf::Color::White);
    menuControls.setString("CONTROLES\n\nJugador 1: W / S\nJugador 2: Flechas");
    sf::FloatRect ctrlBounds = menuControls.getLocalBounds();
    menuControls.setOrigin(ctrlBounds.left + ctrlBounds.width/2.0f, ctrlBounds.top);
    menuControls.setPosition(250.f, 250.f);
    
    menuPowerUps.setFont(font);
    menuPowerUps.setCharacterSize(20);
    menuPowerUps.setFillColor(sf::Color::White);
    menuPowerUps.setString("POWER-UPS\n\nVerde: Crece paleta\nRojo: Acelera bola");
    sf::FloatRect pwrBounds = menuPowerUps.getLocalBounds();
    menuPowerUps.setOrigin(pwrBounds.left + pwrBounds.width/2.0f, pwrBounds.top);
    menuPowerUps.setPosition(550.f, 250.f);
    
    menuGoal.setFont(font);
    menuGoal.setCharacterSize(22);
    menuGoal.setFillColor(sf::Color(255, 215, 0));
    menuGoal.setString("Primer jugador en llegar a 10 puntos GANA");
    sf::FloatRect goalBounds = menuGoal.getLocalBounds();
    menuGoal.setOrigin(goalBounds.left + goalBounds.width/2.0f, goalBounds.top);
    menuGoal.setPosition(400.f, 400.f);
    
    pauseText.setFont(font);
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setString("PAUSA");
    pauseText.setPosition(280.f, 250.f);
    
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(70);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(180.f, 200.f);
    
    winnerText.setFont(font);
    winnerText.setCharacterSize(40);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(200.f, 300.f);
    
    ball.reset(800.f, 600.f);
}

void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        processEvents();
        
        if (state == PLAYING) {
            update(dt);
        }
        
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (state == PLAYING) {
                    state = PAUSED;
                } else if (state == PAUSED) {
                    state = PLAYING;
                } else {
                    window.close();
                }
            }
            
            if (event.key.code == sf::Keyboard::Space) {
                if (state == MENU) {
                    state = PLAYING;
                    powerUpClock1.restart();
                    powerUpClock2.restart();
                    powerUpClock3.restart();
                } else if (state == PAUSED) {
                    state = PLAYING;
                } else if (state == GAME_OVER) {
                    resetGame();
                    state = MENU;
                }
            }
        }
    }
}

void Game::update(float dt) {
    // Control paddles
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        leftPaddle.moveUp(dt, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        leftPaddle.moveDown(dt, 600.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        rightPaddle.moveUp(dt, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        rightPaddle.moveDown(dt, 600.f);
    }
    
    ball.update(dt);
    checkCollisions();
    updateScore();
    
    // Generar power-up 1
    if (powerUpClock1.getElapsedTime().asSeconds() > powerUpSpawnTime1 && !powerUp1.isActive()) {
        powerUp1.spawn(800.f, 600.f);
        powerUpClock1.restart();
        powerUpSpawnTime1 = 3.f + (std::rand() % 5);
    }
    
    // Generar power-up 2
    if (powerUpClock2.getElapsedTime().asSeconds() > powerUpSpawnTime2 && !powerUp2.isActive()) {
        powerUp2.spawn(800.f, 600.f);
        powerUpClock2.restart();
        powerUpSpawnTime2 = 4.f + (std::rand() % 6);
    }
    
    // Generar power-up 3
    if (powerUpClock3.getElapsedTime().asSeconds() > powerUpSpawnTime3 && !powerUp3.isActive()) {
        powerUp3.spawn(800.f, 600.f);
        powerUpClock3.restart();
        powerUpSpawnTime3 = 5.f + (std::rand() % 7);
    }
    
    checkPowerUpCollision();
}

void Game::checkCollisions() {
    sf::Vector2f ballPos = ball.getPosition();
    
    if (ballPos.y <= 10.f || ballPos.y >= 590.f) {
        ball.reverseY();
    }
    
    if (ball.getBounds().intersects(leftPaddle.getBounds())) {
          hitSound.play(); 
        ball.reverseX();
        ball.setPosition(leftPaddle.getBounds().left + leftPaddle.getBounds().width + 10.f, ballPos.y);
        ball.setLastPaddleHit(1);
        
        float paddleCenter = leftPaddle.getTop() + leftPaddle.getHeight() / 2.f;
        float hitOffset = (ballPos.y - paddleCenter) / (leftPaddle.getHeight() / 2.f);
        hitOffset = std::max(-1.f, std::min(1.f, hitOffset));
        
        if (std::abs(hitOffset) > 0.3f) {
            ball.increaseSpeed(std::abs(hitOffset) * 20.f);
        }
    }
    
    if (ball.getBounds().intersects(rightPaddle.getBounds())) {
        hitSound.play(); 
        ball.reverseX();
        ball.setPosition(rightPaddle.getBounds().left - 10.f, ballPos.y);
        ball.setLastPaddleHit(2);
        
        float paddleCenter = rightPaddle.getTop() + rightPaddle.getHeight() / 2.f;
        float hitOffset = (ballPos.y - paddleCenter) / (rightPaddle.getHeight() / 2.f);
        hitOffset = std::max(-1.f, std::min(1.f, hitOffset));
        
        if (std::abs(hitOffset) > 0.3f) {
            ball.increaseSpeed(std::abs(hitOffset) * 20.f);
        }
    }
}

void Game::checkPowerUpCollision() {
    // Power-up 1
    if (powerUp1.isActive() && ball.getBounds().intersects(powerUp1.getBounds())) {
        PowerUpType type = powerUp1.getType();
        int lastHit = ball.getLastPaddleHit();
        
        if (type == GROW_PADDLE) {
            if (lastHit == 1) {
                leftPaddle.growHeight(40.f);
            } else if (lastHit == 2) {
                rightPaddle.growHeight(40.f);
            }
        } else if (type == SPEED_BALL) {
            ball.increaseSpeed(50.f);
        }
        
        powerUp1.deactivate();
    }
    
    // Power-up 2
    if (powerUp2.isActive() && ball.getBounds().intersects(powerUp2.getBounds())) {
        PowerUpType type = powerUp2.getType();
        int lastHit = ball.getLastPaddleHit();
        
        if (type == GROW_PADDLE) {
            if (lastHit == 1) {
                leftPaddle.growHeight(40.f);
            } else if (lastHit == 2) {
                rightPaddle.growHeight(40.f);
            }
        } else if (type == SPEED_BALL) {
            ball.increaseSpeed(50.f);
        }
        
        powerUp2.deactivate();
    }
    
    // Power-up 3
    if (powerUp3.isActive() && ball.getBounds().intersects(powerUp3.getBounds())) {
        PowerUpType type = powerUp3.getType();
        int lastHit = ball.getLastPaddleHit();
        
        if (type == GROW_PADDLE) {
            if (lastHit == 1) {
                leftPaddle.growHeight(40.f);
            } else if (lastHit == 2) {
                rightPaddle.growHeight(40.f);
            }
        } else if (type == SPEED_BALL) {
            ball.increaseSpeed(50.f);
        }
        
        powerUp3.deactivate();
    }
}

void Game::updateScore() {
    sf::Vector2f ballPos = ball.getPosition();
    
    if (ballPos.x < 0) {
        rightScore++;
        rightScoreText.setString(std::to_string(rightScore));
        ball.reset(800.f, 600.f);
        leftPaddle.resetHeight();
        rightPaddle.resetHeight();
        
        if (rightScore >= 10) {
            state = GAME_OVER;
            winnerText.setString("Jugador 2 Gana!\n\nPresiona ESPACIO");
             gameOverSound.play();  // <- AGREGAR ESTA LÍNEA
        }
    }
    
    if (ballPos.x > 800.f) {
        leftScore++;
        leftScoreText.setString(std::to_string(leftScore));
        ball.reset(800.f, 600.f);
        leftPaddle.resetHeight();
        rightPaddle.resetHeight();
        
        if (leftScore >= 10) {
            state = GAME_OVER;
            winnerText.setString("Jugador 1 Gana!\n\nPresiona ESPACIO");
             gameOverSound.play();  // <- AGREGAR ESTA LÍNEA
        }
    }
}

void Game::resetGame() {
    leftScore = 0;
    rightScore = 0;
    leftScoreText.setString("0");
    rightScoreText.setString("0");
    ball.reset(800.f, 600.f);
    leftPaddle.resetHeight();
    rightPaddle.resetHeight();
    powerUp1.deactivate();
    powerUp2.deactivate();
    powerUp3.deactivate();
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    // DIBUJAR FONDO SIEMPRE PRIMERO
    window.draw(backgroundSprite);
    
    if (state == MENU) {
        renderMenu();
    } else if (state == PLAYING || state == PAUSED) {
        // Línea central
        sf::RectangleShape centerLine(sf::Vector2f(5.f, 600.f));
        centerLine.setPosition(397.5f, 0.f);
        centerLine.setFillColor(sf::Color(100, 100, 100));
        window.draw(centerLine);
        
        leftPaddle.draw(window);
        rightPaddle.draw(window);
        ball.draw(window);
        
        // Dibujar los 3 power-ups
        powerUp1.draw(window);
        powerUp2.draw(window);
        powerUp3.draw(window);
        
        window.draw(leftScoreText);
        window.draw(rightScoreText);
        
        if (state == PAUSED) {
            renderPause();
        }
    } else if (state == GAME_OVER) {
        renderGameOver();
    }
    
    window.display();
}

void Game::renderMenu() {
    // Fondo con efectos
    sf::RectangleShape topBar(sf::Vector2f(800.f, 5.f));
    topBar.setPosition(0.f, 180.f);
    topBar.setFillColor(sf::Color::Cyan);
    window.draw(topBar);
    
    sf::RectangleShape leftDecor(sf::Vector2f(15.f, 80.f));
    leftDecor.setPosition(50.f, 260.f);
    leftDecor.setFillColor(sf::Color(100, 200, 255));
    window.draw(leftDecor);
    
    sf::RectangleShape rightDecor(sf::Vector2f(15.f, 80.f));
    rightDecor.setPosition(735.f, 260.f);
    rightDecor.setFillColor(sf::Color(100, 200, 255));
    window.draw(rightDecor);
    
    sf::CircleShape greenPowerUp(12.f);
    greenPowerUp.setPosition(470.f, 290.f);
    greenPowerUp.setFillColor(sf::Color::Green);
    window.draw(greenPowerUp);
    
    sf::CircleShape redPowerUp(12.f);
    redPowerUp.setPosition(470.f, 330.f);
    redPowerUp.setFillColor(sf::Color::Red);
    window.draw(redPowerUp);
    
    sf::RectangleShape goldLine(sf::Vector2f(600.f, 3.f));
    goldLine.setPosition(100.f, 390.f);
    goldLine.setFillColor(sf::Color(255, 215, 0));
    window.draw(goldLine);
    
    window.draw(menuTitle);
    window.draw(menuInstruction);
    window.draw(menuControls);
    window.draw(menuPowerUps);
    window.draw(menuGoal);
}

void Game::renderPause() {
    sf::RectangleShape overlay(sf::Vector2f(800.f, 600.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);
    window.draw(pauseText);
    
    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setCharacterSize(30);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setString("Presiona ESPACIO o ESC para continuar");
    resumeText.setPosition(150.f, 330.f);
    window.draw(resumeText);
}

void Game::renderGameOver() {
    window.draw(gameOverText);
    window.draw(winnerText);
}