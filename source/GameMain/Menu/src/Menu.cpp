#include "../include/Menu.h"
#include "../../Core/include/GameManager.h"
#include "../include/FadeEffect.h"
#include <iostream>

// Constructor for Menu class, initializes menu elements
Menu::Menu(sf::RenderWindow &window)
    : m_window(window), m_selectedIndex(0), m_background(window, 150), m_titleSprite(m_titleTexture), m_clickSound(m_clickBuffer), m_slideSound(m_slideBuffer)
{
    // Load font for menu text
    if (!m_font.openFromFile("../source/assets/fonts/Montserrat-Regular.ttf"))
    {
        std::cerr << "Error: Cannot load font!\n";
    }

    // Load background music
    if (!m_music.openFromFile("../source/assets/sounds/MenuBackGroundSound.ogg"))
    {
        std::cerr << "Error: Cannot load music!\n";
    }
    else
    {
        // Configure and play music
        m_music.setLooping(true);
        m_music.setVolume(50.f);
        m_music.play();
    }

    // Load click sound effect
    if (!m_clickBuffer.loadFromFile("../source/assets/sounds/MenuClickSound.ogg"))
    {
        std::cerr << "Error: Cannot load click sound!\n";
    }
    else
    {
        // Configure click sound
        m_clickSound.setBuffer(m_clickBuffer);
        m_clickSound.setVolume(100.f);
        m_clickSound.setPitch(2.0f);
    }

    if (!m_slideBuffer.loadFromFile("../source/assets/sounds/MenuSlideSound.ogg"))
    {
        std::cerr << "Error: Cannot load slide sound!\n";
    }
    else
    {
        m_slideSound.setBuffer(m_slideBuffer);
        m_slideSound.setVolume(100.f);
        m_slideSound.setPitch(2.0f);
    }

    // Load title image
    if (!m_titleTexture.loadFromFile("../source/assets/images/GameIcon.png"))
    {
        std::cerr << "Error: Cannot load title image!\n";
    }
    else
    {
        // Set up title sprite and center it
        m_titleSprite = sf::Sprite(m_titleTexture);
        sf::Vector2u winSize = m_window.getSize();
        sf::FloatRect bounds = m_titleSprite.getLocalBounds();
        m_titleSprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        m_titleSprite.setPosition({winSize.x / 2.f, 150.f});
    }

    // Initialize menu items (Play, Settings, Exit)
    std::vector<std::string> labels = {"Play", "Game", "Credit", "Help", "Exit"};
    for (size_t i = 0; i < labels.size(); i++)
    {
        MenuItem item(labels[i], m_font, 20, {950.f, 410.f + i * 60.f});
        m_options.push_back(item);
    }
}

// Main menu loop, handles user input and rendering
int Menu::run()
{
    // Ensure background music is playing
    if (m_music.getStatus() != sf::Music::Status::Playing)
    {
        m_music.play();
    }
    FadeEffect fade(m_window.getSize()); // Initialize fade effect overlay
    bool startAction = false;
    int actionIndex = -1;

    // Menu loop
    while (m_window.isOpen())
    {
        // Update delta time for animations
        float dt = m_clock.restart().asSeconds();

        // Handle events
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return 2; // Return exit code
            }
            if (auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (fade.isFading())
                    continue; // Ignore input during fade

                // Navigate menu with keyboard
                if (keyEvent->scancode == sf::Keyboard::Scan::Up || keyEvent->scancode == sf::Keyboard::Scan::W)
                    moveUp();
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down || keyEvent->scancode == sf::Keyboard::Scan::S)
                    moveDown();
                else if (keyEvent->scancode == sf::Keyboard::Scan::Enter)
                {
                    // Play click sound and start fade effect
                    if (m_clickSound.getStatus() != sf::Sound::Status::Playing)
                        m_clickSound.play();
                    fade.startFadeIn(0.5f);
                    startAction = true;
                    actionIndex = m_selectedIndex;
                }
            }
        }

        // Update and render background (snow + gradient)
        m_background.update(dt);
        m_window.draw(m_titleSprite);

        // Update and draw menu items
        for (size_t i = 0; i < m_options.size(); i++)
        {
            m_options[i].setSelected(i == m_selectedIndex);
            m_options[i].update(dt);
            m_options[i].draw(m_window);
        }

        // Update and draw fade effect
        fade.update(dt);
        fade.draw(m_window);
        m_window.display();

        // Handle menu actions after fade completes
        if (startAction && !fade.isFading())
        {
            if (actionIndex == 0)
            {
                m_music.stop();
                return 0; // Return code for "Play"
            }
            else if (actionIndex == 1)
            {
                // Open settings menu and update selected game
                int chosen = runSettings();
                if (chosen >= 0)
                    GameManager::instance().setSelected(chosen);
                m_selectedIndex = 0;
            }
            else if (actionIndex == 2)
            {
                runCredits();
            }
            else if (actionIndex == 3)
            {
                runHelp();
            }
            else if (actionIndex == 4)
            {
                return 2; // Return code for "Exit"
            }

            // Start fade out to return to menu
            fade.startFadeOut(1.0f);
            startAction = false;
        }
    }
    return 2; // Default exit code
}

