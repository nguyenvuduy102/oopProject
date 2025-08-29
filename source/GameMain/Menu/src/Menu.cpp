#include "../include/Menu.h"
#include "../../Core/include/GameManager.h"
#include "../include/FadeEffect.h"
#include <iostream>

Menu::Menu(sf::RenderWindow &window)
    : m_window(window), m_selectedIndex(0), m_background(window, 150), m_titleSprite(m_titleTexture), m_clickSound(m_clickBuffer)
{
    if (!m_font.openFromFile("assets/fonts/Montserrat-Regular.ttf"))
    {
        std::cerr << "Error: Cannot load font!\n";
    }

    if (!m_music.openFromFile("music/Presstart.wav"))
    {
        std::cerr << "Error: Cannot load music!\n";
    }
    else
    {
        m_music.setLooping(true);
        m_music.setVolume(50.f);
        m_music.play();
    }

    if (!m_clickBuffer.loadFromFile("assets/music/MinecraftSounds.wav"))
    {
        std::cerr << "Error: Cannot load click sound!\n";
    }
    else
    {
        m_clickSound.setBuffer(m_clickBuffer);
        m_clickSound.setVolume(100.f);
        m_clickSound.setPitch(2.0f);
    }

    if (!m_titleTexture.loadFromFile("assets/images/GameIcon.png"))
    {
        std::cerr << "Error: Cannot load title image!\n";
    }
    else
    {
        m_titleSprite = sf::Sprite(m_titleTexture); // tạo sprite từ texture
        sf::Vector2u winSize = m_window.getSize();
        sf::FloatRect bounds = m_titleSprite.getLocalBounds();
        m_titleSprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        m_titleSprite.setPosition({winSize.x / 2.f, 150.f});
    }

    std::vector<std::string> labels = {"Play", "Settings", "Exit"};
    for (size_t i = 0; i < labels.size(); i++)
    {
        MenuItem item(labels[i], m_font, 20, {400.f, 300.f + i * 60.f});
        m_options.push_back(item);
    }
}

int Menu::run()
{
    if (m_music.getStatus() != sf::Music::Status::Playing)
    {
        m_music.play();
    }
    FadeEffect fade(m_window.getSize()); // overlay đen
    bool startAction = false;
    int actionIndex = -1;

    while (m_window.isOpen())
    {
        float dt = m_clock.restart().asSeconds();

        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return 2;
            }
            if (auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (fade.isFading())
                    continue; // đang fade thì ignore input

                if (keyEvent->scancode == sf::Keyboard::Scan::Up || keyEvent->scancode == sf::Keyboard::Scan::W)
                    moveUp();
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down || keyEvent->scancode == sf::Keyboard::Scan::S)
                    moveDown();
                else if (keyEvent->scancode == sf::Keyboard::Scan::Enter)
                {
                    if (m_clickSound.getStatus() != sf::Sound::Status::Playing)
                        m_clickSound.play();
                    fade.startFadeIn(0.5f); // bắt đầu fade in
                    startAction = true;
                    actionIndex = m_selectedIndex;
                }
            }
        }

        m_background.update(dt); // vừa update, vừa vẽ snow + gradient
        m_window.draw(m_titleSprite);

        for (size_t i = 0; i < m_options.size(); i++)
        {
            m_options[i].setSelected(i == m_selectedIndex);
            m_options[i].update(dt);
            m_options[i].draw(m_window);
        }

        fade.update(dt);     // cập nhật overlay
        fade.draw(m_window); // vẽ fade lên trên
        m_window.display();

        if (startAction && !fade.isFading())
        {
            // Chỗ thực hiện action sau fade
            if (actionIndex == 0)
            {
                m_music.stop();
                return 0; // Play
            }
            else if (actionIndex == 1)
            {
                int chosen = runSettings();
                if (chosen >= 0)
                    GameManager::instance().setSelected(chosen);
                m_selectedIndex = 0;
            }
            else if (actionIndex == 2)
            {
                return 2; // Exit
            }

            // Fade out trở lại menu
            fade.startFadeOut(1.0f);
            startAction = false;
        }
    }
    return 2;
}

int Menu::runSettings()
{
    std::vector<std::string> games = {"Tetris", "Snake", "Pong", "Flappy Bird", "Back"};
    int selected = 0;

    std::vector<MenuItem> gameOptions;
    for (size_t i = 0; i < games.size(); i++)
    {
        MenuItem item(games[i], m_font, 20, {400.f, 300.f + i * 60.f});
        gameOptions.push_back(item);
    }

    while (m_window.isOpen())
    {
        float dt = m_clock.restart().asSeconds();

        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return -1;
            }
            if (auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->scancode == sf::Keyboard::Scan::Up || keyEvent->scancode == sf::Keyboard::Scan::W)
                    selected = (selected > 0) ? selected - 1 : (int)gameOptions.size() - 1;
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down || keyEvent->scancode == sf::Keyboard::Scan::S)
                    selected = (selected < (int)gameOptions.size() - 1) ? selected + 1 : 0;
                else if (keyEvent->scancode == sf::Keyboard::Scan::Enter)
                {
                    if (m_clickSound.getStatus() != sf::Sound::Status::Playing)
                        m_clickSound.play();
                    if (selected == (int)gameOptions.size() - 1)
                        return -1;   // Back
                    return selected; // trả về index game
                }
            }
        }

        m_background.update(dt);
        m_window.draw(m_titleSprite);

        for (size_t i = 0; i < gameOptions.size(); i++)
        {
            gameOptions[i].setSelected(i == selected);
            gameOptions[i].update(dt);
            gameOptions[i].draw(m_window);
        }

        m_window.display();
    }
    return -1;
}

void Menu::moveUp()
{
    if (m_selectedIndex > 0)
        m_selectedIndex--;
    else
        m_selectedIndex = m_options.size() - 1;
}

void Menu::moveDown()
{
    if (m_selectedIndex < (int)m_options.size() - 1)
        m_selectedIndex++;
    else
        m_selectedIndex = 0;
}
