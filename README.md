# IPC_message_queue

compile program:
	g++ msg_send1.cpp msg_send_recv.cpp -o msg_send1
	g++ msg_send2.cpp msg_send_recv.cpp -o msg_send2
	
run program:
	./msg_send1
	./msg_send2
	
các file trong repo này dùng để trao đổi dữ liệu từ hai tiến trình khác nhau (msg_send1 và msg_send2)

1. msg_send_recv.h
- định nghĩa các hàm được sử dụng (nhiều lần) của project
- định nghĩa message structure

2. msg_send_recv.cpp
- implement hàm send_msg và recv_msg được định nghĩa trong msg_send_recv.h

3. msg_send1.cpp và msg_send2.cpp
- hàm xử lý việc gửi/nhận các message tới/từ message queue, cho phép hai tiến trình trao đổi dữ liệu qua lại

4. msg.txt
- file để generate key - dùng để truy cập vào vùng bộ nhớ với quyền đọc và ghi 

