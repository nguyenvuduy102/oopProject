# OOP Project
## Compile
1. Mở terminal/cmd.  
2. Di chuyển đến thư mục `release`.
3. Compile code trong thư mục source sang file thực thi trong release:
>  g++ ..\source\main.cpp ..\source\GameMain\Core\src\*.cpp ..\source\GameMain\Menu\src\*.cpp ..\source\ShapedGames\FlappyBird\src\*.cpp ..                   \source\ShapedGames\PongGame\src\*.cpp ..\source\ShapedGames\SnakeGame\src\*.cpp ..\source\ShapedGames\TetrisGame\src\*.cpp  -o Game -I"C:\Program Files\SFML-3.0.0\include" -L"C:\Program Files\SFML-3.0.0\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
4. Sau khi chạy xong, trong release/ sẽ có file Game.exe.

## Run
Trong thư mục release, chạy chương trình:
> Game.exe