<?php
function db_check() {
  $servername = "localhost";
  $username = "root";
  $password = "";
  $conn = new mysqli($servername, $username, $password);
  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }

  $sql = "CREATE DATABASE social_media";
  $dbname = "social_media";
  if (mysqli_query($conn, $sql)) {
    echo "Database created successfully";
    $conn = new mysqli($servername, $username, $password, $dbname);
    $sql = "CREATE TABLE username_list (
    user_no INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(30) NOT NULL,
    password VARCHAR(32) NOT NULL,
    user VARCHAR(30) NOT NULL, 
    bio VARCHAR(500) NOT NULL,
    photo VARCHAR(500) NOT NULL
    )";
    if (mysqli_query($conn, $sql)) {
      echo "Table username_list 新增成功";
      if (($handle = fopen($_SERVER["DOCUMENT_ROOT"]. "/final_project/csv/username_list.csv", "r")) !== FALSE) {
        $i=0;
        while (($data = fgetcsv($handle, 1000, ',')) !== FALSE) {
          if($i == 0) {  // 跳過第一列
            $i++;
            continue;
          }
          $username = $data[1];
          $password = $data[2];
          $user = $data[3];
          $bio = $data[4];
          $photo = $data[5];
          // echo $email. '  '. $username. '  '. $password. '  '. $reg_date. '<br>';
          $query = "INSERT INTO username_list (username, password, user, bio,photo) VALUES 
            ('$username', '$password', '$user', '$bio', '$photo')";
          $result = mysqli_query($conn, $query);
          if ($result == false) {
            echo 'Error description <br/>' . mysqli_error($conn);
          }
        }
        fclose($handle);
      }
    } else {
      echo "Error creating table: " . $conn->error;
    }
    $sql = "CREATE TABLE friend_list (
    user_no INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    friend_no INT(6) NOT NULL
    )";
    if (mysqli_query($conn, $sql)) {
      echo "Table friend_list 新增成功";
      if (($handle = fopen($_SERVER["DOCUMENT_ROOT"]. "/final_project/csv/friend_list.csv", "r")) !== FALSE) {
        $i=0;
        while (($data = fgetcsv($handle, 1000, ',')) !== FALSE) {
          if($i == 0) {  // 跳過第一列
            $i++;
            continue;
          }
          $friend_no = $data[1];
          // echo $user_id. '  '. $username. '  '. $title. '  '. $content. '  '. $img. '  '. $reg_date. '<br>';
          $query = "INSERT INTO user_article (friend_no) VALUES 
            ('$friend_no')";
          $result = mysqli_query($conn, $query);
          if ($result == false) {
            echo 'Error description <br/>' . mysqli_error($conn);
          }
        }
        fclose($handle);
      }
    } else {
      echo "Error creating table: " . $conn->error;
    }

    $sql = "CREATE TABLE posts (
      posts_no int NOT NULL AUTO_INCREMENT, 
      poster_no int NOT NULL,
      content text DEFAULT NULL,
      'time' datetime,
      picture varchar(200),
      PRIMARY KEY (posts_no),
      FOREIGN KEY (poster_no) REFERENCES user_list(user_no)
      )";
      if (mysqli_query($conn, $sql)) {
        echo "Table posts 新增成功";
        if (($handle = fopen($_SERVER["DOCUMENT_ROOT"]. "/final_project/csv/post_data.csv", "r")) !== FALSE) {
          $i = 0;
          while (($data = fgetcsv($handle, 1000, ',')) !== FALSE) {
            if($i == 0) {  // 跳過第一列
              $i++;
              continue;
            }
            $poster_no = $data[1];
            $content = $data[2];
            $time = $data[3];
            $picture = $data[4];
            $query = "INSERT INTO posts (poster_no, content, 'time', picture)
                      VALUES ('$poster_no', '$content', '$time', '$picture')";
            $result = mysqli_query($conn, $query);
            if ($result == false) {
              echo 'Error description <br/>' . mysqli_error($conn);
            }
          }
          fclose($handle);
        }
      } else {
        echo "Error creating table: " . $conn->error;
      }

  }
  return  $conn = new mysqli($servername, $username, $password, $dbname);
}