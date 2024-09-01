<?php
//require_once dirname(__FILE__)."/database_check.php";

if(isset($_GET['add_friend_no']) && isset($_COOKIE["user_no"])){
  $servername="localhost";
  $username="root";
  $password="";
  $database="social_media";
  $friend_no = $_GET['add_friend_no'];
  $user_no = $_COOKIE["user_no"]; 

  $conn = mysqli_connect($servername,$username,$password,$database);
  if(!$conn){
    die("Database connection failed: ".mysqli_connect_error());
  }
  else{
      $sql_add = "INSERT INTO friend_list VALUES ($user_no, $friend_no)";
      $result = mysqli_query($conn, $sql_add);
      header("Location: ../Home.html"); 
  }
}
?>