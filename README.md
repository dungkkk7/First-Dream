
```

███████╗██╗██████╗ ████████╗    ██████╗ ██████╗ ███████╗ █████╗ ███╗   ███╗
██╔════╝██║██╔══██╗╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██╔══██╗████╗ ████║
█████╗  ██║██████╔╝   ██║       ██║  ██║██████╔╝█████╗  ███████║██╔████╔██║
██╔══╝  ██║██╔══██╗   ██║       ██║  ██║██╔══██╗██╔══╝  ██╔══██║██║╚██╔╝██║
██║     ██║██║  ██║   ██║       ██████╔╝██║  ██║███████╗██║  ██║██║ ╚═╝ ██║
╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝       ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝
                                                                           
```

## Tổng Quan
Dự án này tập trung vào việc xây dựng một **Remote Access Trojan (RAT)** – một phần mềm cho phép kiểm soát máy tính từ xa với nhiều tính năng mạnh mẽ. RAT này sẽ giúp người dùng (ở đây là người phát triển) theo dõi và điều khiển máy tính mục tiêu từ xa, bao gồm việc ghi lại phím bấm, chụp ảnh màn hình, quay webcam, lấy tài liệu, và nhiều tính năng khác.

**Mục đích**: Tạo ra một công cụ toàn diện để quản lý và truy cập máy tính từ xa.  
**Lưu ý quan trọng**: Việc phát triển hoặc sử dụng RAT mà không có sự đồng ý là **bất hợp pháp** và trái với đạo đức. Dự án này chỉ nên được thực hiện với mục đích **giáo dục** hoặc **nghiên cứu bảo mật** trong môi trường được kiểm soát.

---