// Settings menu loop for selecting games
int Menu::runSettings()
{
    // List of available games and "Back" option
    std::vector<std::string> games = {"Tetris", "Snake", "Pong", "Flappy Bird", "Back"};
    int selected = 0;

    // Initialize settings menu items
    std::vector<MenuItem> gameOptions;
    for (size_t i = 0; i < games.size(); i++)
    {
        MenuItem item(games[i], m_font, 20, {940.f, 410.f + i * 60.f});
        gameOptions.push_back(item);
    }

    // Settings menu loop
    while (m_window.isOpen())
    {
        float dt = m_clock.restart().asSeconds();

        // Handle events
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return -1; // Return on window close
            }
            if (auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                // Navigate settings menu
                if (keyEvent->scancode == sf::Keyboard::Scan::Up || keyEvent->scancode == sf::Keyboard::Scan::W)
                {
                    selected = (selected > 0) ? selected - 1 : (int)gameOptions.size() - 1;
                    if (m_slideSound.getStatus() != sf::Sound::Status::Playing)
                        m_slideSound.play();
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down || keyEvent->scancode == sf::Keyboard::Scan::S)
                {
                    selected = (selected < (int)gameOptions.size() - 1) ? selected + 1 : 0;
                    if (m_slideSound.getStatus() != sf::Sound::Status::Playing)
                        m_slideSound.play();
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Enter)
                {
                    // Play click sound
                    if (m_clickSound.getStatus() != sf::Sound::Status::Playing)
                        m_clickSound.play();
                    if (selected == (int)gameOptions.size() - 1)
                        return -1;   // Return for "Back"
                    return selected; // Return selected game index
                }
            }
        }

        // Update and render background and title
        m_background.update(dt);
        m_window.draw(m_titleSprite);

        // Update and draw settings menu items
        for (size_t i = 0; i < gameOptions.size(); i++)
        {
            gameOptions[i].setSelected(i == selected);
            gameOptions[i].update(dt);
            gameOptions[i].draw(m_window);
        }

        m_window.display();
    }
    return -1; // Default return for settings menu
}

int Menu::runCredits()
{
    bool running = true;

    while (m_window.isOpen() && running)
    {
        float dt = m_clock.restart().asSeconds();

        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return -1;
            }
            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape ||
                    key->code == sf::Keyboard::Key::Enter)
                {
                    running = false; // thoát về menu
                }
            }
        }

        m_background.update(dt);
        m_window.draw(m_titleSprite);
        sf::RectangleShape overlay(sf::Vector2f(m_window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        m_window.draw(overlay);

        // Hiển thị dòng chữ credits
        sf::Text title(m_font, "CREDITS", 48);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition({860.f, 290.f});

        sf::Text text(m_font,
                      "                                                             Game Hub Project\n\n"
                      "Developer: Tieu Dai Duy , Nguyen Duong Gia Thuan , To Hoa Phi Long , Nguyen Vu Duy\n"
                      "                                                             Team: Awesome Team\n"
                      "                       Special Thanks: Our Teachers for guidance and inspiration,\n"
                      "                                our Friends for encouragement and support,\n\n\n\n"
                      "                                                             Press ESC to return",
                      20);

        text.setFillColor(sf::Color::White);
        text.setPosition({560.f, 420.f});

        m_window.draw(title);
        m_window.draw(text);

        m_window.display();
    }

    return 0;
}

