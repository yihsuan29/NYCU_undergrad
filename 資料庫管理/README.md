# 資料庫Final Project - Social Media
## 前端
### 登入頁面
![](https://i.imgur.com/WVj5baH.png)
### 註冊頁面
![](https://i.imgur.com/EiPvsmc.png)
### 個人檔案
![](https://i.imgur.com/9dfNh2T.jpg)


![](https://i.imgur.com/kNdSbyx.jpg)
### 修改個資頁面
![](https://i.imgur.com/J0MVFAo.png)


### 發文頁面
![](https://i.imgur.com/GrinU91.png)
### 編輯貼文頁面
![](https://i.imgur.com/HQ8rR75.jpg)

![](https://i.imgur.com/GaEJy76.jpg)

### 首頁
![](https://i.imgur.com/GGXEPuR.jpg)

![](https://i.imgur.com/AqPtCz8.png)


### 好友個人檔案
![](https://i.imgur.com/tOZeYmv.jpg)



## 後端功能實作(php)
### 登入
![](https://i.imgur.com/dcRnvLu.png)

* 比對帳號密碼是否存在
* 把user_no寫入cookies

### 註冊
![](https://i.imgur.com/u97oYal.png)
* 比對帳號是否已註冊過
* 確認密碼無誤
* 從電腦裡讀出圖片並且顯示出來
可參考: https://developer.mozilla.org/zh-TW/docs/Web/API/File/Using_files_from_web_applications#%E4%BD%BF%E7%94%A8html%E9%81%B8%E6%93%87%E6%9C%AC%E5%9C%B0%E6%AA%94%E6%A1%88
如果沒有上傳請使用預設頭像
![](https://i.imgur.com/su3heih.png =100x80)
* 把資料寫進username_list資料表

### 修改個資
![](https://i.imgur.com/ZHiI2Qe.png)
* 透過cookie 讀出是哪位使用者
* 確認密碼無誤
* 從電腦裡讀出圖片並且顯示出來 如果沒有上傳就不要更動原本的頭像
* 把資料寫進username_list資料表

### 加好友
![](https://i.imgur.com/1fUk2iX.png)
* 讀出所有非朋友的人(用not exist)
* 在html顯示出讀出的username 跟 photo **並包在同一個div裡** 
* **最終要用js生成div 不可以直接用php顯示出來**
* 按下加好友後friend_list新增一行 user_no=當前使用者 friend_no=該陌生人的user_no

### 刪好友(類似加好友)
* 讀出所有朋友(用exist)
* 在html顯示出讀到的username 跟 photo **並包在同一個div裡** 
* **最終要用js生成div 不可以直接用php顯示出來**
* 按下刪好友後friend_list刪除user_no=當前使用者 friend_no=該朋友的user_no的那行

### 發文
![](https://i.imgur.com/niRxtLp.png)
* 從電腦裡讀出圖片並且顯示出來 如果沒有上傳可以用default的黑圖之類
* 把資料寫進post_list資料表 其中user_no是用cookies取得 另外還要存發文時間(應該是用javescript 的 getTime 可參考 https://www.delftstack.com/zh-tw/howto/javascript/get-current-time-javascript/)

### 編輯貼文
![](https://i.imgur.com/gUs54Eg.png)
* 讀出欲改的貼文原本的內容 (用input value="")
* 然後改寫內容並存到post_list

### 刪除貼文
* 透過欲刪除貼文的post_no 把post_list裡那行刪掉

### 個人檔案
![](https://i.imgur.com/OhH2kgv.png)
* 用cookies存的user_no 讀出對應的使用者個資 顯示他的username 跟照片
* 用cookies存的user_no 讀出對應的發文紀錄 顯示出post_no跟 該貼文的照片 (兩者要存在同一個div)
*  **最終要用js生成div 不可以直接用php顯示出來**
*  並且要能根據username改變title
    比方說使用者叫lala 則title要變成"lala的個人檔案"


### 個人檔案=>查看貼文內容
![](https://i.imgur.com/NQgnPzg.png)
* 點選某貼文 透過他的post_no 查到該貼文的貼文內容 **而且這些資料要分開用不同的variable 儲存**


### 首頁
![](https://i.imgur.com/6LP8Kgo.png)
* 用cookies存的user_no 找到他的好友
* 用好友的user_no 讀出對應的個資(1.頭貼 2.username)以及發文紀錄(3.post_no 4.已發了多長時間(用現在時間減去發文時間) 5.貼文內容 6.貼文圖片) 
* **而且這些資料要分開用不同的variable 儲存**
* **全部東西要裝在同一個div** 
* **最終要用js生成div 不可以直接用php顯示出來**
* 現在時間可用用javescript 的 getTime 可參考 https://www.delftstack.com/zh-tw/howto/javascript/get-current-time-javascript/


## 分工
### 陳以瑄(前端):
登入頁面 註冊頁面 個人檔案(自己+好友) 修改個資頁面 發文頁面 編輯貼文頁面
### 吳珮慈(前端):
首頁
### 李語涵(後端):
登入 註冊 修改個資 加好友 刪好友
### 陳盈均(後端):
發文 編輯貼文 刪除貼文
### 吳安琪(後端):
個人檔案 個人檔案=>查看貼文 首頁











