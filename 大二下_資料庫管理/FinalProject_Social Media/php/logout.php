<?php
setcookie("user_no","",time()-1800,"/");
setcookie("username","",time()-1800,"/");
setcookie("password","",time()-1800,"/");
setcookie("nickname","",time()-1800,"/");
setcookie("user_photo","",time()-1800,"/");
header("Location:../LoginRegisterPage.html");
?>
