var login_btn=document.getElementById("R_login");
var register_btn=document.getElementById("L_register");
var login=document.querySelector(".login");
var register=document.querySelector(".register");
login_btn.addEventListener('click',  function() {
    R_upload_btn.value = "";
    R_upload_btn_label.style.display="block";
    R_load_img.style.height='250px';
    R_chosen_photo.removeAttribute('src');
    R_photo_file_name.textContent="";
    login.style.display = "flex";
    register.style.display = "none";
    R_photo_container.style.width="0px";
});
register_btn.addEventListener('click',  function() {
    register.style.display = "block";
    login.style.display = "none";
});