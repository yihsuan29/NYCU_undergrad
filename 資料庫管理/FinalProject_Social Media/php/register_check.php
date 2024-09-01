<?php
//require_once dirname(__FILE__)."/database_check.php";

$servername="localhost";
$username="root";
$password="";
$database="social_media";

$conn = mysqli_connect($servername,$username,$password,$database);
if(!$conn){
  die("Database connection failed: ".mysqli_connect_error());
}
if (isset($_POST['R_username'])&&isset($_POST['R_password'])&&isset($_POST['R_password_check'])&&isset($_POST['R_name'])&&isset($_POST['R_photo_name'])){
  $R_photo_name = htmlspecialchars($_POST['R_photo_name']);
  if($R_photo_name ==""){
    $R_photo_name = "img/HeadPhoto/user_photo.jpg";
  }
  else{
    $R_photo_name = 'img/HeadPhoto/'.htmlspecialchars($_POST["R_photo_name"]);
  }
    $query = [
      'R_username' => htmlspecialchars($_POST["R_username"]),
      'R_password' => htmlspecialchars($_POST["R_password"]),
      'R_password_check' => htmlspecialchars($_POST["R_password_check"]),
      'R_name'     => htmlspecialchars($_POST['R_name']),
      'R_photo_name'=> $R_photo_name
    ];
    //$conn = db_check();
    insertData($query['R_username'],$query['R_password'],$query['R_password_check'],$query['R_name'],$query['R_photo_name'],$conn);
    $conn->close();
}
function insertData($username, $password,$check_password, $name,$photo, $conn) {
  $username_sql = "SELECT user_no FROM username_list WHERE username = '$username'";
  $username_result = mysqli_query($conn, $username_sql);
  if(mysqli_num_rows($username_result) > 0) {
    echo "fail";
  }
  if($password!=$check_password){
    echo "fail";
  }
  if((mysqli_num_rows($username_result) === 0)&& ($password==$check_password)) {
    $sql = "INSERT INTO username_list (username,password, nickname,user_photo)
    VALUES ('$username', '$password', '$name','$photo')";
    if (mysqli_query($conn, $sql)) {
      header("Location:../LoginRegisterPage.html");
      echo "success";
    } else {
      echo "Error: " . $sql . "<br>" . $conn->error;
    }  
  }
}
?>
