# Git Workflow cho Dự án oopProject

## Tổng quan

Tài liệu này mô tả quy trình làm việc với Git mà nhóm sẽ tuân thủ trong dự án oopProject. Workflow này kết hợp các tính năng của **Feature Branch Workflow** và **GitFlow** để đảm bảo sự ổn định của codebase và khả năng hợp tác hiệu quả.

## Mục tiêu

- Đảm bảo code trên nhánh `main` luôn ổn định và có thể triển khai được
- Cho phép phát triển song song nhiều tính năng
- Tạo môi trường review code minh bạch
- Giảm thiểu xung đột merge
- Dễ dàng theo dõi lịch sử phát triển

## Cấu trúc Branch

### Branches chính

| Branch | Mục đích |
|--------|----------|
| `main` | Chứa code ổn định, đã được tested. Luôn ở trạng thái có thể deploy |

### Branches hỗ trợ

| Branch Pattern | Mục đích | Ví dụ |
|----------------|----------|-------|
| `feature/*` | Phát triển tính năng mới | `feature/snake-game`, `feature/game-system` |
| `release/*` | Chuẩn bị cho bản phát hành | `release/v1.2.0` |

## 🔄 Quy trình làm việc chi tiết

### 1. Bắt đầu một tính năng mới

# 1. Cập nhật nhánh main/local
git checkout main
git pull origin main

# 2. Tạo nhánh tính năng mới (từ main)
git checkout -b feature/tên-tính-năng

# 3. Đẩy nhánh lên remote
git push -u origin feature/tên-tính-năng

**Quy tắc đặt tên nhánh:**
- Sử dụng tiếng Anh
- Viết thường, phân cách bằng dấu gạch ngang
- Mô tả ngắn gọn tính năng
- Ví dụ: `feature/flappy-bird`, `feature/core-system`

### 2. Làm việc trên nhánh tính năng

# 1. Commit thường xuyên với message rõ ràng
git add .
git commit -m "feat: thêm chức năng di chuyển cho nhân vật"

# 2. Đồng bộ với main định kỳ để tránh xung đột
git fetch origin
git merge origin/main

# 3. Đẩy code lên thường xuyên
git push origin feature/tên-tính-năng

**Quy ước commit message:**
type: mô tả ngắn gọn

[Body mô tả chi tiết nếu cần]

- feat: Tính năng mới
- fix: Sửa lỗi
- docs: Thay đổi tài liệu
- style: Thay đổi format code (không ảnh hưởng logic)
- refactor: Tái cấu trúc code
- test: Thêm test
- chore: Công việc bảo trì

### 3. Tạo Pull Request (PR)

1. Truy cập repository trên GitHub
2. Tạo Pull Request từ nhánh feature → `main`
3. Điền đầy đủ thông tin theo template:

## Mô tả tính năng
[Mô tả chi tiết tính năng này]

## Thay đổi
- [ ] Thay đổi 1
- [ ] Thay đổi 2

## Kiểm thử
- [ ] Đã test trên Windows
- [ ] Đã chạy unit tests

## Screenshots (nếu có)

### 4. Quy trình review code

1. **Assign reviewers**: Gán ít nhất 2 thành viên review
2. **Review process**:
   - Reviewer kiểm tra code quality
   - Kiểm tra logic và hiệu năng
   - Đảm bảo tuân thủ coding convention
3. **Sửa đổi** (nếu cần):
   - Thảo luận trong comment của PR
   - Tạo commit mới để fix issues
4. **Approval**: Cần ít nhất 2 approvals để merge

### 5. Merge và đóng nhánh

# 1. Merge về main (squash commits)
git checkout main
git merge --squash feature/tên-tính-năng
git commit -m "feat: thêm tính năng XYZ"

# 2. Đẩy lên main
git push origin main

# 3. Xóa nhánh feature
git branch -d feature/tên-tính-năng
git push origin --delete feature/tên-tính-năng

## Cài đặt và Configuration

### .gitconfig recommendation

[user]
    name = Your Name
    email = your.email@example.com

[alias]
    co = checkout
    ci = commit
    st = status
    br = branch
    hist = log --pretty=format:\"%h %ad | %s%d [%an]\" --graph --date=short
    type = cat-file -t
    dump = cat-file -p

### Git hooks (optional)

Thêm pre-commit hook để tự động chạy tests:

#!/bin/sh
# .git/hooks/pre-commit
echo "Running tests before commit..."
make test
if [ $? -ne 0 ]; then
    echo "Tests failed! Commit aborted."
    exit 1
fi

## Xử lý tình huống đặc biệt

### 1. Xung đột merge

# Khi gặp conflict
git mergetool
# Giải quyết conflict, sau đó
git add .
git commit -m "resolve merge conflicts"

### 2. Hotfix khẩn cấp

```bash
# Tạo nhánh hotfix từ main
git checkout -b hotfix/tên-sửa-lỗi main

# Sửa lỗi và commit
git commit -m "fix: sửa lỗi khẩn cấp XYZ"

# Merge ngay vào main
git checkout main
git merge hotfix/tên-sửa-lỗi
git push origin main

# Đồng bộ về develop
git checkout develop
git merge main
```

### 3. Revert commit sai

# Revert một commit cụ thể
git revert <commit-hash>

# Hoặc revert merge commit
git revert -m 1 <merge-commit-hash>

## Công cụ hỗ trợ

### GitHub Features

- **Protected Branches**: Bật protection cho nhánh `main`
- **Required Status Checks**: Yêu cầu tests pass trước khi merge
- **Code Owners**: Thiết lập người review tự động
- **Actions**: Tự động chạy CI/CD pipeline

### Branch Protection Rules

# Require cho nhánh main:
- Require pull request reviews before merging
- Required approving reviews: 2
- Require status checks to pass before merging
- Require branches to be up to date before merging

## Checklist trước khi tạo PR

- [ ] Code đã được test đầy đủ
- [ ] Đã chạy linter và không có lỗi
- [ ] Đã cập nhật tài liệu (nếu cần)
- [ ] Commit messages tuân thủ convention
- [ ] Không có conflict với main
- [ ] Đã test trên ít nhất 1 môi trường

## Template files

### PR Template (.github/pull_request_template.md)

## Description
<!-- Mô tả PR này làm gì -->

## Related Issues
<!-- Link đến issue liên quan -->
Fixes #123

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Đã test manual
- [ ] Đã chạy unit tests
- [ ] Ảnh hưởng đến performance

## Screenshots
<!-- Nếu là thay đổi UI -->
```

## Liên hệ và hỗ trợ

Nếu có thắc mắc về quy trình:
1. Kiểm tra tài liệu này trước
2. Hỏi trong group chat của nhóm
3. Liên hệ maintainers:
   - @nguyenvuduy102
   - @MonkeyCode2006
   - @tohoapliJong
    -@duydev123
---

*Tài liệu này được cập nhật lần cuối: 30/08/2025*