## Tài Nguyên
- **[Duckey Logger](https://github.com/CosmodiumCS/MalwareDNA/tree/main/rubberducky/DucKey-Logger)**: Đây là một công cụ ghi lại phím bấm (keylogger) có sẵn trên GitHub từ dự án MalwareDNA. Chúng ta sẽ sử dụng nó làm nền tảng để phát triển module keylogger cho RAT.

---

## Các Thành Phần Chính

### 1. Keylogger (Ghi Phím)
- **Chức năng**: Ghi lại mọi phím mà người dùng nhấn trên máy tính, ví dụ như văn bản họ gõ, mật khẩu, hoặc lệnh.
- **Tính năng bổ sung**: 
  - Phát hiện phím **Backspace** để chỉnh sửa chính xác những gì người dùng gõ (ví dụ: nếu họ xóa ký tự, nội dung ghi lại sẽ phản ánh đúng).
  - Hỗ trợ các phím đặc biệt như Enter, Shift, Ctrl.
- **Nguồn tham khảo**: Dựa trên **[Duckey Logger](https://github.com/CosmodiumCS/MalwareDNA/tree/main/rubberducky/DucKey-Logger)** và cải tiến thêm.

### 2. Chụp Ảnh Màn Hình
- **Chức năng**: Chụp ảnh màn hình của máy tính mục tiêu bất cứ khi nào được yêu cầu hoặc theo lịch trình tự động.
- **Ứng dụng**: Giúp người điều khiển xem người dùng đang làm gì trên màn hình.

### 3. Truy Cập Webcam
- **Chức năng**: Bật webcam từ xa và ghi lại hình ảnh hoặc video.
- **Ứng dụng**: Theo dõi trực tiếp người dùng hoặc thu thập thông tin nhạy cảm từ môi trường xung quanh.

### 4. Đánh Cắp Dữ Liệu (Exfiltration)
- **Chức năng**: Tìm kiếm và sao chép các tệp quan trọng từ máy tính mục tiêu, sau đó gửi về cho người điều khiển.
- **Ví dụ dữ liệu**: 
  - Tệp văn bản (Word, Notepad).
  - Bảng tính (Excel).
  - Hình ảnh hoặc bất kỳ loại tệp nào được chỉ định.

### 5. Truy Cập Từ Xa (Remote Access)
- **Chức năng**: Cho phép người điều khiển gửi lệnh đến máy tính mục tiêu và nhận kết quả, giống như đang ngồi trước máy tính đó.
- **Ví dụ**: Mở file, chạy chương trình, hoặc tắt máy.

### 6. Đánh Cắp Thông Tin Đăng Nhập (Credentials)
- **Chức năng**: Thu thập mật khẩu và thông tin đăng nhập từ nhiều nguồn:
  - **Web**: Lấy mật khẩu từ trình duyệt (Chrome, Firefox, v.v.).
  - **Máy tính**: Lấy mật khẩu tài khoản người dùng trên hệ điều hành.
  - **Ứng dụng**: Lấy thông tin từ các phần mềm như Skype, Discord.
  - **Wifi**: Lấy mật khẩu của các mạng Wifi mà máy đã từng kết nối.

### 7. Thu Thập Thông Tin Chi Tiết (Advanced Reconnaissance)
- **Chức năng**: Lấy thông tin cá nhân từ máy tính mục tiêu.
- **Ví dụ**: Danh bạ, email, tin nhắn, hoặc bất kỳ dữ liệu nào giúp hiểu rõ hơn về người dùng.

### 8. Nâng Quyền (Privilege Escalation)
- **Chức năng**: Tìm cách giành quyền cao hơn (quyền quản trị viên) trên máy tính mục tiêu.
- **Ứng dụng**: Cho phép thực hiện các lệnh hoặc truy cập các phần bị giới hạn bởi hệ thống.

### 9. Lan Truyền (Worm)
- **Chức năng**: Tự động sao chép và lây lan RAT sang các máy tính khác trong cùng mạng.
- **Ứng dụng**: Mở rộng phạm vi kiểm soát mà không cần người điều khiển can thiệp.

---

## Lộ Trình Phát Triển

### Bước 1: Làm Lại Keylogger
- **Mục tiêu**: Cải thiện **[Duckey Logger](https://github.com/CosmodiumCS/MalwareDNA/tree/main/rubberducky/DucKey-Logger)** để nó hoạt động tốt hơn.
- **Công việc**: 
  - Thêm khả năng nhận diện phím Backspace và phím đặc biệt.
  - Tăng tính ổn định và làm cho nó khó bị phát hiện hơn.

### Bước 2: Ẩn Giấu và Né Tránh
- **Mục tiêu**: Đảm bảo RAT không bị phát hiện bởi các phần mềm bảo mật.
- **Công việc**:
  - **Phát hiện AV và VM**: Tạo cơ chế nhận biết phần mềm diệt virus (Antivirus) và máy ảo (Virtual Machine), sau đó né tránh hoặc tắt chúng.
  - **Tắt Firewall và AV**: Tìm cách vô hiệu hóa tường lửa và phần mềm diệt virus trên máy tính mục tiêu.

### Bước 3: Xây Dựng Các Module Còn Lại
- **Chụp Ảnh Màn Hình**: Viết code để chụp và gửi ảnh màn hình.
- **Truy Cập Webcam**: Thêm tính năng bật webcam và ghi hình.
- **Đánh Cắp Dữ Liệu**: Tạo công cụ tìm kiếm và gửi tệp từ máy tính.
- **Truy Cập Từ Xa**: Xây dựng hệ thống gửi và nhận lệnh từ xa.
- **Đánh Cắp Thông Tin Đăng Nhập**: Viết code để lấy mật khẩu từ web, máy tính, ứng dụng, và Wifi.
- **Thu Thập Thông Tin Chi Tiết**: Tạo module lấy danh bạ, email, v.v.
- **Nâng Quyền**: Nghiên cứu cách chiếm quyền quản trị viên.
- **Lan Truyền**: Xây dựng cơ chế để RAT tự lây lan trong mạng.

### Bước 4: Gộp Lại và Kiểm Tra
- **Tích hợp**: Kết hợp tất cả các module thành một RAT hoàn chỉnh.
- **Kiểm tra**: Dùng máy ảo để thử nghiệm xem RAT có hoạt động ổn định, khó bị phát hiện và hiệu quả không.

---

## Tính Năng Bổ Sung (Extraneous)
- **Gây Màn Hình Xanh (BSOD)**: Thêm tùy chọn làm máy tính mục tiêu bị lỗi nghiêm trọng (màn hình xanh).
- **Lịch Sử Duyệt Web**: Ghi lại các trang web mà người dùng đã truy cập.
- **Hoạt Động Người Dùng**: Theo dõi các hành động như mở ứng dụng, nhấp chuột, hoặc di chuyển con trỏ.

---

