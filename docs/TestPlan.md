# Test Plan - Game Collection Unit Testing

## 1. Mục tiêu kiểm thử
Đảm bảo các thành phần cốt lõi của 4 game (Flappy Bird, Snake, Pong, Tetris) hoạt động đúng theo thiết kế thông qua unit testing.

## 2. Phạm vi kiểm thử
- **Flappy Bird**: Bird movement, Pipe movement, Off-screen detection
- **Snake Game**: Snake growth, Direction control, Collision detection, Food spawning
- **Pong Game**: Ball physics, Paddle movement, Boundary checking
- **Tetris Game**: Grid initialization, Row clearing, Boundary detection

## 3. Chiến lược kiểm thử
### 3.1. Unit Testing
- Sử dụng Google Test framework
- Tập trung vào testing các class core
- Mock các dependencies khi cần thiết

### 3.2. Phương pháp tiếp cận
- White-box testing dựa trên code implementation
- Boundary value analysis
- State transition testing

### 3.3. Tiêu chí hoàn thành
- 100% test cases đã defined phải pass
- Code coverage tối thiểu 80% cho các core components
- Không có critical bugs tồn đọng

## 4. Môi trường kiểm thử
- **Framework**: Google Test v1.12+
- **Compiler**: GCC/Clang với C++17 support
- **Build System**: CMake hoặc Makefile
- **OS**: Windows/Linux/macOS

## 5. Kế hoạch thực hiện
1. **Giai đoạn 1**: Setup testing environment
2. **Giai đoạn 2**: Implement unit tests cho từng game
3. **Giai đoạn 3**: Chạy tests và ghi nhận kết quả
4. **Giai đoạn 4**: Fix bugs và retest
5. **Giai đoạn 5**: Final test report

## 6. Rủi ro và giảm thiểu
- **Rủi ro**: Mocking SFML components có thể phức tạp
- **Giảm thiểu**: Sử dụng interface abstraction và dependency injection