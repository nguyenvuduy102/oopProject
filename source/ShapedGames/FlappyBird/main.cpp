#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <random>
#include <string>
#include <optional>
#include <algorithm>

using namespace sf;

class SoundManager
{
private:
	SoundBuffer chingBuffer, hopBuffer, dishkBuffer;
	std::unique_ptr<Sound> ching, hop, dishk;

public:
	SoundManager()
		: chingBuffer("audio/score.wav"),
		  hopBuffer("audio/flap.wav"),
		  dishkBuffer("audio/crash.wav"),
		  ching(std::make_unique<Sound>(chingBuffer)),
		  hop(std::make_unique<Sound>(hopBuffer)),
		  dishk(std::make_unique<Sound>(dishkBuffer))
	{
	}

	void playChing()
	{
		if (ching)
			ching->play();
	}
	void playHop()
	{
		if (hop)
			hop->play();
	}
	void playDishk()
	{
		if (dishk)
			dishk->play();
	}
};

class TextureManager
{
private:
	Texture flappy[6];
	Texture pipe;
	Texture background;
	Texture gameover;

public:
	TextureManager()
		: flappy{Texture{"images/flappy1.png"},
				 Texture{"images/flappy2.png"},
				 Texture{"images/flappy3.png"},
				 Texture{"images/flappy3.png"},
				 Texture{"images/flappy3.png"},
				 Texture{"images/flappy3.png"}},
		  pipe{"images/pipe.png"},
		  background{"images/background.png"},
		  gameover{"images/gameover.png"}
	{
	}

	const Texture &getFlappy(int index) const { return flappy[index]; }
	const Texture &getPipe() const { return pipe; }
	const Texture &getBackground() const { return background; }
	const Texture &getGameover() const { return gameover; }
};

class Flappy
{
private:
	Sprite sprite;
	double v = 0.0;
	int frame = 0;
	const TextureManager &textures;

public:
	Flappy(const TextureManager &tex) : textures(tex), sprite(tex.getFlappy(0))
	{
		sprite.setPosition({250.f, 510.f});
		sprite.setScale({2.f, 2.f});
	}

	void update(int gameFrames, bool animate, bool applyPhysics)
	{
		if (animate && (gameFrames % 6 == 0))
		{
			frame = (frame + 1) % 3;
		}
		sprite.setTexture(textures.getFlappy(frame));

		if (applyPhysics)
		{
			sprite.move({0.f, static_cast<float>(v)});
			v += 0.5;
			auto pos = sprite.getPosition();
			if (pos.y < 0.f)
			{
				sprite.setPosition({250.f, 0.f});
				v = 0.0;
			}
		}
	}

	void flap() { v = -8.0; }
	void reset()
	{
		v = 0.0;
		frame = 0;
		sprite.setPosition({250.f, 510.f});
	}
	Sprite &getSprite() { return sprite; }
	const Sprite &getSprite() const { return sprite; }
	bool isOutOfBounds() const { return getSprite().getPosition().y > 1080.f; }
	float getX() const { return getSprite().getPosition().x; }
};

class PipeManager
{
private:
	std::vector<Sprite> pipes;
	const TextureManager &textures;
	std::mt19937 rng;

	void generate(int frames)
	{
		if (frames % 150 == 0)
		{
			std::uniform_int_distribution<int> dist(240, 820);
			int r = dist(rng);
			int gap = 200;

			Sprite pipeL(textures.getPipe());
			pipeL.setPosition({1000.f, static_cast<float>(r + gap)});
			pipeL.setScale({2.f, 2.5f});
			pipes.push_back(std::move(pipeL));

			Sprite pipeU(textures.getPipe());
			pipeU.setPosition({1000.f, static_cast<float>(r)});
			pipeU.setScale({2.f, -2.5f});
			pipes.push_back(std::move(pipeU));
		}
	}

	void movePipes()
	{
		for (auto &pipe : pipes)
		{
			pipe.move({-3.f, 0.f});
		}
	}

	void removeOffscreen(int frames)
	{
		if (frames % 100 == 0)
		{
			pipes.erase(std::remove_if(pipes.begin(), pipes.end(),
									   [](const Sprite &pipe)
									   { return pipe.getPosition().x <= -104.f; }),
						pipes.end());
		}
	}

public:
	PipeManager(const TextureManager &tex) : textures(tex)
	{
		std::random_device rd;
		rng.seed(rd());
	}

	void update(bool isStarted, int frames)
	{
		if (isStarted)
		{
			generate(frames);
			movePipes();
		}
		removeOffscreen(frames);
	}

	bool checkCollision(const Sprite &flappySprite) const
	{
		FloatRect birdBounds({flappySprite.getPosition().x, flappySprite.getPosition().y },
							 {68.f, 48.f}); // 34*2, 24*2

		for (const auto &pipe : pipes)
		{
			float px = pipe.getPosition().x;
			float py = pipe.getPosition().y;
			float pw = 104.f; // 52*2
			float ph;
			if (pipe.getScale().y > 0)
			{
				ph = 640.f; // 320*2
			}
			else
			{
				ph = -320.f * pipe.getScale().y;
				py -= ph;
			}
			FloatRect pipeBounds({px, py}, {pw, ph});
			if (birdBounds.findIntersection(pipeBounds))
			{
				return true;
			}
		}
		return false;
	}

