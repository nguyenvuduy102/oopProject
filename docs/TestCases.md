# Test Cases - Game Collection Unit Tests

## Flappy Bird Test Cases

### Test Case FB-001: Bird Flap Changes Position
- **Mô tả**: Kiểm tra bird di chuyển lên khi flap
- **Input**: 
  - Bird ở vị trí (400, 600)
  - Gọi flap(-5.f)
  - Gọi update(9.8f, 1, false, true)
- **Expected Output**: Vị trí y của bird giảm (di chuyển lên)
- **Priority**: High

### Test Case FB-002: Pipe Moves Left
- **Mô tả**: Kiểm tra pipe di chuyển sang trái
- **Input**: 
  - Pipe ở vị trí x ban đầu
  - Gọi update(2.0f)
- **Expected Output**: Vị trí x của pipe giảm
- **Priority**: High

### Test Case FB-003: Pipe Moves Off Screen
- **Mô tả**: Kiểm tra pipe được detect là off-screen
- **Input**: 
  - Pipe update 200 lần với speed 5.f
- **Expected Output**: isOffScreen() trả về true
- **Priority**: Medium

## Snake Game Test Cases

### Test Case SN-001: Grow Increases Length
- **Mô tả**: Kiểm tra snake tăng độ dài khi grow
- **Input**: 
  - Snake initialized
  - Gọi grow()
- **Expected Output**: Độ dài snake tăng lên 1
- **Priority**: High

### Test Case SN-002: Prevents Reverse Direction
- **Mô tả**: Kiểm tra snake không đổi hướng ngược
- **Input**: 
  - Snake đang di chuyển sang phải (20.f, 0.f)
  - Set direction sang trái (-20.f, 0.f)
- **Expected Output**: Direction vẫn giữ nguyên (20.f, 0.f)
- **Priority**: High

### Test Case SN-003: Self Collision Detected
- **Mô tả**: Kiểm tra snake phát hiện tự va chạm
- **Input**: 
  - Snake grow 5 lần
  - Di chuyển tạo hình chữ U để tự cắn đuôi
- **Expected Output**: checkSelfCollision() trả về true
- **Priority**: High

### Test Case SN-004: Food Spawns Inside Bounds
- **Mô tả**: Kiểm tra food spawn trong biên
- **Input**: 
  - Gọi spawn(200, 200)
- **Expected Output**: Vị trí food nằm trong [0, 200)
- **Priority**: Medium

### Test Case SN-005: Snake Grows When Eating Food
- **Mô tả**: Kiểm tra snake tăng độ dài (giống SN-001)
- **Input**: 
  - Gọi grow()
- **Expected Output**: Độ dài snake tăng lên 1
- **Priority**: High

## Pong Game Test Cases

### Test Case PG-001: Ball Inverts Velocity X
- **Mô tả**: Kiểm tra ball đảo chiều X
- **Input**: 
  - Ball di chuyển sang phải (5.f, 0.f)
  - Gọi invertX()
  - Gọi update()
- **Expected Output**: Vị trí x giảm (di chuyển trái)
- **Priority**: High

### Test Case PG-002: Paddle Moves Up And Down
- **Mô tả**: Kiểm tra paddle di chuyển lên/xuống
- **Input**: 
  - Gọi moveUp()
  - Gọi moveDown()
- **Expected Output**: 
  - Vị trí y giảm khi moveUp()
  - Vị trí y tăng khi moveDown()
- **Priority**: High

### Test Case PG-003: Ball Inverts Velocity Y
- **Mô tả**: Kiểm tra ball đảo chiều Y
- **Input**: 
  - Ball di chuyển xuống (0.f, 5.f)
  - Gọi invertY()
  - Gọi update()
- **Expected Output**: Vị trí y giảm (di chuyển lên)
- **Priority**: High

### Test Case PG-004: Paddle Stays In Bounds
- **Mô tả**: Kiểm tra paddle không ra khỏi biên
- **Input**: 
  - Paddle ở vị trí biên
  - Di chuyển ra ngoài biên
  - Gọi updateBounds()
- **Expected Output**: Paddle vẫn nằm trong biên
- **Priority**: Medium

## Tetris Game Test Cases

### Test Case TE-001: Grid Initializes Empty
- **Mô tả**: Kiểm tra grid khởi tạo trống
- **Input**: 
  - Grid mới initialized
- **Expected Output**: Tất cả cells = 0
- **Priority**: High

### Test Case TE-002: Clear Full Rows Works
- **Mô tả**: Kiểm tra xóa hàng đầy
- **Input**: 
  - Làm đầy hàng 0
  - Gọi ClearFullRows()
- **Expected Output**: 
  - Số hàng cleared = 1
  - Hàng 0 trở về trống
- **Priority**: High

### Test Case TE-003: Row Full Then Cleared
- **Mô tả**: Kiểm tra xóa hàng đầy (giống TE-002)
- **Input**: 
  - Làm đầy hàng 19
  - Gọi ClearFullRows()
- **Expected Output**: 
  - Số hàng cleared > 0
  - Hàng 19 trở về trống
- **Priority**: High

### Test Case TE-004: Out Of Bounds Cell Is Detected
- **Mô tả**: Kiểm tra phát hiện cell ngoài biên
- **Input**: 
  - Các vị trí ngoài biên: (-1, 0), (21, 0), (0, 13)
- **Expected Output**: IsCellOutside() trả về true
- **Priority**: Medium