int Menu::runHelp()
{
    bool running = true;
    int page = 0; // 0 = Tetris, 1 = Snake, 2 = Pong, 3 = Flappy

    // Nội dung hướng dẫn cho từng game
    std::vector<std::string> helpTexts = {
        "TETRIS:\n- LEFT/RIGHT: Move block\n- UP: Rotate block\n- DOWN: Drop faster\n- ESC: Quit game",
        "SNAKE:\n- Arrow keys: Control snake\n- Eat food to grow\n- Don't hit walls or yourself",
        "PONG:\n- Left player: W/S to move\n- Right player: UP/DOWN to move\n- First to score wins!",
        "FLAPPY BIRD:\n- SPACE or UP: Flap\n- Avoid pipes\n- Try to survive as long as possible"};

    while (m_window.isOpen() && running)
    {
        float dt = m_clock.restart().asSeconds();

        // --- Xử lý sự kiện ---
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return -1;
            }
            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    running = false; // Thoát help
                }
                else if (key->code == sf::Keyboard::Key::Right || key->code == sf::Keyboard::Key::D)
                {
                    if (page < (int)helpTexts.size() - 1)
                        page++;
                }
                else if (key->code == sf::Keyboard::Key::Left || key->code == sf::Keyboard::Key::A)
                {
                    if (page > 0)
                        page--;
                }
            }
        }

        // --- Vẽ nền ---
        m_background.update(dt);
        m_window.draw(m_titleSprite);

        // Thêm overlay tối mờ
        sf::RectangleShape overlay(sf::Vector2f(m_window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        m_window.draw(overlay);

        // --- Tiêu đề cố định ---
        sf::Text title(m_font, "HOW TO PLAY", 48);
        title.setFillColor(sf::Color::Cyan);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
        title.setPosition({m_window.getSize().x / 2.f, 260.f});
        m_window.draw(title);

        // --- Nội dung của trang hiện tại ---
        sf::Text content(m_font, helpTexts[page], 24);
        content.setFillColor(sf::Color::White);
        content.setPosition({800.f, 360.f});
        m_window.draw(content);

        // --- Nút Prev (mũi tên trái) ---
        if (page > 0)
        {
            sf::ConvexShape prevArrow;
            prevArrow.setPointCount(3);
            prevArrow.setPoint(0, {0.f, 20.f});  // đáy trên
            prevArrow.setPoint(1, {0.f, -20.f}); // đáy dưới
            prevArrow.setPoint(2, {-30.f, 0.f}); // mũi tên nhọn bên trái
            prevArrow.setFillColor(sf::Color::White);
            prevArrow.setPosition({740.f, 520.f}); // vị trí trung tâm

            m_window.draw(prevArrow);

            // chữ "Prev" phía trên nút
            sf::Text prevLabel(m_font, "Prev", 18);
            prevLabel.setFillColor(sf::Color::White);
            sf::FloatRect pb = prevLabel.getLocalBounds();
            prevLabel.setOrigin({pb.size.x / 2.f + 18.f, pb.size.y / 2.f});
            prevLabel.setPosition({prevArrow.getPosition().x, prevArrow.getPosition().y - 40.f});
            m_window.draw(prevLabel);
        }

        // --- Nút Next (mũi tên phải) ---
        if (page < (int)helpTexts.size() - 1)
        {
            sf::ConvexShape nextArrow;
            nextArrow.setPointCount(3);
            nextArrow.setPoint(0, {0.f, -20.f}); // đáy trên
            nextArrow.setPoint(1, {0.f, 20.f});  // đáy dưới
            nextArrow.setPoint(2, {30.f, 0.f});  // mũi tên nhọn bên phải
            nextArrow.setFillColor(sf::Color::White);
            nextArrow.setPosition({1240.f, 520.f});

            m_window.draw(nextArrow);

            // chữ "Next" phía trên nút
            sf::Text nextLabel(m_font, "Next", 18);
            nextLabel.setFillColor(sf::Color::White);
            sf::FloatRect nb = nextLabel.getLocalBounds();
            nextLabel.setOrigin({nb.size.x / 2.f - 18.f, nb.size.y / 2.f});
            nextLabel.setPosition({nextArrow.getPosition().x, nextArrow.getPosition().y - 40.f});
            m_window.draw(nextLabel);
        }

        m_window.display();
    }

    return 0;
}

// Move selection up in the menu
void Menu::moveUp()
{
    if (m_selectedIndex > 0)
        m_selectedIndex--;
    else
        m_selectedIndex = m_options.size() - 1;

    if (m_slideSound.getStatus() != sf::Sound::Status::Playing)
        m_slideSound.play();
}

// Move selection down in the menu
void Menu::moveDown()
{
    if (m_selectedIndex < (int)m_options.size() - 1)
        m_selectedIndex++;
    else
        m_selectedIndex = 0;

    if (m_slideSound.getStatus() != sf::Sound::Status::Playing)
        m_slideSound.play();
}