	int checkScore(float flappyX) const
	{
		for (const auto &pipe : pipes)
		{
			if (pipe.getPosition().x == 250.f && flappyX == 250.f)
			{
				return 1;
			}
		}
		return 0;
	}

	const std::vector<Sprite> &getPipes() const { return pipes; }
	void clear() { pipes.clear(); }
};

class Game
{
private:
	enum class GameState
	{
		Waiting,
		Started,
		Gameover
	};
	RenderWindow window;
	TextureManager textures;
	SoundManager sounds;
	Flappy flappy;
	PipeManager pipes;
	std::array<Sprite, 6> background;
	Sprite gameover;	
	Text pressC;
	Text scoreText;
	Text highscoreText;
	Font font;
	int score = 0;
	int highscore = 0;
	int frames = 0;
	GameState state = GameState::Waiting;

public:
	Game()
		: window(VideoMode::getDesktopMode(), "Flappy Bird", State::Fullscreen),
		  flappy(textures),
		  pipes(textures),
		  background{Sprite(textures.getBackground()),
					 Sprite(textures.getBackground()),
					 Sprite(textures.getBackground()),
					 Sprite(textures.getBackground()),
					 Sprite(textures.getBackground()),
					 Sprite(textures.getBackground())},
		  gameover(textures.getGameover()),
		  pressC(font, "Press C to continue", 90),
		  scoreText(font, "", 90),
		  highscoreText(font, "", 50),
		  font("fonts/flappy.ttf")
	{
		window.setFramerateLimit(60);
		window.setKeyRepeatEnabled(false);

		for (int i = 0; i < 6; ++i)
		{
			background[i].setScale({1.4f, 2.2f});
			background[i].setPosition({static_cast<float>(i * 333), 0.f});
		}

		gameover.setOrigin({96.f, 21.f});
		gameover.setPosition({980.f, 350.f});
		gameover.setScale({3.f, 3.f});

		pressC.setFillColor(Color::White);
		FloatRect pressBounds = pressC.getLocalBounds();
		pressC.setOrigin({pressBounds.size.x / 2.f, 0.f});
		pressC.setPosition({960.f, 450.f});

		scoreText.setFillColor(Color::White);
		scoreText.setPosition({50.f, 0.f});

		highscoreText.setFillColor(Color::White);
		highscoreText.setPosition({30.f, 110.f});
	}

	void run()
	{
		while (window.isOpen())
		{
			handleEvents();
			update();
			render();
			frames++;
		}
	}

private:
	void handleEvents()
	{
		while (auto eventOpt = window.pollEvent())
		{
			const auto &event = *eventOpt;
			if (event.is<Event::Closed>())
			{
				window.close();
			}
			else if (event.is<Event::KeyPressed>())
			{
				const auto *keyEvent = event.getIf<Event::KeyPressed>();
				if (keyEvent)
				{
					if (keyEvent->code == Keyboard::Key::Space)
					{
						if (state == GameState::Waiting)
						{
							state = GameState::Started;
						}
						if (state == GameState::Started)
						{
							flappy.flap();
							sounds.playHop();
						}
					}
					else if (keyEvent->code == Keyboard::Key::C && state == GameState::Gameover)
					{
						state = GameState::Waiting;
						flappy.reset();
						score = 0;
						pipes.clear();
					}
				}
			}
		}
	}

	void update()
	{
		scoreText.setString(std::to_string(score));
		highscoreText.setString("HI " + std::to_string(highscore));

		bool animate = (state == GameState::Waiting || state == GameState::Started);
		bool physics = (state == GameState::Started);
		flappy.update(frames, animate, physics);

		if (state == GameState::Started)
		{
			int deltaScore = pipes.checkScore(flappy.getX());
			if (deltaScore > 0)
			{
				sounds.playChing();
				score += deltaScore;
				if (score > highscore)
				{
					highscore = score;
				}
			}
			pipes.update(true, frames);

			if (flappy.isOutOfBounds() || pipes.checkCollision(flappy.getSprite()))
			{
				state = GameState::Gameover;
				sounds.playDishk();
			}
		}
	}

	void render()
	{
		window.clear();
		for (const auto &bg : background)
		{
			window.draw(bg);
		}

		window.draw(flappy.getSprite());
		for (const auto &pipe : pipes.getPipes())
		{
			window.draw(pipe);
		}
		window.draw(scoreText);
		window.draw(highscoreText);

		if (state == GameState::Gameover)
		{
			window.draw(gameover);
			if (frames % 60 < 30)
			{
				window.draw(pressC);
			}
		}

		window.display();
	}
};

int main()
{
	Game game;
	game.run();
	return 0;
}
