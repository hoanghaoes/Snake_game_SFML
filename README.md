# snakegamesfml
<h1>Dự án Lập trình nâng cao</h1>
  <ul>
    <li>Tên sinh viên: Nguyễn Hoàng Hào
    <li>MSV: 21020314</li>
    <li>Lớp: K66CC</li></li>
  </ul>  
<h2>Cài đặt và chạy chương trình:</h2> 
  <ul>
    <li ">lưu thư mục về máy.</li>
    <li>Mở file Project Snake sfml.sln bằng Visual Studio.</li>
    <li>Run & Play</li>
  </ul>

<h2>Mô tả trò chơi</h2>  
  <ul>
    <li>Là game điều khiển rắn ăn mụ tiêu bằng các nút điều hướng </li>
    <li>Thay vì chơi trên điện thoại thì game chơi trên máy tình và sử dụng các nút trên bàn phím (lên, xuống, trái, phải,space,esc) để xử lí rắn di chuyển và chuyển trạng thái.</li>
    <li>Diều khiển rắn ăn quả để tăng kích thước, trò chơi kết thúc khi rắn chạm biên hoặc đầu va chạm với đuôi . </li>
  </ul>

<h2>Mô tả các chức năng game</h2>  
     <ul>
    <li>Menu game gồm tuỳ chọn bắt đầu và thoát game .</li>
    <li>Khi hiện cửa số game chọn "Play" xong nhấn enter để chơi,có hiệu ứng đổi màu chữ khi chọn "play" hoặc "exit.</li>
    <li>Tăng kích thước rắn khi ăn quả. </li>
    <li>Rắn không có khả năng đi xuyên tường.</li>
    <li>Game có nhạc trong quá trình trò chơi,khi ăn và khi kết thúc trò chơi.</li>
    <li>Khi kết thúc game(đầu rắn chạm thân hoặc chạm biên) sẽ in ra màn hình số điểm và quay lại màn hình bắt đầu sau 5s.</li>
    </ul>

<h2>Các kỹ thuật lập trình</h2>  
     <ul>                                                                                                                                          
    <li>Sử dụng kiểu "class" cho game.</li>
    <li>Rắn sử dụng "vector" để thêm linh hoạt cho code khi làm dài rắn.</li>
    <li>Phân loại chức năng rõ ràng(mỗi chức năng 1 hàm).</li>
    <li>Sử dụng đồ họa từ SFML như SFML/Graphics.hpp, SFML/Audio.hpp để tăng sự sinh động cho game.</li>
    </ul>

<h2>demo game</h2>  
     <ul>
    <li>https://youtu.be/AzQAEZRR5Gk</li>
    <li>[GameMenu](https://drive.google.com/file/d/1IroB9s-_XLYKwFPLXd-PQ2oYt6URHypk/view?usp=sharing)</li>
    <li>[GamePlay](https://drive.google.com/file/d/1Yjt3xs7SwT38y-L_yDFesPi9lWQZcR1a/view?usp=sharing)</li>
    <li>[GameOver](https://drive.google.com/file/d/1GUWEzuylGuRlQ5V0CMXN0jwodaoA6pgf/view?usp=sharing)</li>
  </ul>


<h2>Tự đánh giá, hướng phát triển game tiếp theo</h2>  
    <ul>                                        
    <li>Game hoàn thiện chức năng cơ bản,tự đánh giá tầm 7-7,5. </li>
    <li>Cần bổ sung phần tạm dừng game, điểm cao nhất, bảng xếp hạng , tạo thêm nhiều bản đồ hơn cho game với các vật cản, buff, mức độ khó của game tăng dần theo số điểm .</li>
    </ul>
